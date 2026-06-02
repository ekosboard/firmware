#include "EPD.h"
#include "epd_GDEY075T7.h"
#include "epd_interface.h"
#include "esp_log.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include <stdint.h>
#include <inttypes.h>


static void GDEY075T7_init_driver(void);
static void GDEY075T7_sleep(void);
static void GDEY075T7_clear(void);
static void GDEY075T7_clear_fast(void);
static void GDEY075T7_clear_partial(void);
static void GDEY075T7_display_image(const unsigned char *data);
static void GDEY075T7_display_image_fast(const unsigned char *data);
static void GDEY075T7_display_image_grayscale(const unsigned char *data);
static void GDEY075T7_display_image_partial_full(const unsigned char *data, bool full_refresh);
static void GDEY075T7_set_ram_basemap(const unsigned char *data);
static void GDEY075T7_close_session(void);

static void GDEY075T7_display_image_area(const unsigned char *data, uint32_t x, uint32_t y, uint32_t w, uint32_t h);

epd_interface_t gdey075t7_driver = {
    .init = GDEY075T7_init_driver,
    .clear = GDEY075T7_clear_partial,
    .display_image = GDEY075T7_display_image,
    .display_image_fast = GDEY075T7_display_image_fast,
    .display_image_grayscale = GDEY075T7_display_image_grayscale,
    .display_image_partial = GDEY075T7_display_image_partial_full,
    .display_image_area = GDEY075T7_display_image_area,
    .set_basemap = GDEY075T7_set_ram_basemap,
    .sleep = GDEY075T7_close_session,
};

static spi_device_handle_t spi_handle;

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
    init_epd_event_group();
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

static void GDEY075T7_write_data_buf(const uint8_t *data, size_t len)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));

    t.length = len * 8;   // longueur en bits
    t.tx_buffer = data;

    gpio_set_level(GDEY075T7_DC, 1); // DATA
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

static void GDEY075T7_close_session(void)
{
    GDEY075T7_sleep();
}

static void GDEY075T7_sleep(void)
{
    GDEY075T7_write_cmd(0x50);
    GDEY075T7_write_data(0xF7);

    GDEY075T7_write_cmd(0x02); // power off
    GDEY075T7_wait_busy();

    GDEY075T7_write_cmd(0x07); // deep sleep
    GDEY075T7_write_data(0xA5);

    vTaskDelay(pdMS_TO_TICKS(10));
}

static void GDEY075T7_update_display(void)
{
    ESP_LOGI("GDEY075T7", "update_display");
    GDEY075T7_write_cmd(0x12);
    vTaskDelay(pdMS_TO_TICKS(5));
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

    GDEY075T7_write_cmd(0x01); // POWER SETTING
    GDEY075T7_write_data(0x07);
    GDEY075T7_write_data(0x07); // VGH=20V,VGL=-20V
    GDEY075T7_write_data(0x3f); // VDH=15V
    GDEY075T7_write_data(0x3f); // VDL=-15V
    GDEY075T7_write_data(0x03); // VDHR=4.2V

    //Enhanced display drive
    GDEY075T7_write_cmd(0x06); //Booster Soft Start
    GDEY075T7_write_data(0x27);
    GDEY075T7_write_data(0x27);
    GDEY075T7_write_data(0x18);
    GDEY075T7_write_data(0x17);

    GDEY075T7_write_cmd(0x04); // POWER ON
    vTaskDelay(pdMS_TO_TICKS(100));
    GDEY075T7_wait_busy();

    GDEY075T7_write_cmd(0X00); // PANNEL SETTING
    GDEY075T7_write_data(0x1f); // KW-3f KWR-2F BWROTP 0f BWOTP 1f

    GDEY075T7_write_cmd(0x61); // tres
    GDEY075T7_write_data(0x03); // source 800
    GDEY075T7_write_data(0x20);
    GDEY075T7_write_data(0x01); // gate 480
    GDEY075T7_write_data(0xE0);

    GDEY075T7_write_cmd(0X15); // DUSPI
    GDEY075T7_write_data(0x00); // disabled

    /* GDEY075T7_write_cmd(0X50);     //VCOM AND DATA INTERVAL SETTING */
    /* GDEY075T7_write_data(0x10); */
    /* GDEY075T7_write_data(0x07); */

    GDEY075T7_write_cmd(0X50); // VCOM AND DATA INTERVAL SETTING
    GDEY075T7_write_data(0x29);//29 // LUTKW, N2OCP: copy new to old
    GDEY075T7_write_data(0x07); // CDI 10hsynch (default)

    GDEY075T7_write_cmd(0X60); // TCON SETTING
    GDEY075T7_write_data(0x22); // S2G G2S, 12 (default)

    GDEY075T7_write_cmd(0xE3); // PWS
    GDEY075T7_write_data(0x22); // VCOM 2 line period, Source 2 * 660ns

    /* GDEY075T7_write_cmd(0x82); */
    /* GDEY075T7_write_data(0x1A); */
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
        GDEY075T7_write_data(0x00);
    }
    GDEY075T7_write_cmd(0x13); //write new data
    for(i = 0; i < EPD_ARRAY; i++)
    {
        GDEY075T7_write_data(0x00);
    }
}

