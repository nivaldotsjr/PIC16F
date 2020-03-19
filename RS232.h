//******************************************************************************
// Library to RS232 mode developed under 16F877 data sheet
// Developed by Nivaldo T. Schiefler Jr.  Dr eng.
// Build under XC8 compiler
// 09/04/2019 
// Updates: 

//******************************************************************************
/*
  int init_RS232(const long int baudrate);
  void write_char_UART(char data);
  void write_text_UART(char *text);
  char read_UART(void);
  void read_text_UART(char *read_text, unsigned int text_size);
  char TX_UART_empty(void);
  char UART_data_Ready(void);
 */
//******************************************************************************

#ifndef RS232_H
#define	RS232_H

//#include <xc.h> // include processor files - each processor file is guarded.  
//******************************************************************************
#pragma warning disable 520 // Disable unused functions warnings
//******************************************************************************
int init_RS232(const long int baudrate);
void write_char_UART(char data);
void write_text_UART(char *text);
char read_UART(void);
void read_text_UART(char *read_text, unsigned int text_size);
char TX_empty_UART(void);
char data_Ready_UART(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* RS232_H */

