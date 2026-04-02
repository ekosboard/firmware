#include "EPD.h"
#include "epd_GDEY042T81.h"
#include "epd_interface.h"
#include "freertos/projdefs.h"


static void GDEY042T81_init_driver(void);
static void GDEY042T81_sleep(void);
static void GDEY042T81_clear(void);
static void GDEY042T81_clear_fast(void);
static void GDEY042T81_display_image(const unsigned char *data);
static void GDEY042T81_display_image_fast(const unsigned char *data);
static void GDEY042T81_display_image_grayscale(const unsigned char *data);
static void GDEY042T81_display_image_partial_full(const unsigned char *data, bool base);

epd_interface_t gdey042t81_driver = {
    .init = GDEY042T81_init_driver,
    .clear = GDEY042T81_clear,
    .display_image = GDEY042T81_display_image,
    .display_image_fast = GDEY042T81_display_image_fast,
    .display_image_grayscale = GDEY042T81_display_image_grayscale,
    .display_image_partial = GDEY042T81_display_image_partial_full,
    .display_image_area = NULL,
    .set_basemap = NULL,
    .sleep = GDEY042T81_sleep
};

static spi_device_handle_t spi_handle;

static void init_gpio()
{
    gpio_set_direction(GDEY042T81_BUSY, GPIO_MODE_INPUT);
    gpio_set_direction(GDEY042T81_RST, GPIO_MODE_OUTPUT);
    gpio_set_direction(GDEY042T81_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(GDEY042T81_CS, GPIO_MODE_OUTPUT);
}

static void init_SPI()
{
    spi_bus_config_t buscfg = {
        .miso_io_num = -1,
        .mosi_io_num = GDEY042T81_MOSI,
        .sclk_io_num = GDEY042T81_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096
    };
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 10 * 1000 * 1000,
        .mode = 0,
        .spics_io_num = GDEY042T81_CS,
        .queue_size = 7,
        .flags = 0,
    };
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &spi_handle));
}

static void GDEY042T81_init_driver(void)
{
    init_gpio();
    init_SPI();
}

static void GDEY042T81_write_cmd(unsigned char command)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &command;

    gpio_set_level(GDEY042T81_DC, 0);
    spi_device_transmit(spi_handle, &t);
}

static void GDEY042T81_write_data(unsigned char data)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &data;

    gpio_set_level(GDEY042T81_DC, 1);
    spi_device_transmit(spi_handle, &t);
}

static void GDEY042T81_wait_busy(void)
{
    while(42)
    {
        if (gpio_get_level(GDEY042T81_BUSY) == 0) break;;
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

static void GDEY042T81_sleep(void)
{
    GDEY042T81_write_cmd(0x10);
    GDEY042T81_write_data(0x01);
    vTaskDelay(pdMS_TO_TICKS(10));
}

////////////////////////////////////////////////////////////////////////////////
//  CLASSIC (SLOW)
////////////////////////////////////////////////////////////////////////////////
static void GDEY042T81_init_display(void)
{
    gpio_set_level(GDEY042T81_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(GDEY042T81_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(10));

    GDEY042T81_wait_busy();
    GDEY042T81_write_cmd(0x12);  //SWRESET
    GDEY042T81_wait_busy();

    GDEY042T81_write_cmd(0x01); //Driver output control
    GDEY042T81_write_data((GDEY042T81_HEIGHT - 1) % 256);
    GDEY042T81_write_data((GDEY042T81_HEIGHT - 1) / 256);
    GDEY042T81_write_data(0x01);

    GDEY042T81_write_cmd(0x21); //  Display update control
    GDEY042T81_write_data(0x40);
    GDEY042T81_write_data(0x00);

    GDEY042T81_write_cmd(0x3C); //BorderWavefrom
    GDEY042T81_write_data(0x05);

    GDEY042T81_write_cmd(0x11); //data entry mode
    GDEY042T81_write_data(0x01);

    GDEY042T81_write_cmd(0x44); //set Ram-X address start/end position
    GDEY042T81_write_data(0x00);
    GDEY042T81_write_data(GDEY042T81_WIDTH / 8 - 1);
    GDEY042T81_write_cmd(0x45); //set Ram-Y address start/end position
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)%256);
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)/256);
    GDEY042T81_write_data(0x00);
    GDEY042T81_write_data(0x00);

    GDEY042T81_write_cmd(0x4E);   // set RAM x address count to 0;
    GDEY042T81_write_data(0x00);
    GDEY042T81_write_cmd(0x4F);   // set RAM y address count to 0X199;
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)%256);
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)/256);
    GDEY042T81_wait_busy();
}

