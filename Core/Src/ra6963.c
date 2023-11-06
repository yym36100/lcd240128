#include "ra6963.h"

static uint8_t lcd_db_isin=0;
static uint8_t lcd_status=0;

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
	lcd_set_data(data);
	LCD_WR_0();
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
	//lcd_delay_80ns();
	res= lcd_get_data();
	LCD_RD_1();
	LCD_CE_1();
	if(isstatus)lcd_status=res;
	return res;
}

void lcd_set_cmd(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t len){
	// #15 1.8v lcd datasheet

	// data1
	if(len!=0) {while((lcd_read(1)&3)!=3){;}lcd_write(data1,0);}

	// data2
	if(len==2) {while((lcd_read(1)&3)!=3){;}lcd_write(data2,0);}

	// cmd
	while((lcd_read(1)&3)!=3){;}lcd_write(cmd,1);
}

void lcd_write_data(uint8_t d){

	while((lcd_read(1)&3)!=3);
	lcd_write(d,0);

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

	lcd_set_cmd(x40_set_text_home_address, 		0 , 0, 2);
	lcd_set_cmd(x41_set_text_area, 				30, 0, 2);

	lcd_set_cmd(x42_set_graphic_home_address, 	0 , 8, 2);
	lcd_set_cmd(x43_set_graphic_area, 			30, 0, 2);

	lcd_set_cmd(x90_display_mode|8,		0, 0, 0); //blink curs text gra

	lcd_set_cmd(x21_set_cursor_position, 		0, 0, 2);

	lcd_set_cmd(x24_set_address_pointer, 0, 0, 2);
	for(int i=0;i<240*128/8;i++){
		lcd_set_cmd(xc0_data_write_inc, 0x2, 0, 1);
	}

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
