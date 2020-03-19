//******************************************************************************
// Library to RS232 mode developed under 16F877 data sheet
// Developed by Nivaldo T. Schiefler Jr.  Dr eng.
// Build under XC8 compiler
// 09/04/2019 
// Updates: 

//******************************************************************************
#include <xc.h>
#include "config.h"
//******************************************************************************
int init_RS232(const long int baudrate)
{
  //                  Pagina 113
  //         SYNC BRGH = 0 (Low Speed)                          BRGH = 1 (High Speed)
  //    0  (Asynchronous) Baud Rate = FOSC/(64 (X + 1))     Baud Rate = FOSC/(16 (X + 1))
  //    1   (Synchronous) Baud Rate = FOSC/(4 (X + 1))             N/A
  //                 Legend: X = value in SPBRG (0 to 255)
  unsigned int x;
  TRISC7 = 1;      //RX
  TRISC6 = 0;      //TX 
  //_XTAL_FREQ was set in config.h
   x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);   // SPBRG for Low Baud Rate 
                                                   // If High Baud Rage Required
   BRGH = 0; //High Baud Rate Select bit      
   /*   Asynchronous mode:
        1 = High speed
        0 = Low speed
        Synchronous mode:
        Unused in this mode.
    */
  if(x>255)                                       
  {
    x = (_XTAL_FREQ - baudrate*16)/(baudrate*16); //SPBRG for High Baud Rate
    BRGH = 1;                                     //Setting High Baud Rate
  }
  if(x<256)
  {
    SPBRG = x;                                    //Writing SPBRG Register
    //**************   TXSTA   *******************
    TXEN = 1;                                     //Enables Transmit Enable bit
    SYNC = 0;                                     //USART Mode Select bit  
                                                  //   1 = Synchronous mode
                                                  //   0 = Asynchronous mode
     //**************   RXSTA   *******************
    SPEN = 1;                                     //Enables Serial Port                                 
    CREN = 1;                                     //Enables Continuous Receive Enable bit
   
    return 1;                                     //Returns 1 to indicate Successful Completion
  }
  return 0;                                       //Returns 0 to indicate UART initialization failed
}  
//******************************************************************************
void write_char_UART(char data)
{
  while(!TRMT)  // Transmit Shift Register Status bit
      ;         //  1 = TSR empty
                //  0 = TSR full
  TXREG = data;
}
//******************************************************************************
void write_text_UART(char *text)
{
  int i;
  for(i = 0; text[i]!= '\0' ; i++)
      write_char_UART(text[i]);  
}
//******************************************************************************
char read_UART(void)
{
  while(!RCIF)  //  PIR1  -> RCIF: USART Receive Interrupt Flag bit
       ;        //     1 = The USART receive buffer is full
                //     0 = The USART receive buffer is empty
  return RCREG;  
}
//******************************************************************************
void read_text_UART(char *read_text, unsigned int text_size)
{
  unsigned int i;
  for(i = 0; i < text_size; i++)
       read_text[i] = read_UART();  
}
//******************************************************************************
char TX_empty_UART(void)
{
  return (char)TRMT;  
}
//******************************************************************************
char data_Ready_UART(void)
{
  return (char)RCIF;  
}
//******************************************************************************