static void GDEY075T7_clear_basemap(void)
{
    uint16_t i;
    GDEY075T7_write_cmd(0x10); // write old data
    for(i = 0; i < EPD_ARRAY; i++)
    {
        GDEY075T7_write_data(0xFF); //blanc
    }
    GDEY075T7_write_cmd(0x13); //write new data
    for(i = 0; i < EPD_ARRAY; i++)
    {
        GDEY075T7_write_data(0x00); //noir
    }
}

static void GDEY075T7_set_basemap(const unsigned char *data)
{
    // DTM1 = 0xFF (requis par la waveform partial)
    GDEY075T7_write_cmd(0x10);
    for(uint16_t i = 0; i < EPD_ARRAY; i++)
        GDEY075T7_write_data(0xFF);

    // DTM2 = image
    GDEY075T7_write_cmd(0x13);
    for(uint16_t i = 0; i < EPD_ARRAY; i++)
        GDEY075T7_write_data(data[i]);
}

static void GDEY075T7_clear(void)
{
    GDEY075T7_init_display();
    GDEY075T7_write_clear();
    GDEY075T7_update_display();
    GDEY075T7_sleep();
    /* vTaskDelay(pdMS_TO_TICKS(3000)); */
}

static void GDEY075T7_display_image(const unsigned char *data)
{
    GDEY075T7_init_display();
    GDEY075T7_write_display(data);
    GDEY075T7_update_display();
    GDEY075T7_sleep();
    /* vTaskDelay(pdMS_TO_TICKS(3000)); */
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
    vTaskDelay(pdMS_TO_TICKS(1500));
}

