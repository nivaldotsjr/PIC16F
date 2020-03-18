//******************************************************************************
// Library to I2C mode developed under 16F877 data sheet
// Developed by Nivaldo T. Schiefler Jr.  Dr eng.
// Build under XC8 compiler
// 10/03/2020 
// Updates: 
// 
//******************************************************************************
#include <xc.h>
#include "config.h"
#include "I2C.h"
//******************************************************************************

void init_i2c(char master_slave,unsigned long freq_i2c,int address)
{
    //must configure these pins as inputs or outputs through the TRISC<4:3> bits.
  
  //  settings pagina 74   
  //SSPSTAT: MSSP STATUS REGISTER 
  //SSPSTAT:   SMP CKE D/A P S R/W UA BF   
 
  // SSPCON1: MSSP CONTROL REGISTER 1 
  // SSPCON1: WCOL SSPOV  SSPEN  CKP SSPM3 SSPM2 SSPM1 SSPM0  
  
  // SSPCON2: MSSP CONTROL REGISTER 2  
  // SSPCON2: GCEN ACKSTAT ACKDT ACKEN RCEN PEN RSEN SEN  
  
  // SSPADD Synchronous Serial Port (I2C mode) Address Register  
  //**************************************************************************** 
   SSPSTAT = 0b00000000;
   SSPCON  = 0b00000000;
   SSPCON2 = 0b00000000;
   //***************************************************************************
   SSPADD = _XTAL_FREQ/(4*freq_i2c) - 1;      //page 82  
   //***************************************************************************
   if(master_slave == 1)
   {
     // SSPCON1  WCOL SSPOV  SSPEN  CKP SSPM3 SSPM2 SSPM1 SSPM0    
     //   WCOL: Write Collision Detect bit -> = No collision 
     //  SSPEN: Synchronous Serial Port Enable bit
     //   1 = Enables the serial port and configures the SDA and SCL pins as the serial port pins
     //SSPM3:SSPM0:  1000 = I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))
        SSPCON  = 0b00000000 | 0b00101000;
        TRISC4 = 1;  // SDA
        TRISC3 = 1;  // SCL
        
   }
   else
   {
        SSPADD = address;   
       //SMP: Slew Rate Control bit
       //In Master or Slave mode:
       // 1 = Slew rate control disabled for standard speed mode (100 kHz and 1 MHz)
       // 0 = Slew rate control enabled for high-speed mode (400 kHz)   
        if(freq_i2c == 100000 || freq_i2c == 1000000)  
            SSPSTAT = SSPSTAT | 0b10000000;
        else
            SSPSTAT = SSPSTAT | 0b00000000;
       // SSPCON: WCOL SSPOV SSPEN CKP SSPM3 SSPM2 SSPM1 SSPM0 
       // SSPEN: Synchronous Serial Port Enable bit
       //  1 = Enables the serial port and configures the SDA and SCL pins as the serial port pins 
       // CKP: SCK Release Control bit
       // In Slave mode:
       // 1 = Release clock
       // 0 = Holds clock low (clock stretch). (Used to ensure data setup time.) 
       // SSPM3:SSPM0: Synchronous Serial Port Mode Select bits 
       // 0110 = I2C Slave mode, 7-bit address 
       SSPCON  = 0b00110110; // configura I2c como slave, 7bits
       //       SSPCON2: GCEN ACKSTAT ACKDT ACKEN RCEN PEN RSEN SEN
       // SEN: Start Condition Enabled/Stretch Enabled bit
       // In Slave mode:
       // 1 = Clock stretching is enabled for both slave transmit and slave receive (stretch enabled)
       // 0 = Clock stretching is enabled for slave transmit only (PIC16F87X compatibility)
       SSPCON2 = 0b00000001;  
       // INTCON = 0xC0; 
       GIE = 1;
       PEIE = 1;    //habilita interrupção do modulo I2c
       
       SSPIE = 1; 
       SSPIF = 0;
       
       TRISC4 = 1;  // SDA
       TRISC3 = 1;  // SCL
   }
     
   
}
//******************************************************************************
void write_i2c(char data)
{
   while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));//(SSPSTATbits.READ_WRITE == 1);  // 1 = Transmit is in progress
   SSPBUF = data; 
}
//******************************************************************************
char read_i2c(unsigned char ackdt_bit)
{
   char data; 
   while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));//
   SSPCON2bits.ACKDT = 1;
   
   while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));//
   data = SSPBUF; 
   
   while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));//
   if(ackdt_bit == 0)
       ACKDT = 0;
   else
       ACKDT = 1;
   return data;
}
//******************************************************************************
void i2c_start(char master_slave)
{
  if(master_slave == 1) 
  {
       while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));//
     //while(SSPSTATbits.READ_WRITE == 1);  // 1 = Transmit is in progress
     SSPCON2bits.SEN = 1; // SEN: Start Condition Enabled/Stretch Enabled bit
  }
}
//******************************************************************************
void i2c_start_repeat(char master_slave)
{
  if(master_slave == 1) 
  {
     while(SSPSTATbits.READ_WRITE == 1);  // 1 = Transmit is in progress
     SSPCON2bits.RSEN = 1; // RSEN: Repeated Start Condition Enabled bit (Master mode only)
  }
}
//******************************************************************************
void i2c_stop(char master_slave)
{
  if(master_slave == 1) 
  {
     while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));//
    // while(SSPSTATbits.READ_WRITE == 1);  // 1 = Transmit is in progress
     SSPCON2bits.PEN = 1; // PEN: Stop Condition Enable bit (Master mode only)
  }
}
//******************************************************************************
