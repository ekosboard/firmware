#include "EPD.h"
#include "epd_WS073F.h"
#include "epd_interface.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include <stdint.h>

static void WS073F_init_driver(void);
static void WS073F_sleep(void);
static void WS073F_clear(void);
static void WS073F_display_image(const unsigned char *data);
static void WS073F_display_image_fast(const unsigned char *data);
static void WS073F_display_image_grayscale(const unsigned char *data);
static void WS073F_display_image_partial(const unsigned char *data, bool full_refresh);

static void WS073F_clear_screen(const unsigned char color);
static void EPD_7IN3F_Display(const unsigned char *data);

epd_interface_t ws073f_driver = {
    .init = WS073F_init_driver,
    .clear = WS073F_clear,
    .display_image = WS073F_display_image,
    .display_image_fast = WS073F_display_image_fast,
    .display_image_grayscale = WS073F_display_image_grayscale,
    .display_image_partial = WS073F_display_image_partial,
    .sleep = WS073F_sleep
};

static spi_device_handle_t spi_handle;

static void init_gpio()
{
    gpio_set_direction(WS073F_BUSY, GPIO_MODE_INPUT);
    gpio_set_direction(WS073F_RST, GPIO_MODE_OUTPUT);
    gpio_set_direction(WS073F_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(WS073F_CS, GPIO_MODE_OUTPUT);
}

static void init_SPI()
{
    spi_bus_config_t buscfg = {
        .miso_io_num = -1,
        .mosi_io_num = WS073F_MOSI,
        .sclk_io_num = WS073F_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096
    };
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 10 * 1000 * 1000,
        .mode = 0,
        .spics_io_num = WS073F_CS,
        .queue_size = 7,
        .flags = 0,
    };
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &spi_handle));
}

static void WS073F_init_driver(void)
{
    init_gpio();
    init_SPI();
    init_epd_event_group();
}

static void WS073F_write_cmd(unsigned char command)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &command;

    gpio_set_level(WS073F_DC, 0);
    spi_device_transmit(spi_handle, &t);
}

static void WS073F_write_data(unsigned char data)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &data;

    gpio_set_level(WS073F_DC, 1);
    spi_device_transmit(spi_handle, &t);
}

