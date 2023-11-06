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


#define x40_set_text_home_address		(0x40) 	// low high addr
#define x41_set_text_area				(0x41) 	// col 0 (number of columns of text (8pix wide)
#define x42_set_graphic_home_address	(0x42)	// low high addr
#define x43_set_graphic_area			(0x43)	// col 0	(hres/8)

#define x90_display_mode				(0x90)	// 0-blink 1-cursor 2-text 3-graph (0len cmd)
#define x21_set_cursor_position			(0x21)	// x, y

#define x24_set_address_pointer			(0x24)	//low high 2

#define xc0_data_write_inc				(0xc0)	//low high 2

#define x80_mode_set					(0x80)  //0 or 1 xor 3 and | 0x08 ext cg

#define lcd_delay_80ns() frt_wait_nops(2)

//LD1_GPIO_Port->BSRR = LD1_Pin;
// pindef
#define LCD_WR_1() lcd_wr_GPIO_Port->BSRR = lcd_wr_Pin
#define LCD_WR_0() lcd_wr_GPIO_Port->BSRR = lcd_wr_Pin<<16

#define LCD_RD_1() lcd_rd_GPIO_Port->BSRR = lcd_rd_Pin
#define LCD_RD_0() lcd_rd_GPIO_Port->BSRR = lcd_rd_Pin<<16

#define LCD_CE_1() lcd_ce_GPIO_Port->BSRR = lcd_ce_Pin
#define LCD_CE_0() lcd_ce_GPIO_Port->BSRR = lcd_ce_Pin<<16

#define LCD_CD_1() lcd_cd_GPIO_Port->BSRR = lcd_cd_Pin
#define LCD_CD_0() lcd_cd_GPIO_Port->BSRR = lcd_cd_Pin<<16

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


// 0x80 -> 7  * 2 -> 14 -> 2^14 = 0x4000 = 0x80*0x80

#define LCD_DB0_out()  lcd_d0_GPIO_Port->MODER |=  (uint32_t)(lcd_d0_Pin *  lcd_d0_Pin)
#define LCD_DB0_in()   lcd_d0_GPIO_Port->MODER &= ~(uint32_t)(lcd_d0_Pin *  lcd_d0_Pin)

#define LCD_DB1_out()  lcd_d1_GPIO_Port->MODER |=  (uint32_t)(lcd_d1_Pin *  lcd_d1_Pin)
#define LCD_DB1_in()   lcd_d1_GPIO_Port->MODER &= ~(uint32_t)(lcd_d1_Pin *  lcd_d1_Pin)

#define LCD_DB2_out()  lcd_d2_GPIO_Port->MODER |=  (uint32_t)(lcd_d2_Pin *  lcd_d2_Pin)
#define LCD_DB2_in()   lcd_d2_GPIO_Port->MODER &= ~(uint32_t)(lcd_d2_Pin *  lcd_d2_Pin)

#define LCD_DB3_out()  lcd_d3_GPIO_Port->MODER |=  (uint32_t)(lcd_d3_Pin *  lcd_d3_Pin)
#define LCD_DB3_in()   lcd_d3_GPIO_Port->MODER &= ~(uint32_t)(lcd_d3_Pin *  lcd_d3_Pin)

#define LCD_DB4_out()  lcd_d4_GPIO_Port->MODER |=  (uint32_t)(lcd_d4_Pin *  lcd_d4_Pin)
#define LCD_DB4_in()   lcd_d4_GPIO_Port->MODER &= ~(uint32_t)(lcd_d4_Pin *  lcd_d4_Pin)

#define LCD_DB5_out()  lcd_d5_GPIO_Port->MODER |=  (uint32_t)(lcd_d5_Pin *  lcd_d5_Pin)
#define LCD_DB5_in()   lcd_d5_GPIO_Port->MODER &= ~(uint32_t)(lcd_d5_Pin *  lcd_d5_Pin)

#define LCD_DB6_out()  lcd_d6_GPIO_Port->MODER |=  (uint32_t)(lcd_d6_Pin *  lcd_d6_Pin)
#define LCD_DB6_in()   lcd_d6_GPIO_Port->MODER &= ~(uint32_t)(lcd_d6_Pin *  lcd_d6_Pin)

#define LCD_DB7_out()  lcd_d7_GPIO_Port->MODER |=  (uint32_t)(lcd_d7_Pin *  lcd_d7_Pin)
#define LCD_DB7_in()   lcd_d7_GPIO_Port->MODER &= ~(uint32_t)(lcd_d7_Pin *  lcd_d7_Pin)





void lcd_init(void) __attribute__((optimize("O3")));
void lcd_set_data(uint8_t d) __attribute__((optimize("O3")));
uint8_t lcd_get_data(void) __attribute__((optimize("O3")));
