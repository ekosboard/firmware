#include "EPD.h"
#include "epd_GDEY075T7.h"
#include "epd_interface.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include <stdint.h>


static void GDEY075T7_init_driver(void);
static void GDEY075T7_sleep(void);
static void GDEY075T7_clear(void);
static void GDEY075T7_clear_fast(void);
static void GDEY075T7_clear_partial(void);
static void GDEY075T7_display_image(const unsigned char *data);
static void GDEY075T7_display_image_fast(const unsigned char *data);
static void GDEY075T7_display_image_grayscale(const unsigned char *data);
static void GDEY075T7_display_image_partial_full(const unsigned char *data, bool full_refresh);

epd_interface_t gdey075t7_driver = {
    .init = GDEY075T7_init_driver,
    .clear = GDEY075T7_clear_partial,
    .display_image = GDEY075T7_display_image,
    .display_image_fast = GDEY075T7_display_image_fast,
    .display_image_grayscale = GDEY075T7_display_image_grayscale,
    .display_image_partial = GDEY075T7_display_image_partial_full,
    .sleep = GDEY075T7_sleep
};

static spi_device_handle_t spi_handle;


static void GDEY075T7_display_image_grayscale(const unsigned char *data)
{
    return;
}

static void init_gpio()
{
    gpio_set_direction(GDEY075T7_BUSY, GPIO_MODE_INPUT);
    gpio_set_direction(GDEY075T7_RST, GPIO_MODE_OUTPUT);
    gpio_set_direction(GDEY075T7_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(GDEY075T7_CS, GPIO_MODE_OUTPUT);
}

static void init_SPI()
{
    spi_bus_config_t buscfg = {
        .miso_io_num = -1,
        .mosi_io_num = GDEY075T7_MOSI,
        .sclk_io_num = GDEY075T7_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096
    };
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 10 * 1000 * 1000,
        .mode = 0,
        .spics_io_num = GDEY075T7_CS,
        .queue_size = 7,
        .flags = 0,
    };
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &spi_handle));
}

static void GDEY075T7_init_driver(void)
{
    init_gpio();
    init_SPI();
}

static void GDEY075T7_write_cmd(unsigned char command)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &command;

    gpio_set_level(GDEY075T7_DC, 0);
    spi_device_transmit(spi_handle, &t);
}

static void GDEY075T7_write_data(unsigned char data)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &data;

    gpio_set_level(GDEY075T7_DC, 1);
    spi_device_transmit(spi_handle, &t);
}