static void GDEY075T7_display_image_fast(const unsigned char *data)
{
    GDEY075T7_init_display();
    GDEY075T7_init_fast_display();
    GDEY075T7_write_display(data);
    GDEY075T7_update_display();
    GDEY075T7_sleep();
    vTaskDelay(pdMS_TO_TICKS(1500));
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

static void EPD_Dis_Part(uint32_t x, uint32_t y, const uint8_t *data, uint32_t h, uint32_t w)
{
    // En I1, 1 bit par pixel, largeur écran en octets
    const uint32_t stride = EPD_WIDTH / 8;  // 800/8 = 100 octets par ligne

    // Offset vers le premier octet de la zone dans le framebuffer complet
    // x doit être aligné sur 8 bits pour I1
    const uint32_t x_byte = x / 8;
    const uint32_t w_bytes = w / 8;
    const uint32_t offset = (y * stride) + x_byte;
    const unsigned char *zone_data = data + offset;

    // Envoyer ligne par ligne car les données ne sont pas contiguës
    uint16_t x_end = x + w - 1;
    uint16_t y_end = y + h - 1;

    GDEY075T7_write_cmd(0x50);
    GDEY075T7_write_data(0xA9);
    GDEY075T7_write_data(0x07);

    GDEY075T7_write_cmd(0x91); // partial in
    GDEY075T7_write_cmd(0x90); // resolution setting
    GDEY075T7_write_data(x / 256);
    GDEY075T7_write_data(x % 256);
    GDEY075T7_write_data(x_end / 256);
    GDEY075T7_write_data(x_end % 256 - 1);
    GDEY075T7_write_data(y / 256);
    GDEY075T7_write_data(y % 256);
    GDEY075T7_write_data(y_end / 256);
    GDEY075T7_write_data(y_end % 256 - 1);
    GDEY075T7_write_data(0x01);

    GDEY075T7_write_cmd(0x13);
    for(uint32_t line = 0; line < h; line++)
    {
        const unsigned char *line_data = zone_data + (line * stride);
        for(uint32_t col = 0; col < w_bytes; col++)
            GDEY075T7_write_data(line_data[col]);
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

    /* GDEY075T7_write_cmd(0x10); // old data */
    /* for (uint16_t i = 0; i < EPD_ARRAY; i++) */
    /* { */
    /*     /1* GDEY075T7_write_data(~datas[i]); // Inversion binaire pour forcer un changement *1/ */
    /*     GDEY075T7_write_data(0x00); // Inversion binaire pour forcer un changement */
    /* } */

    GDEY075T7_write_cmd(0x50);
    /* GDEY075T7_write_data(0x21); // N2OCP disabled */
    GDEY075T7_write_data(0xA9);
    GDEY075T7_write_data(0x07);

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
}

static bool force_full_refresh = false;

static void GDEY075T7_clear_partial(void)
{
    GDEY075T7_init_display();
    GDEY075T7_clear_basemap();
    GDEY075T7_update_display();
    GDEY075T7_sleep();
    force_full_refresh = true;
    vTaskDelay(pdMS_TO_TICKS(500));
}

static void GDEY075T7_display_image_partial_full(const unsigned char *data, bool full_refresh)
{
    GDEY075T7_init_display();

    if (force_full_refresh || full_refresh)
    {
        force_full_refresh = false;
        GDEY075T7_init_fast_display();
        GDEY075T7_init_partial_display();
        GDEY075T7_write_display(data);
        EPD_Dis_PartAll(data);
        GDEY075T7_update_display();
        GDEY075T7_write_cmd(0x92);
    }
    else
    {
        GDEY075T7_init_partial_display();
        EPD_Dis_PartAll(data);
        GDEY075T7_update_display();
        GDEY075T7_write_cmd(0x92);
    }

    GDEY075T7_sleep();
    vTaskDelay(pdMS_TO_TICKS(500));
}

static void GDEY075T7_set_ram_basemap(const unsigned char *data)
{
    const uint8_t *fb = data + 8; // skip header LVGL comme dans flush

    GDEY075T7_init_display();

    // OLD data = ce qui était affiché
    GDEY075T7_write_cmd(0x10);
    for (int i = 0; i < EPD_ARRAY; i++)
        GDEY075T7_write_data(fb[i]);

    // NEW data = identique
    GDEY075T7_write_cmd(0x13);
    for (int i = 0; i < EPD_ARRAY; i++)
        GDEY075T7_write_data(fb[i]);

    // Pas d'update_display — on restaure juste la RAM
    ESP_LOGI("EPD", "Basemap restored after wakeup");
}

static void GDEY075T7_display_image_area(const unsigned char *data,
        uint32_t x, uint32_t y,
        uint32_t w, uint32_t h)
{
    GDEY075T7_init_display();
    GDEY075T7_init_partial_display();
    EPD_Dis_Part(x, y, data, h, w);
    GDEY075T7_update_display();
    GDEY075T7_write_cmd(0x92);
    vTaskDelay(pdMS_TO_TICKS(300));
}

////////////////////////////////////////////////////////////////////////////////
//  GRAYSCALE (NOT TESTED)
////////////////////////////////////////////////////////////////////////////////
// full screen update LUT 0~3 gray
const unsigned char lut_20_vcom0_4G[] =
{
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x01,
    0x60, 0x14, 0x14, 0x00, 0x00, 0x01,
    0x00, 0x14, 0x0A, 0x00, 0x00, 0x01,
    0x00, 0x13, 0x0A, 0x01, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//R21 white: o-n: 1-1
const unsigned char lut_21_ww_4G[] =
{ // 10 w
  0x40, 0x0A, 0x00, 0x00, 0x00, 0x01, // 01 00 00 00
  0x90, 0x14, 0x14, 0x00, 0x00, 0x01, // 10 01 00 00
  0x10, 0x14, 0x0A, 0x00, 0x00, 0x01, // 00 01 00 00
  0xA0, 0x13, 0x0A, 0x00, 0x00, 0x01, // 10 10 00 00
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R22H light grey: o-n: 0-1
const unsigned char lut_22_bw_4G[] =
{ // 10 w
  0x40, 0x0A, 0x00, 0x00, 0x00, 0x01, // 01 00 00 00
  0x90, 0x14, 0x14, 0x00, 0x00, 0x01, // 10 01 00 00
  0x00, 0x14, 0x0A, 0x00, 0x00, 0x01, // 00 00 00 00
  0x99, 0x0C, 0x01, 0x03, 0x04, 0x01, // 10 01 10 01
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R23H dark grey: o-n: 1-0
const unsigned char lut_23_wb_4G[] =
{ // 01 b
  0x40, 0x0A, 0x00, 0x00, 0x00, 0x01, // 01 00 00 00
  0x90, 0x14, 0x14, 0x00, 0x00, 0x01, // 10 01 00 00
  0x00, 0x14, 0x0A, 0x00, 0x00, 0x01, // 00 00 00 00
  0x99, 0x0B, 0x04, 0x04, 0x01, 0x01, // 10 01 10 01
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R24H black: o-n: 0-0
const unsigned char lut_24_bb_4G[] =
{ // 01 b
  0x80, 0x0A, 0x00, 0x00, 0x00, 0x01, // 10 00 00 00
  0x90, 0x14, 0x14, 0x00, 0x00, 0x01, // 10 01 00 00
  0x20, 0x14, 0x0A, 0x00, 0x00, 0x01, // 00 10 00 00
  0x50, 0x13, 0x01, 0x00, 0x00, 0x01, // 01 01 00 00
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// 4 Gray display
void EPD_Init_4G(void)
{
    ESP_LOGI("GDEY075T7", "EPD_Init_4G");
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

static void GDEY075T7_init_display_grayscale(void)
{

    gpio_set_level(GDEY075T7_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(GDEY075T7_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(10));

    GDEY075T7_write_cmd(0x01); // POWER SETTING
    GDEY075T7_write_data(0x07);
    GDEY075T7_write_data(0x07); // VGH=20V,VGL=-20V
    GDEY075T7_write_data(0x3f); // VDH=15V
    GDEY075T7_write_data(0x3f); // VDL=-15V
    GDEY075T7_write_data(0x09); //3 // VDHR=4.2V

    //Enhanced display drive
    GDEY075T7_write_cmd(0x06); //Booster Soft Start
    GDEY075T7_write_data(0x17);
    GDEY075T7_write_data(0x17);
    GDEY075T7_write_data(0x28);
    GDEY075T7_write_data(0x17);

    GDEY075T7_write_cmd(0x04); // POWER ON
    vTaskDelay(pdMS_TO_TICKS(100));
    GDEY075T7_wait_busy();

    GDEY075T7_write_cmd(0X00); // PANNEL SETTING
    GDEY075T7_write_data(0x3f); // KW-3f KWR-2F BWROTP 0f BWOTP 1f

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

    GDEY075T7_write_cmd(0x82);
    GDEY075T7_write_data(0x30);

    GDEY075T7_write_cmd(0x20);
    GDEY075T7_write_data_buf(lut_20_vcom0_4G, sizeof(lut_20_vcom0_4G));
    GDEY075T7_write_cmd(0x21);
    GDEY075T7_write_data_buf(lut_21_ww_4G, sizeof(lut_21_ww_4G));
    GDEY075T7_write_cmd(0x22);
    GDEY075T7_write_data_buf(lut_22_bw_4G, sizeof(lut_22_bw_4G));
    GDEY075T7_write_cmd(0x23);
    GDEY075T7_write_data_buf(lut_23_wb_4G, sizeof(lut_23_wb_4G));
    GDEY075T7_write_cmd(0x24);
    GDEY075T7_write_data_buf(lut_24_bb_4G, sizeof(lut_24_bb_4G));
    GDEY075T7_write_cmd(0x25);
    GDEY075T7_write_data_buf(lut_21_ww_4G, sizeof(lut_21_ww_4G));

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

    for (i = 0; i < 48000; i++)	               //48000*2  800*480
    { 
        temp3 = 0;
        for (j = 0; j < 2; j++)
        {
            temp1 = datas[i * 2 + j];
            for (k = 0; k < 4; k++)
            {
                temp2 = temp1 & 0xC0;
                if (temp2 == 0xC0)
                    temp3 |= 0x00;//white
                else if (temp2 == 0x00)
                    temp3 |= 0x01;  //black
                else if ((temp2 >= 0x80) && (temp2 < 0xC0)) 
                    temp3 |= 0x00;  //gray1
                else if (temp2 == 0x40)
                    temp3 |= 0x01; //gray2

                if ((j == 0 && k <= 3) || (j == 1 && k <= 2))
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
    for (i = 0; i < 48000; i++)             //48000*2   800*480
    { 
        temp3 = 0;
        for (j = 0; j < 2; j++)	
        {
            temp1 = datas[i * 2 + j];
            for (k = 0; k < 4; k++)
            {
                temp2 = temp1 & 0xC0;
                if (temp2 == 0xC0)
                    temp3 |= 0x00;//white
                else if (temp2 == 0x00)
                    temp3 |= 0x01;  //black
                else if ((temp2 >= 0x80) && (temp2 < 0xC0)) 
                    temp3 |= 0x01;  //gray1
                else if (temp2 == 0x40)
                    temp3 |= 0x00; //gray2

                if ((j == 0 && k <= 3) || ( j== 1 && k <= 2))
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
    ESP_LOGI("GDEY075T7", "DISPLAY_4Level_Gray");
    unsigned int i; 

    GDEY075T7_wait_busy();
    GDEY075T7_write_cmd(0x10);   

    ESP_LOGI("GDEY075T7", "DISPLAY_4Level_Gray_2");
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

    ESP_LOGI("GDEY075T7", "DISPLAY_4Level_Gray_3");
    GDEY075T7_wait_busy();
    GDEY075T7_write_cmd(0x13);   

    ESP_LOGI("GDEY075T7", "DISPLAY_4Level_Gray_4");
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
    ESP_LOGI("GDEY075T7", "DISPLAY_4Level_Gray_END");
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
static void GDEY075T7_write_grayscale_display(const unsigned char *datas)
{
    unsigned int i;
    unsigned char value;

    GDEY075T7_write_cmd(0x10);
    for(i = 0; i < GDEY075T7_ARRAY * 2; i += 2)
    {
        value = R24_DTM1(*(datas + i), *(datas + i + 1));
        GDEY075T7_write_data(value);
    }

    GDEY075T7_write_cmd(0x13);
    for(i = 0; i < GDEY075T7_ARRAY * 2; i += 2)
    {
        value = R26_DTM2(*(datas + i), *(datas + i + 1));
        GDEY075T7_write_data(value);
    }
}

static void GDEY075T7_display_image_grayscale(const unsigned char *data)
{
    ESP_LOGI("GDEY075T7", "_display_image_grayscale");

    /* EPD_Init_4G(); */
    GDEY075T7_init_display_grayscale();
        /* GDEY075T7_write_grayscale_display(data); */

    /* Display_4Level_Gray(); */
    EPD_WhiteScreen_ALL_4G(data);

    GDEY075T7_update_display();
    GDEY075T7_sleep();
    ESP_LOGI("GDEY075T7", "end");
    return;
}