static void WS073F_wait_busy(void)
{
    while(42)
    {
        if (gpio_get_level(WS073F_BUSY) == 0) break;;
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

/******************************************************************************
function :  Initialize the e-Paper register
parameter:
******************************************************************************/
static void WS073F_init_display(void)
{
    gpio_set_level(WS073F_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(20));
    gpio_set_level(WS073F_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(1));
    gpio_set_level(WS073F_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(20));

    WS073F_wait_busy();

    WS073F_write_cmd(0xAA);    // CMDH
    WS073F_write_data(0x49);
    WS073F_write_data(0x55);
    WS073F_write_data(0x20);
    WS073F_write_data(0x08);
    WS073F_write_data(0x09);
    WS073F_write_data(0x18);

    WS073F_write_cmd(0x01);
    WS073F_write_data(0x3F);
    WS073F_write_data(0x00);
    WS073F_write_data(0x32);
    WS073F_write_data(0x2A);
    WS073F_write_data(0x0E);
    WS073F_write_data(0x2A);

    WS073F_write_cmd(0x00);
    WS073F_write_data(0x5F);
    WS073F_write_data(0x69);

    WS073F_write_cmd(0x03);
    WS073F_write_data(0x00);
    WS073F_write_data(0x54);
    WS073F_write_data(0x00);
    WS073F_write_data(0x44);

    WS073F_write_cmd(0x05);
    WS073F_write_data(0x40);
    WS073F_write_data(0x1F);
    WS073F_write_data(0x1F);
    WS073F_write_data(0x2C);

    WS073F_write_cmd(0x06);
    WS073F_write_data(0x6F);
    WS073F_write_data(0x1F);
    WS073F_write_data(0x1F);
    WS073F_write_data(0x22);

    WS073F_write_cmd(0x08);
    WS073F_write_data(0x6F);
    WS073F_write_data(0x1F);
    WS073F_write_data(0x1F);
    WS073F_write_data(0x22);

    WS073F_write_cmd(0x13);    // IPC
    WS073F_write_data(0x00);
    WS073F_write_data(0x04);

    WS073F_write_cmd(0x30);
    WS073F_write_data(0x3C);

    WS073F_write_cmd(0x41);     // TSE
    WS073F_write_data(0x00);

    WS073F_write_cmd(0x50);
    WS073F_write_data(0x3F);

    WS073F_write_cmd(0x60);
    WS073F_write_data(0x02);
    WS073F_write_data(0x00);

    WS073F_write_cmd(0x61);
    WS073F_write_data(0x03);
    WS073F_write_data(0x20);
    WS073F_write_data(0x01);
    WS073F_write_data(0xE0);

    WS073F_write_cmd(0x82);
    WS073F_write_data(0x1E);

    WS073F_write_cmd(0x84);
    WS073F_write_data(0x00);

    WS073F_write_cmd(0x86);    // AGID
    WS073F_write_data(0x00);

    WS073F_write_cmd(0xE3);
    WS073F_write_data(0x2F);

    WS073F_write_cmd(0xE0);   // CCSET
    WS073F_write_data(0x00);

    WS073F_write_cmd(0xE6);   // TSSET
    WS073F_write_data(0x00);
}


static void WS073F_turn_on(void) {
    WS073F_write_cmd(0x04);  // POWER_ON
    WS073F_wait_busy();

    WS073F_write_cmd(0x12);  // DISPLAY_REFRESH
    WS073F_write_data(0x00);
    WS073F_wait_busy();

    WS073F_write_cmd(0x02);  // POWER_OFF
    WS073F_write_data(0x00);
    WS073F_wait_busy();
}

static void WS073F_display_image(const unsigned char *data)
{
    WS073F_init_display();
    EPD_7IN3F_Display(data);
    WS073F_sleep();
    set_epd_event(EPD_EVENT_FLUSH_COMPLETE);
}

static void WS073F_display_image_fast(const unsigned char *data)
{
    // Pas de mode fast sur ce panel → fallback
    WS073F_display_image(data);
}

static void WS073F_display_image_grayscale(const unsigned char *data)
{
    // Pas supporté → fallback
    WS073F_display_image(data);
}

static void WS073F_display_image_partial(const unsigned char *data, bool full_refresh)
{
    // Pas supporté → fallback
    WS073F_display_image(data);
}

static void WS073F_clear(void)
{
    WS073F_init_display();
    WS073F_clear_screen(EPD_7IN3F_WHITE);
    WS073F_sleep();
}
/******************************************************************************
function :  Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
static void EPD_7IN3F_Display(const unsigned char *data)
{
    unsigned long i,j;

    WS073F_write_cmd(0x10);
    for(i = 0; i < WS073F_HEIGHT; i++)
    {
        for(j = 0; j < WS073F_WIDTH / 2; j++)
        {
            WS073F_write_data(data[j + WS073F_WIDTH * i]); //XXX
        }
    }

    WS073F_turn_on();
}

/******************************************************************************
function :  Sends the part image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
static void EPD_7IN3F_Display_part(const unsigned char *image,
        unsigned int xstart,
        unsigned int ystart,
        unsigned int image_width,
        unsigned int image_heigh)
{
    unsigned long i, j;

    WS073F_write_cmd(0x10);
    for (i = 0; i < WS073F_HEIGHT; i++)
    {
        for (j = 0; j < WS073F_WIDTH / 2; j++)
        {
            if (i < image_heigh + ystart \
                    && i >= ystart \
                    && j < (image_width + xstart) / 2 \
                    && j >= xstart / 2)
            {
                WS073F_write_data(image[(j - xstart / 2) + (image_width / 2*(i - ystart))]);
            }
            else
            {
                WS073F_write_data(0x11);
            }
        }
    }

    WS073F_turn_on();
}

/******************************************************************************
function :  show 7 kind of color block
parameter:
******************************************************************************/
static void EPD_7IN3F_Show7Block(void)
{
    unsigned long i, j, k;
    unsigned char const Color_seven[8] =
    {EPD_7IN3F_BLACK, EPD_7IN3F_BLUE, EPD_7IN3F_GREEN, EPD_7IN3F_ORANGE,
    EPD_7IN3F_RED, EPD_7IN3F_YELLOW, EPD_7IN3F_WHITE, EPD_7IN3F_WHITE};

    WS073F_write_cmd(0x10);
    for (i = 0; i < 240; i++)
    {
        for (k = 0; k < 4; k++)
        {
            for (j = 0; j < 100; j++)
            {
                WS073F_write_data((Color_seven[k]<<4) |Color_seven[k]);
            }
        }
    }

    for (i = 0; i < 240; i++)
    {
        for (k = 4; k < 8; k++)
        {
            for (j = 0; j < 100; j++)
            {
                WS073F_write_data((Color_seven[k]<<4) |Color_seven[k]);
            }
        }
    }

    WS073F_turn_on();
}

/******************************************************************************
function :
      Clear screen
******************************************************************************/
static void WS073F_clear_screen(const unsigned char color)
{
    WS073F_write_cmd(0x10);
    for (int i = 0; i < WS073F_WIDTH / 2; i++)
    {
        for (int j = 0; j < WS073F_HEIGHT; j++)
        {
            WS073F_write_data((color << 4) | color);
        }
    }

    WS073F_turn_on();
}

/**
 *  @brief: After this command is transmitted, the chip would enter the
 *          deep-sleep mode to save power.
 *          The deep sleep mode would return to standby by hardware reset.
 *          The only one parameter is a check code, the command would be
 *          You can use EPD_Reset() to awaken
 */
static void WS073F_sleep(void)
{
    WS073F_write_cmd(0x07);
    WS073F_write_data(0xA5);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(WS073F_RST, 0);
}
