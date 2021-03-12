//******************************************************************************
// Library to LCD 2 rows mode developed under 16F877 data sheet
// Developed by Nivaldo T. Schiefler Jr.  Dr eng.
// Build under XC8 compiler
// 14/09/2017 
// Updates: 
// 
//******************************************************************************
#include <xc.h>
#include <string.h>
#include "LCD2L.h"
#include "config.h"
//***********************************************************
void init_lcd2L(void) //ok
{
    char x;
    comand_lcd2L(0); 
    __delay_ms(20);
    //****************************
    for(x = 0; x < 3; x++)
       {
        comand_lcd2L(3);
        __delay_ms(5);
       }
    comand_lcd2L(2);
    //****************************
    comand_lcd2L(2); // 0x28;
    comand_lcd2L(8);
  
    comand_lcd2L(0); // 0x0C
    comand_lcd2L(0xC);
   
    comand_lcd2L(0x0); // 0x06
    comand_lcd2L(0x6);
}
//******************************************************************************
void comand_bits_lcd2L(char data_in)
{
 //***************************
 D7 = test_bit(data_in,3);
 D6 = test_bit(data_in,2);
 D5 = test_bit(data_in,1);
 D4 = test_bit(data_in,0);
 //***************************
}
//******************************************************************************
void comand_lcd2L(char data_in)
{
 RS = 0;
 //***************************
 comand_bits_lcd2L(data_in);
 //***************************
 EN = 1; 
 __delay_ms(4);
 EN = 0; 
//****************************
}
//******************************************************************************
void clear_lcd2L(void) // ok
{
   comand_lcd2L(0);
   comand_lcd2L(1);
}
//******************************************************************************
__bit test_bit(char char_in,unsigned char bit_pos_in)// ok
{
      if(((char_in >> bit_pos_in)  & 0x01) == 1)
        return 1;
      else
        return 0;  
}
//******************************************************************************
void write_text_lcd2L(char *text_in,unsigned int row_in,unsigned int column_in)
{
  //******************************************** 
  char position,end_position;
  char char_x;
  char templ,temph;
  char *ptr;
  //********************************************
  ptr = text_in;
  //********************************************
  if (row_in == 0)
      position = 0x80;
  else
      position = 0xC0;
  //********************************************
  end_position = position + (char)column_in;
  templ = (char)(end_position & 0x0F);
  temph = (char)(end_position & 0xF0); 
  comand_lcd2L(temph >> 4);
  comand_lcd2L(templ);
  //********************************************
  while(*ptr)
    {
      char_x = *ptr++;    
      templ = (char)(char_x & 0x0F);
      temph = (char)(char_x & 0xF0);
      RS = 1;  
      comand_bits_lcd2L(temph >> 4);
      EN = 1;
      __delay_us(40);
      
      EN = 0;
      comand_bits_lcd2L(templ);
      EN = 1;
      __delay_us(40);
      EN = 0;
    }
}
//******************************************************************************

void write_char_lcd2L(char char_in,unsigned int row_in,unsigned int column_in)
{
  //*************************************
  char position,end_position;
  char templ,temph;
  //*************************************
  if (row_in == 0)
      position = 0x80;
  else
      position = 0xC0;
  //*************************************
  end_position = position + (char)column_in;
  templ = (char)(end_position & 0x0F);
  temph = (char)(end_position & 0xF0); 
  comand_lcd2L(temph >> 4);
  comand_lcd2L(templ);
  //************************************
  templ = (char)(char_in & 0x0F);
  temph = (char)(char_in & 0xF0);
  RS = 1;  
  comand_bits_lcd2L(temph >> 4);
  EN = 1;
  __delay_us(40);
      
  EN = 0;
  comand_bits_lcd2L(templ);
  EN = 1;
  __delay_us(40);
  EN = 0;
}
//******************************************************************************