static void GDEY042T81_update_display(void)
{
    GDEY042T81_write_cmd(0x22); //Display Update Control
    GDEY042T81_write_data(0xF7);
    GDEY042T81_write_cmd(0x20); //Activate Display Update Sequence
    GDEY042T81_wait_busy();
}

static void GDEY042T81_write_display(const unsigned char *datas)
{
    unsigned int i;
    GDEY042T81_write_cmd(0x24);   //write RAM for black(0)/white (1)
    for(i = 0; i < GDEY042T81_ARRAY; i++)
    {
        GDEY042T81_write_data(datas[i]);
    }
    GDEY042T81_write_cmd(0x26);   //write RAM for black(0)/white (1)
    for(i = 0; i < GDEY042T81_ARRAY; i++)
    {
        GDEY042T81_write_data(datas[i]);
    }
}

static void GDEY042T81_display_image(const unsigned char *data)
{
    GDEY042T81_init_display();
    GDEY042T81_write_display(data);
    GDEY042T81_update_display();
    GDEY042T81_sleep();
}

//Clear screen display
static void GDEY042T81_write_clear(void)
{
    unsigned int i;
    GDEY042T81_write_cmd(0x24);   //write RAM for black(0)/white (1)
    for(i=0; i < GDEY042T81_ARRAY; i++)
    {
        GDEY042T81_write_data(0xff);
    }
    GDEY042T81_write_cmd(0x26);   //write RAM for black(0)/white (1)
    for(i=0; i < GDEY042T81_ARRAY; i++)
    {
        GDEY042T81_write_data(0xff);
    }
}

static void GDEY042T81_clear(void)
{
    GDEY042T81_init_display();
    GDEY042T81_write_clear();
    GDEY042T81_update_display();
    GDEY042T81_sleep();
}


////////////////////////////////////////////////////////////////////////////////
//  FAST
////////////////////////////////////////////////////////////////////////////////
static void GDEY042T81_init_fast_display(void)
{
    gpio_set_level(GDEY042T81_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(GDEY042T81_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(10));

    GDEY042T81_write_cmd(0x12);  //SWRESET
    GDEY042T81_wait_busy();

    GDEY042T81_write_cmd(0x01); //Driver output control
    GDEY042T81_write_data((GDEY042T81_HEIGHT - 1) % 256);
    GDEY042T81_write_data((GDEY042T81_HEIGHT - 1) / 256);
    GDEY042T81_write_data(0x01);

    GDEY042T81_write_cmd(0x21);
    GDEY042T81_write_data(0x40);
    GDEY042T81_write_data(0x00);

    GDEY042T81_write_cmd(0x3C);
    GDEY042T81_write_data(0x05);

    //1.5s
    GDEY042T81_write_cmd(0x1A); // Write to temperature register
    GDEY042T81_write_data(0x6E);

    GDEY042T81_write_cmd(0x22); // Load temperature value
    GDEY042T81_write_data(0x91);
    GDEY042T81_write_cmd(0x20);
    GDEY042T81_wait_busy();

    GDEY042T81_write_cmd(0x11);  // Data entry mode
    GDEY042T81_write_data(0x01);

    GDEY042T81_write_cmd(0x44); //set Ram-X address start/end position
    GDEY042T81_write_data(0x00);
    GDEY042T81_write_data(GDEY042T81_WIDTH/8-1);


    GDEY042T81_write_cmd(0x45); //set Ram-Y address start/end position
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)%256);
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)/256);
    GDEY042T81_write_data(0x00);
    GDEY042T81_write_data(0x00);

    GDEY042T81_write_cmd(0x4E);   // set RAM x address count to 0;
    GDEY042T81_write_data(0x00);
    GDEY042T81_write_cmd(0x4F);   // set RAM y address count to 0X199;
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)%256);
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)/256);
    GDEY042T81_wait_busy();
}

//Fast refresh 1 update function
static void GDEY042T81_update_fast_display(void)
{
    GDEY042T81_write_cmd(0x22); //Display Update Control
    GDEY042T81_write_data(0xC7);
    GDEY042T81_write_cmd(0x20); //Activate Display Update Sequence
    GDEY042T81_wait_busy();
}