static void GDEY075T7_wait_busy(void)
{
    while(42)
    {
        if (gpio_get_level(GDEY075T7_BUSY) == 0) break;;
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

static void GDEY075T7_sleep(void)
{
    GDEY075T7_write_cmd(0x02); // power off
    GDEY075T7_wait_busy();

    GDEY075T7_write_cmd(0x07); // deep sleep
    GDEY075T7_write_data(0xA5);

    vTaskDelay(pdMS_TO_TICKS(10));
}

static void GDEY075T7_update_display(void)
{
    GDEY075T7_write_cmd(0x12);
    vTaskDelay(pdMS_TO_TICKS(1));
    GDEY075T7_wait_busy();
}


////////////////////////////////////////////////////////////////////////////////
// Full screen update initialization
////////////////////////////////////////////////////////////////////////////////
static void GDEY075T7_init_display(void)
{

    gpio_set_level(GDEY075T7_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(GDEY075T7_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(10));

    GDEY075T7_write_cmd(0x04); // POWER ON
    GDEY075T7_wait_busy();

    GDEY075T7_write_cmd(0X00); // PANNEL SETTING
    GDEY075T7_write_data(0x1f); // KW-3f KWR-2F BWROTP 0f BWOTP 1f

    GDEY075T7_write_cmd(0x01); // POWER SETTING
    GDEY075T7_write_data(0x07);
    GDEY075T7_write_data(0x07); // VGH=20V,VGL=-20V
    GDEY075T7_write_data(0x3f); // VDH=15V
    GDEY075T7_write_data(0x3f); // VDL=-15V
    GDEY075T7_write_data(0x09); // VDHR=4.2V

    //Enhanced display drive
    GDEY075T7_write_cmd(0x06); //Booster Soft Start
    GDEY075T7_write_data(0x17);
    GDEY075T7_write_data(0x17);
    GDEY075T7_write_data(0x28);
    GDEY075T7_write_data(0x17);

    GDEY075T7_write_cmd(0x61); // tres
    GDEY075T7_write_data(0x03); // source 800
    GDEY075T7_write_data(0x20);
    GDEY075T7_write_data(0x01); // gate 480
    GDEY075T7_write_data(0xE0);

    GDEY075T7_write_cmd(0X15); // DUSPI
    GDEY075T7_write_data(0x00); // disabled

    GDEY075T7_write_cmd(0X50); // VCOM AND DATA INTERVAL SETTING
    GDEY075T7_write_data(0x29); // LUTKW, N2OCP: copy new to old
    GDEY075T7_write_data(0x07); // CDI 10hsynch (default)

    GDEY075T7_write_cmd(0X60); // TCON SETTING
    GDEY075T7_write_data(0x22); // S2G G2S, 12 (default)

    GDEY075T7_write_cmd(0xE3); // PWS
    GDEY075T7_write_data(0x22); // VCOM 2 line period, Source 2 * 660ns

    GDEY075T7_write_cmd(0x04); // POWER ON
    vTaskDelay(pdMS_TO_TICKS(100));
    GDEY075T7_wait_busy();
}


 /* Display full screen */
static void GDEY075T7_write_display(const unsigned char *datas)
{
    uint16_t i;
    GDEY075T7_write_cmd(0x10); // write old data
    for(i = 0; i < EPD_ARRAY; i++)
    {
        GDEY075T7_write_data(0x00);
    }
    GDEY075T7_write_cmd(0x13); // write new data
    for(i = 0; i < EPD_ARRAY; i++)
    {
        GDEY075T7_write_data(datas[i]);
    }
}

//Clear screen display
static void GDEY075T7_write_clear(void)
{
    uint16_t i;
    GDEY075T7_write_cmd(0x10); // write old data
    for(i = 0; i < EPD_ARRAY; i++)
    {
        GDEY075T7_write_data(0xff);
    }
    GDEY075T7_write_cmd(0x13); //write new data
    for(i = 0; i < EPD_ARRAY; i++)
    {
        GDEY075T7_write_data(0xff);
    }
}

static void GDEY075T7_clear(void)
{
    GDEY075T7_init_display();
    GDEY075T7_write_clear();
    GDEY075T7_update_display();
    GDEY075T7_sleep();
}

static void GDEY075T7_display_image(const unsigned char *data)
{
    GDEY075T7_init_display();
    GDEY075T7_write_display(data);
    GDEY075T7_update_display();
    GDEY075T7_sleep();
}

////////////////////////////////////////////////////////////////////////////////
//  FAST
////////////////////////////////////////////////////////////////////////////////
static void GDEY075T7_init_fast_display(void)
{
    GDEY075T7_write_cmd(0xE0);
    GDEY075T7_write_data(0x02);
    GDEY075T7_write_cmd(0xE5);
    GDEY075T7_write_data(0x5A);
}

static void GDEY075T7_clear_fast(void)
{
    GDEY075T7_init_display();
    GDEY075T7_init_fast_display();
    GDEY075T7_write_clear();
    GDEY075T7_update_display();
    GDEY075T7_sleep();
}

static void GDEY075T7_display_image_fast(const unsigned char *data)
{
    GDEY075T7_init_display();
    GDEY075T7_init_fast_display();
    GDEY075T7_write_display(data);
    GDEY075T7_update_display();
    GDEY075T7_sleep();
}

////////////////////////////////////////////////////////////////////////////////
//  PARTIAL
////////////////////////////////////////////////////////////////////////////////
static void GDEY075T7_init_partial_display(void)
{
    GDEY075T7_write_cmd(0xE0);
    GDEY075T7_write_data(0x02);
    GDEY075T7_write_cmd(0xE5);
    GDEY075T7_write_data(0x6E);
}

//Partial update display
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
    uint16_t x_end;
    uint16_t y_end;

    x_end = x_start + PART_LINE - 1;
    y_end = y_start + PART_COLUMN - 1;

    GDEY075T7_write_cmd(0x91); // partial in
    GDEY075T7_write_cmd(0x90); // resolution setting

    GDEY075T7_write_data (x_start / 256);
    GDEY075T7_write_data (x_start % 256); // x-start

    GDEY075T7_write_data (x_end / 256);
    GDEY075T7_write_data (x_end % 256 - 1);// x-end

    GDEY075T7_write_data (y_start / 256);
    GDEY075T7_write_data (y_start % 256); // y-start

    GDEY075T7_write_data (y_end / 256);
    GDEY075T7_write_data (y_end % 256 - 1); // y-end
    GDEY075T7_write_data (0x01);

    GDEY075T7_write_cmd(0x13); // write new data
    for(uint16_t i = 0; i < PART_COLUMN * PART_LINE / 8; i++)
    {
        GDEY075T7_write_data(datas[i]);
    }
}

//Full screen partial update display
void EPD_Dis_PartAll(const unsigned char * datas)
{
    uint16_t x_start = 0;
    uint16_t y_start = 0;
    uint16_t x_end;
    uint16_t y_end;

    x_end = x_start + EPD_WIDTH - 1;
    y_end = y_start + EPD_HEIGHT - 1;

    GDEY075T7_write_cmd(0x91); // partial in
    GDEY075T7_write_cmd(0x90); // resolution setting
    GDEY075T7_write_data (x_start / 256);
    GDEY075T7_write_data (x_start % 256); // x-start

    GDEY075T7_write_data (x_end / 256);
    GDEY075T7_write_data (x_end % 256 - 1); // x-end

    GDEY075T7_write_data (y_start / 256);
    GDEY075T7_write_data (y_start % 256); // y-start

    GDEY075T7_write_data (y_end / 256);
    GDEY075T7_write_data (y_end % 256-1); // y-end
    GDEY075T7_write_data (0x01);

    GDEY075T7_write_cmd(0x13); // write new data
    for(uint16_t i = 0; i < EPD_ARRAY; i++)
    {
        GDEY075T7_write_data(datas[i]);
    }
    GDEY075T7_write_cmd(0x92); // partial out
}


static bool force_full_refresh = false;

static void GDEY075T7_clear_partial(void)
{
    GDEY075T7_init_display();
    GDEY075T7_write_clear();
    GDEY075T7_update_display();
    GDEY075T7_sleep();
    force_full_refresh = true;
}

static void GDEY075T7_display_image_partial_full(const unsigned char *data, bool full_refresh)
{
    GDEY075T7_init_display();

    if (force_full_refresh || full_refresh)
    {
        force_full_refresh = false;
        GDEY075T7_init_fast_display();
        GDEY075T7_write_display(data);
        GDEY075T7_update_display();
        return;
    }
    else
    {
        GDEY075T7_init_partial_display();
        EPD_Dis_PartAll(data);
        GDEY075T7_update_display();
        return;
    }

    GDEY075T7_sleep();
}

////////////////////////////////////////////////////////////////////////////////
//  GRAYSCALE (NOT TESTED)
////////////////////////////////////////////////////////////////////////////////
// 4 Gray display
void EPD_Init_4G(void)
{
    gpio_set_level(GDEY075T7_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(GDEY075T7_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(10));

    GDEY075T7_write_cmd(0X00); // PANNEL SETTING
    GDEY075T7_write_data(0x1F); //KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f

    GDEY075T7_write_cmd(0X50); // VCOM AND DATA INTERVAL SETTING
    GDEY075T7_write_data(0x10);
    GDEY075T7_write_data(0x07);

    GDEY075T7_write_cmd(0x04); // POWER ON
    vTaskDelay(pdMS_TO_TICKS(10)); //FIXME: 10 ici alors que 100 ailleurs
    GDEY075T7_wait_busy();

    //Enhanced display drive(Add 0x06 command)
    GDEY075T7_write_cmd(0x06);			//Booster Soft Start
    GDEY075T7_write_data (0x27);
    GDEY075T7_write_data (0x27);
    GDEY075T7_write_data (0x18);
    GDEY075T7_write_data (0x17);

    GDEY075T7_write_cmd(0xE0);
    GDEY075T7_write_data(0x02);
    GDEY075T7_write_cmd(0xE5);
    GDEY075T7_write_data(0x5F); //0x5A--1.5s, 0x5F--4 Gray

}

void EPD_WhiteScreen_ALL_4G (const unsigned char *datas)
{
    unsigned int i,j,k;
    unsigned char temp1,temp2,temp3;

    //old  data
    GDEY075T7_write_cmd(0x10);

    for(i=0;i<48000;i++)	               //48000*2  800*480
    { 
        temp3=0;
        for(j=0;j<2;j++)	
        {
            temp1 = datas[i*2+j];
            for(k=0;k<4;k++)
            {
                temp2 = temp1&0xC0 ;
                if(temp2 == 0xC0)
                    temp3 |= 0x01;//white
                else if(temp2 == 0x00)
                    temp3 |= 0x00;  //black
                else if((temp2>=0x80)&&(temp2<0xC0)) 
                    temp3 |= 0x00;  //gray1
                else if(temp2 == 0x40)
                    temp3 |= 0x01; //gray2
                if((j==0&&k<=3)||(j==1&&k<=2))
                {
                    temp3 <<= 1;	
                    temp1 <<= 2;
                }
            }
        }	
        GDEY075T7_write_data(~temp3);			
    }

    //new  data
    GDEY075T7_write_cmd(0x13);	       
    for(i=0;i<48000*2;i++)	               //48000*2   800*480
    { 
        temp3=0;
        for(j=0;j<2;j++)	
        {
            temp1 = datas[i*2+j];
            for(k=0;k<4;k++)
            {
                temp2 = temp1&0xC0 ;
                if(temp2 == 0xC0)
                    temp3 |= 0x01;//white
                else if(temp2 == 0x00)
                    temp3 |= 0x00;  //black
                else if((temp2>=0x80)&&(temp2<0xC0)) 
                    temp3 |= 0x01;  //gray1
                else if(temp2 == 0x40)
                    temp3 |= 0x00; //gray2

                if((j==0&&k<=3)||(j==1&&k<=2))
                {
                    temp3 <<= 1;	
                    temp1 <<= 2;
                }
            }	
        }
        GDEY075T7_write_data(~temp3);			
    }
}




void Display_4Level_Gray(void)
{
    unsigned int i; 

    GDEY075T7_wait_busy();
    GDEY075T7_write_cmd(0x10);   

    for(i=0;i<800*480/16/2;i++)
    {
        GDEY075T7_write_data(0x00);
    }

    for(i=0;i<800*480/16/2;i++)
    {
        GDEY075T7_write_data(0xFF);
    }

    for(i=0;i<800*480/16/2;i++)
    {
        GDEY075T7_write_data(0x00);
    }

    for(i=0;i<800*480/16/2;i++)
    {
        GDEY075T7_write_data(0xFF);
    }

    GDEY075T7_wait_busy();
    GDEY075T7_write_cmd(0x13);   

    for(i=0;i<800*480/16/2;i++)
    {
        GDEY075T7_write_data(0x00);
    }

    for(i=0;i<800*480/16/2;i++)
    {
        GDEY075T7_write_data(0x00);
    }

    for(i=0;i<800*480/16/2;i++)
    {
        GDEY075T7_write_data(0xFF);
    }

    for(i=0;i<800*480/16/2;i++)
    {
        GDEY075T7_write_data(0xFF);
    }
}

