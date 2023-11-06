#pragma once

/*

 - 8 bit data bus
 - nRD nWR signals
 - C/nD command/data
 - nCE chip enable
 - RST reset
 - FNT font select 8x8 6x8
 - VSS-VO-VEE contrast voltage 10K pot

 func
 - after power on reset is required #10
 - the ext RAM can store text/graph/ ext CG-RAM
 - before read/write must perform status check #13
 - without status check lcd can not operate normally even with delay #14
 - first set data then command #15 (max 2 data)
 >- how does read work?
 - offset reg is external CG-RAM address
 - ade addr pointer to read/write RAM
 - there is auto inc read/write mode #26 that has to be disabled manually
 - in non auto it is possible to inc/dec/nochange the address (cmd is necessary for every byte)


 */

#include <stdint.h>
#include "main.h"

#include "frt.h"


#define delay_80ns() frt_wait_nops(2)

//LD1_GPIO_Port->BSRR = LD1_Pin;
// pindef
#define LCD_WR_1() lcd_wr_GPIO_Port->BSRR = lcd_wr_Pin
#define LCD_WR_0() lcd_wr_GPIO_Port->BSRR = lcd_wr_Pin<<16

#define LCD_RD_1() lcd_rd_GPIO_Port->BSRR = lcd_rd_Pin
#define LCD_RD_0() lcd_rd_GPIO_Port->BSRR = lcd_rd_Pin<<16

#define LCD_CE_1() lcd_ce_GPIO_Port->BSRR = lcd_ce_Pin
#define LCD_CE_0() lcd_ce_GPIO_Port->BSRR = lcd_ce_Pin<<16

#define LCD_CD_1() lcd_cd_GPIO_Port->BSRR = lcd_cd_Pin
#define LCD_CD_0() lcd_cd_GPIO_Port->BSRR = lcd_cd_Pin

#define LCD_RST_1() lcd_rst_GPIO_Port->BSRR = lcd_rst_Pin
#define LCD_RST_0() lcd_rst_GPIO_Port->BSRR = lcd_rst_Pin<<16

#define LCD_DB0_1() lcd_d0_GPIO_Port->BSRR = lcd_d0_Pin
#define LCD_DB0_0() lcd_d0_GPIO_Port->BSRR = lcd_d0_Pin<<16

#define LCD_DB1_1() lcd_d1_GPIO_Port->BSRR = lcd_d1_Pin
#define LCD_DB1_0() lcd_d1_GPIO_Port->BSRR = lcd_d1_Pin<<16

#define LCD_DB2_1() lcd_d2_GPIO_Port->BSRR = lcd_d2_Pin
#define LCD_DB2_0() lcd_d2_GPIO_Port->BSRR = lcd_d2_Pin<<16

#define LCD_DB3_1() lcd_d3_GPIO_Port->BSRR = lcd_d3_Pin
#define LCD_DB3_0() lcd_d3_GPIO_Port->BSRR = lcd_d3_Pin<<16

#define LCD_DB4_1() lcd_d4_GPIO_Port->BSRR = lcd_d4_Pin
#define LCD_DB4_0() lcd_d4_GPIO_Port->BSRR = lcd_d4_Pin<<16

#define LCD_DB5_1() lcd_d5_GPIO_Port->BSRR = lcd_d5_Pin
#define LCD_DB5_0() lcd_d5_GPIO_Port->BSRR = lcd_d5_Pin<<16

#define LCD_DB6_1() lcd_d6_GPIO_Port->BSRR = lcd_d6_Pin
#define LCD_DB6_0() lcd_d6_GPIO_Port->BSRR = lcd_d6_Pin<<16

#define LCD_DB7_1() lcd_d7_GPIO_Port->BSRR = lcd_d7_Pin
#define LCD_DB7_0() lcd_d7_GPIO_Port->BSRR = lcd_d7_Pin<<16


#define LCD_FS_1() lcd_fs_GPIO_Port->BSRR = lcd_fs_Pin
#define LCD_FS_0() lcd_fs_GPIO_Port->BSRR = lcd_fs_Pin<<16

#define LCD_DB0() ((lcd_d0_GPIO_Port->IDR & lcd_d0_Pin)!=0)
#define LCD_DB1() ((lcd_d1_GPIO_Port->IDR & lcd_d1_Pin)!=0)
#define LCD_DB2() ((lcd_d2_GPIO_Port->IDR & lcd_d2_Pin)!=0)
#define LCD_DB3() ((lcd_d3_GPIO_Port->IDR & lcd_d3_Pin)!=0)
#define LCD_DB4() ((lcd_d4_GPIO_Port->IDR & lcd_d4_Pin)!=0)
#define LCD_DB5() ((lcd_d5_GPIO_Port->IDR & lcd_d5_Pin)!=0)
#define LCD_DB6() ((lcd_d6_GPIO_Port->IDR & lcd_d6_Pin)!=0)
#define LCD_DB7() ((lcd_d7_GPIO_Port->IDR & lcd_d7_Pin)!=0)


void lcd_init(void) __attribute__((optimize("O3")));
void lcd_set_data(uint8_t d) __attribute__((optimize("O3")));
uint8_t lcd_get_data(void) __attribute__((optimize("O3")));
