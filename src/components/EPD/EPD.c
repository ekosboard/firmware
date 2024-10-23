#include "EPD.h"
#include "driver/gpio.h"
#include "esp_log.h"

//Full screen partial refresh display
/* void EPD_Dis_PartAll(const unsigned char * datas) */
/* { */
/* 	unsigned int i; */
/* 	unsigned int PART_COLUMN, PART_LINE; */
/* 	PART_COLUMN=EPD_HEIGHT,PART_LINE=EPD_WIDTH; */

/*     gpio_set_level(GDEY042T81_RST, 0); */
/*     vTaskDelay(pdMS_TO_TICKS(10)); */
/*     gpio_set_level(GDEY042T81_RST, 1); */
/*     vTaskDelay(pdMS_TO_TICKS(10)); */

/* 	GDEY042T81_write_cmd(0x3C); //BorderWavefrom, */
/* 	GDEY042T81_write_data(0x80); */

/* 	GDEY042T81_write_cmd(0x21); */
/* 	GDEY042T81_write_data(0x00); */
/* 	GDEY042T81_write_data(0x00); */

/* 	GDEY042T81_write_cmd(0x24);   //Write Black and White image to RAM */
/* 	 for(i=0;i<PART_COLUMN*PART_LINE/8;i++) */
/* 	 { */
/* 		 GDEY042T81_write_data(datas[i]); */
/* 	 } */
/* 	 EPD_Part_Update(); */

/* } */


/* //Partial refresh of background display, this function is necessary, please do not delete it!!! */
/* void EPD_SetRAMValue_BaseMap(const unsigned char * datas) */
/* { */
/*     unsigned int i; */
/*     GDEY042T81_write_cmd(0x24);   //Write Black and White image to RAM */
/*     for(i=0; i<GDEY042T81_ARRAY; i++) */
/*     { */
/*         GDEY042T81_write_data(datas[i]); */
/*     } */
/*     GDEY042T81_write_cmd(0x26);   //Write Black and White image to RAM */
/*     for(i=0; i<GDEY042T81_ARRAY; i++) */
/*     { */
/*         GDEY042T81_write_data(datas[i]); */
/*     } */
/*     EPD_Update(); */

/* } */

/* //Partial refresh write address and data */
/* void EPD_Dis_Part_RAM(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE) */
/* { */
/*     unsigned int i; */
/*     unsigned int x_end,y_end; */

/*     x_start=x_start/8; //x address start */
/*     x_end=x_start+PART_LINE/8-1; //x address end */

/*     y_start=y_start-1; //Y address start */
/*     y_end=y_start+PART_COLUMN-1; //Y address end */

/*     gpio_set_level(GDEY042T81_RST, 0); */
/*     vTaskDelay(pdMS_TO_TICKS(10)); */
/*     gpio_set_level(GDEY042T81_RST, 1); */
/*     vTaskDelay(pdMS_TO_TICKS(10)); */

/*     GDEY042T81_write_cmd(0x21); */
/*     GDEY042T81_write_data(0x00); */
/*     GDEY042T81_write_data(0x00); */

/*     GDEY042T81_write_cmd(0x3C); //BorderWavefrom, */
/*     GDEY042T81_write_data(0x80); */

/*     GDEY042T81_write_cmd(0x44);       // set RAM x address start/end */
/*     GDEY042T81_write_data(x_start);  //x address start */
/*     GDEY042T81_write_data(x_end);   //y address end */
/*     GDEY042T81_write_cmd(0x45);     // set RAM y address start/end */
/*     GDEY042T81_write_data(y_start%256);  //y address start2 */
/*     GDEY042T81_write_data(y_start/256); //y address start1 */
/*     GDEY042T81_write_data(y_end%256);  //y address end2 */
/*     GDEY042T81_write_data(y_end/256); //y address end1 */

/*     GDEY042T81_write_cmd(0x4E);   // set RAM x address count to 0; */
/*     GDEY042T81_write_data(x_start);   //x start address */
/*     GDEY042T81_write_cmd(0x4F);   // set RAM y address count to 0X127; */
/*     GDEY042T81_write_data(y_start%256); //y address start2 */
/*     GDEY042T81_write_data(y_start/256); //y address start1 */

/*     GDEY042T81_write_cmd(0x24);   //Write Black and White image to RAM */
/*     for(i=0; i<PART_COLUMN*PART_LINE/8; i++) */
/*     { */
/*         GDEY042T81_write_data(datas[i]); */
/*     } */
/* } */

/* //Partial refresh update function */
/* void EPD_Part_Update(void) */
/* { */
/*     GDEY042T81_write_cmd(0x22); //Display Update Control */
/*     GDEY042T81_write_data(0xFF); */
/*     GDEY042T81_write_cmd(0x20); //Activate Display Update Sequence */
/*     Epaper_READBUSY(); */
/* } */

/* void EPD_Dis_Part_Time(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA, */
/*                        unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB, */
/*                        unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC, */
/*                        unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD, */
/*                        unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE, */
/*                        unsigned int PART_COLUMN,unsigned int PART_LINE */
/*                       ) */
/* { */
/*     EPD_Dis_Part_RAM(x_startA,y_startA,datasA,PART_COLUMN,PART_LINE); */
/*     EPD_Dis_Part_RAM(x_startB,y_startB,datasB,PART_COLUMN,PART_LINE); */
/*     EPD_Dis_Part_RAM(x_startC,y_startC,datasC,PART_COLUMN,PART_LINE); */
/*     EPD_Dis_Part_RAM(x_startD,y_startD,datasD,PART_COLUMN,PART_LINE); */
/*     EPD_Dis_Part_RAM(x_startE,y_startE,datasE,PART_COLUMN,PART_LINE); */
/*     EPD_Part_Update(); */
/* } */

/* void pic_display_4line(void) */
/* { */
/*     unsigned int row,col; */
/*     GDEY042T81_write_cmd(0x24);			//¿ªÊ¼´«ÊäºÚ°×Í¼Ïñ */
/*     for(col=0;col<300;col++) */
/*     { */
/*         for(row=0;row<13;row++) */
/*         { */
/*             GDEY042T81_write_data(0xFF); */
/*         } */
/*         for(row=0;row<12;row++) */
/*         { */
/*             GDEY042T81_write_data(0x00); */
/*         } */
/*         for(row=0;row<12;row++) */
/*         { */
/*             GDEY042T81_write_data(0xFF); */
/*         } */
/*         for(row=0;row<13;row++) */
/*         { */
/*             GDEY042T81_write_data(0x00); */
/*         } */
/*     } */

/*     GDEY042T81_write_cmd(0x26);			//¿ªÊ¼´«ÊäºìÍ¼Ïñ */
/*     for(col=0;col<300;col++) */
/*     { */
/*         for(row=0;row<13;row++) */
/*         { */
/*             GDEY042T81_write_data(0xFF); */
/*         } */
/*         for(row=0;row<12;row++) */
/*         { */
/*             GDEY042T81_write_data(0xFF); */
/*         } */
/*         for(row=0;row<12;row++) */
/*         { */
/*             GDEY042T81_write_data(0x00); */
/*         } */
/*         for(row=0;row<13;row++) */
/*         { */
/*             GDEY042T81_write_data(0x00); */
/*         } */
/*     } */

/*     EPD_Update_4G(); */
/* } */