//Fast refresh display function
static void GDEY042T81_write_fast_display(const unsigned char *datas)
{
    unsigned int i;

    GDEY042T81_write_cmd(0x24);
    for(i = 0; i < GDEY042T81_ARRAY; i++)
    {
        GDEY042T81_write_data(datas[i]);
    }

    GDEY042T81_write_cmd(0x26);
    for(i = 0; i < GDEY042T81_ARRAY; i++)
    {
        GDEY042T81_write_data(datas[i]);
    }
}

static void GDEY042T81_display_image_fast(const unsigned char *data)
{
    GDEY042T81_init_fast_display();
    GDEY042T81_write_fast_display(data);
    GDEY042T81_update_fast_display();
    GDEY042T81_sleep();
}

static void GDEY042T81_write_fast_clear(void)
{
    unsigned int i;

    GDEY042T81_write_cmd(0x24);
    for(i = 0; i < GDEY042T81_ARRAY; i++)
    {
        GDEY042T81_write_data(0xff);
    }

    GDEY042T81_write_cmd(0x26);
    for(i = 0; i < GDEY042T81_ARRAY; i++)
    {
        GDEY042T81_write_data(0xff);
    }
}

static void GDEY042T81_clear_fast(void)
{
    GDEY042T81_init_fast_display();
    GDEY042T81_write_fast_clear();
    GDEY042T81_update_fast_display();
    GDEY042T81_sleep();
}


////////////////////////////////////////////////////////////////////////////////
//  GRAYSCALE
////////////////////////////////////////////////////////////////////////////////
static void GDEY042T81_init_grayscale_display(void)
{
    gpio_set_level(GDEY042T81_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(GDEY042T81_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(10));

    GDEY042T81_write_cmd(0x12);  //SWRESET
    GDEY042T81_wait_busy();

    GDEY042T81_write_cmd(0x01); //Driver output control
    GDEY042T81_write_data((GDEY042T81_HEIGHT - 1) % 256);
    GDEY042T81_write_data((GDEY042T81_HEIGHT - 1) / 256);
    GDEY042T81_write_data(0x01);

    GDEY042T81_write_cmd(0x3C);
    GDEY042T81_write_data(0x05);

    //4 Gray
    GDEY042T81_write_cmd(0x1A); // Write to temperature register
    GDEY042T81_write_data(0x5A);

    GDEY042T81_write_cmd(0x22); // Load temperature value
    GDEY042T81_write_data(0x91);
    GDEY042T81_write_cmd(0x20);
    GDEY042T81_wait_busy();

    GDEY042T81_write_cmd(0x11);  // Data entry mode
    GDEY042T81_write_data(0x01);

    GDEY042T81_write_cmd(0x44); //set Ram-X address start/end position
    GDEY042T81_write_data(0x00);
    GDEY042T81_write_data(GDEY042T81_WIDTH/8-1);
    GDEY042T81_write_cmd(0x45); //set Ram-Y address start/end position
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)%256);
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)/256);
    GDEY042T81_write_data(0x00);
    GDEY042T81_write_data(0x00);

    GDEY042T81_write_cmd(0x4E);   // set RAM x address count to 0;
    GDEY042T81_write_data(0x00);
    GDEY042T81_write_cmd(0x4F);   // set RAM y address count to 0X199;
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)%256);
    GDEY042T81_write_data((GDEY042T81_HEIGHT-1)/256);
    GDEY042T81_wait_busy();
}

//4 Gray refresh update function
static void GDEY042T81_update_grayscale_display(void)
{
    GDEY042T81_write_cmd(0x22); //Display Update Control
    GDEY042T81_write_data(0xCF);
    GDEY042T81_write_cmd(0x20); //Activate Display Update Sequence
    GDEY042T81_wait_busy();
}

static unsigned char R24_DTM1(unsigned char in_pixel_1, unsigned char in_pixel_2)
{
    unsigned char tmp_1, tmp_2;
    unsigned char out_pixel = 0x00;

    tmp_1 = in_pixel_1;
    tmp_2 = in_pixel_2;

    for(int i = 0; i < 4; i++)
    {
        out_pixel = out_pixel << 1;
        if(((tmp_1 & 0xC0) == 0xC0) || ((tmp_1 & 0xC0) == 0x40))
        {
            out_pixel = out_pixel | 0x01;
        }
        else
        {
            out_pixel = out_pixel | 0x00;
        }

        tmp_1 = tmp_1 << 2;
    }

    for(int all = 0; all < 4; all++)
    {
        out_pixel = out_pixel << 1;
        if((tmp_2 & 0xC0) == 0xC0 || (tmp_2 & 0xC0) == 0x40)
        {
            out_pixel = out_pixel | 0x01;
        }
        else
        {
            out_pixel = out_pixel |0x00;
        }
        tmp_2 = tmp_2 << 2;
    }
    return out_pixel;
}

