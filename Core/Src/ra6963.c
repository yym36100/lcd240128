#include "ra6963.h"

void lcd_write(uint8_t data, uint8_t iscmd){
	if(iscmd)LCD_CD_1(); else LCD_CD_0();
	LCD_CE_0();

	lcd_set_data(cmd);
	LCD_WR_0();
	lcd_delay_80ns();
	LCD_WR_1();
	LCD_CE_1();
}

void lcd_init(void){

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
