//******************************************************************************
// Library to LCD 2 rows mode developed under 16F877 data sheet
// Developed by Nivaldo T. Schiefler Jr.  Dr eng.
// Build under XC8 compiler
// 14/09/2017 
// Updates: 
// 
//******************************************************************************
/*
void init_lcd2L(void);
void comand_bits_lcd2L(char data_in);
void comand_lcd2L(char data_in);
void clear_lcd2L(void);
__bit test_bit(char char_in,unsigned char bit_pos_in);
void write_text_lcd2L(char *text_in,unsigned int row_in,unsigned int column_in);
void write_char_lcd2L(char char_in,unsigned int row_in,unsigned int column_in);
*/
//******************************************************************************
#ifndef LCD2L_H
#define	LCD2L_H

#ifdef	__cplusplus
extern "C" {
#endif
//******************************************************************************
//                     Pinos para o LCD de 4 bits
//******************************************************************************    
#define RS RE0
#define EN RE1
   
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
      
//******************************************************************************
#pragma warning disable 520 // Disable os warnings
//******************************************************************************
 void init_lcd2L(void);
 void comand_bits_lcd2L(char data_in);
 void comand_lcd2L(char data_in);
 void clear_lcd2L(void);
 __bit test_bit(char char_in,unsigned char bit_pos_in);
 void write_text_lcd2L(char *text_in,unsigned int row_in,unsigned int column_in);
 void write_char_lcd2L(char char_in,unsigned int row_in,unsigned int column_in);
//******************************************************************************
#ifdef	__cplusplus
}
#endif

#endif	/* LCD2L_H */