static unsigned char R26_DTM2(unsigned char in_pixel_1, unsigned char in_pixel_2)
{
    unsigned int i, all;
    unsigned char tmp_1 , tmp_2 ;
    unsigned char out_pixel = 0x00;
    tmp_1 = in_pixel_1;
    tmp_2 = in_pixel_2;

    for(i = 0; i < 4; i++)
    {
        out_pixel = out_pixel << 1;
        if(((tmp_1 & 0xC0) == 0xC0) || ((tmp_1 & 0xC0) == 0x80))
        {
            out_pixel = out_pixel | 0x01;
        }
        else
        {
            out_pixel = out_pixel | 0x00;
        }
        tmp_1 = tmp_1 << 2;
    }

    for(all = 0; all < 4; all++)
    {
        out_pixel = out_pixel << 1;
        if((tmp_2 & 0xC0) == 0xC0 || (tmp_2 & 0xC0) == 0x80)
        {
            out_pixel = out_pixel | 0x01;
        }
        else
        {
            out_pixel = out_pixel | 0x00;
        }
        tmp_2 = tmp_2 << 2;
    }
    return out_pixel;
}

//4 Gray refresh display function
static void GDEY042T81_write_grayscale_display(const unsigned char *datas)
{
    unsigned int i;
    unsigned char value;

    GDEY042T81_write_cmd(0x24);
    for(i = 0; i < GDEY042T81_ARRAY * 2; i += 2)
    {
        value = R24_DTM1(*(datas + i), *(datas + i + 1));
        GDEY042T81_write_data(value);
    }

    GDEY042T81_write_cmd(0x26);
    for(i = 0; i < GDEY042T81_ARRAY * 2; i += 2)
    {
        value = R26_DTM2(*(datas + i), *(datas + i + 1));
        GDEY042T81_write_data(value);
    }
}

static void GDEY042T81_display_image_grayscale(const unsigned char *data)
{
    GDEY042T81_init_grayscale_display();
    GDEY042T81_write_grayscale_display(data);
    GDEY042T81_update_grayscale_display();
    GDEY042T81_sleep();
}

////////////////////////////////////////////////////////////////////////////////
//  PARTIAL
////////////////////////////////////////////////////////////////////////////////
static void GDEY042T81_update_partial_display(void)
{
    GDEY042T81_write_cmd(0x22); //Display Update Control
    GDEY042T81_write_data(0xFF);
    GDEY042T81_write_cmd(0x20); //Activate Display Update Sequence
    GDEY042T81_wait_busy();
}

/* void EPD_Dis_PartAll(const unsigned char * datas) */
static void GDEY042T81_write_partial_display(const unsigned char * datas)
{
    unsigned int i;

    gpio_set_level(GDEY042T81_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(GDEY042T81_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(10));

    GDEY042T81_write_cmd(0x3C); //BorderWavefrom,
    GDEY042T81_write_data(0x80);

    GDEY042T81_write_cmd(0x21);
    GDEY042T81_write_data(0x00);
    GDEY042T81_write_data(0x00);

    GDEY042T81_write_cmd(0x24);
    for(i = 0; i < GDEY042T81_ARRAY; i++)
    {
        GDEY042T81_write_data(datas[i]);
    }
    /* GDEY042T81_update_partial_display(); */
}


static void EPD_SetRAMValue_BaseMap(const unsigned char *datas)
{
    unsigned int i;
    GDEY042T81_write_cmd(0x24);
    for(i = 0; i < GDEY042T81_ARRAY; i++)
    {
        GDEY042T81_write_data(datas[i]);
    }
    GDEY042T81_write_cmd(0x26);
    for(i = 0; i < GDEY042T81_ARRAY; i++)
    {
        GDEY042T81_write_data(datas[i]);
    }
}

//degager les sleep, a priori on sleep pas entre les refresh
static void GDEY042T81_display_image_partial_full(const unsigned char *data, bool base)
{
    if (base == true)
    {
        GDEY042T81_init_display();
        EPD_SetRAMValue_BaseMap(data);
        GDEY042T81_update_display();
        /* GDEY042T81_sleep(); */
        return;
    }
    else
    {
        GDEY042T81_write_partial_display(data);
        GDEY042T81_update_partial_display();
        /* GDEY042T81_sleep(); */
        return;
    }
}
