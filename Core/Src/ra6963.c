#include "ra6963.h"

static uint8_t lcd_db_isin=0;

void ldc_db_in(){
	if(lcd_db_isin) return;
	lcd_db_isin = 1;
	LCD_DB0_in();
	LCD_DB1_in();
	LCD_DB2_in();
	LCD_DB3_in();
	LCD_DB4_in();
	LCD_DB5_in();
	LCD_DB6_in();
	LCD_DB7_in();
}

void ldc_db_out(){
	if(!lcd_db_isin) return;
	lcd_db_isin = 0;
	LCD_DB0_out();
	LCD_DB1_out();
	LCD_DB2_out();
	LCD_DB3_out();
	LCD_DB4_out();
	LCD_DB5_out();
	LCD_DB6_out();
	LCD_DB7_out();
}

void lcd_write(uint8_t data, uint8_t iscmd){
	ldc_db_out();
	if(iscmd)LCD_CD_1(); else LCD_CD_0(); //100ns cycle
	LCD_CE_0(); // ce, rd/wr cycle =80ns
	LCD_WR_0();
	lcd_set_data(data);
	lcd_delay_80ns();
	LCD_WR_1();
	LCD_CE_1();
}

uint8_t lcd_read(uint8_t isstatus){
	uint8_t res;
	ldc_db_in();
	if(isstatus)LCD_CD_1(); else LCD_CD_0(); //100ns cycle
	LCD_CE_0(); // ce, rd/wr cycle =80ns
	LCD_RD_0();

	lcd_delay_80ns();
	lcd_delay_80ns();
	res= lcd_get_data();
	LCD_RD_1();
	LCD_CE_1();
	return res;
}

volatile uint8_t status = 0x5d;
void lcd_init(void){
	LCD_WR_1();
	LCD_RD_1();
	LCD_CE_1();
	LCD_CD_1();
	LCD_FS_1(); //6x8 font

	HAL_Delay(100);
	// release reset
	LCD_RST_1();

	HAL_Delay(20);
	status = lcd_read(1);


}



void lcd_set_data(uint8_t d){
	if(d&1)  {LCD_DB0_1();} else {LCD_DB0_0();}
	if(d&2)  {LCD_DB1_1();} else {LCD_DB1_0();}
	if(d&4)  {LCD_DB2_1();} else {LCD_DB2_0();}
	if(d&8)  {LCD_DB3_1();} else {LCD_DB3_0();}
	if(d&16) {LCD_DB4_1();} else {LCD_DB4_0();}
	if(d&32) {LCD_DB5_1();} else {LCD_DB5_0();}
	if(d&64) {LCD_DB6_1();} else {LCD_DB6_0();}
	if(d&128){LCD_DB7_1();} else {LCD_DB7_0();}
}

uint8_t lcd_get_data(void){
	uint8_t res;
	res = LCD_DB0();
	res|=LCD_DB1()<<1;
	res|=LCD_DB2()<<2;
	res|=LCD_DB3()<<3;
	res|=LCD_DB4()<<4;
	res|=LCD_DB5()<<5;
	res|=LCD_DB6()<<6;
	res|=LCD_DB7()<<7;
	return res;
}
