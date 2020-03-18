//******************************************************************************
// Library to I2C mode developed under 16F877 data sheet
// Developed by Nivaldo T. Schiefler Jr.  Dr eng.
// Build under XC8 compiler
// 10/03/2020 
// Updates: 

//******************************************************************************
/*
 void init_i2c(char master_slave,unsigned long freq_i2c,int address);  
 void write_i2c(char data);
 char read_i2c(unsigned char ackdt_bit);
 void i2c_start(char master_slave);
 void i2c_start_repeat(char master_slave);
 void i2c_stop(char master_slave);
 */
//******************************************************************************

#ifndef I2C_H
#define	I2C_H


#ifdef	__cplusplus
extern "C" {
#endif 
//******************************************************************************
#pragma warning disable 520 // Disable unused functions warnings
//******************************************************************************
 void init_i2c(char master_slave,unsigned long freq_i2c,int address);  
 void write_i2c(char data);
 char read_i2c(unsigned char ackdt_bit);
 void i2c_start(char master_slave);
 void i2c_start_repeat(char master_slave);
 void i2c_stop(char master_slave);
//****************************************************************************** 
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* I2C_H */

