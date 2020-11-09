/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "I2C_protocol.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    I2C_Peripheral_Start();
    UART_Start();
    
    DataFrame[0] = HEADER;
    DataFrame[DATA_FRAME_SIZE - 1] = TAIL;
    
     CyDelay(5); //"The boot procedure is complete about 5 milliseconds after device power-up."
    
    // String to print out messages on the UART
    char message[50] = {'\0'};
    
    UART_Start();
    UART_PutString("**************\r\n");
    UART_PutString("** I2C Scan **\r\n");
    UART_PutString("**************\r\n");
    
    CyDelay(100);
    
    uint32_t rval;
 
	// Setup the screen and print the header
	UART_PutString("\n\n   ");
	for(uint8_t i = 0; i<0x10; i++)
	{
        sprintf(message, "%02X ", i);
		UART_PutString(message);
	}
 
	// Iterate through the address starting at 0x00
	for(uint8_t i2caddress = 0; i2caddress < 0x80; i2caddress++)
	{
		if(i2caddress % 0x10 == 0 )
        {
            sprintf(message, "\n%02X ", i2caddress);
		    UART_PutString(message);
        }
 
		rval = I2C_Master_MasterSendStart(i2caddress, I2C_Master_WRITE_XFER_MODE);
        
        if(rval == I2C_Master_MSTR_NO_ERROR) // If you get ACK then print the address
		{
            sprintf(message, "%02X ", i2caddress);
		    UART_PutString(message);
		}
		else //  Otherwise print a --
		{
		    UART_PutString("-- ");
		}
        I2C_Master_MasterSendStop();
	}
	UART_PutString("\n\n");
    
    
    
    
    /******************************************/
    /*            I2C Writing                 */
    /******************************************/
       
    UART_PutString("\r\nWriting new Registers' values..\r\n");
    
    /***  CTRL_REG1 Writing in the start condition    ***/
    
    if (ctrl_reg1 != LIS3DH_START_MODE_CTRL_REG1)
    {
        ctrl_reg1 = LIS3DH_START_MODE_CTRL_REG1;
    
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
    
        if (error == NO_ERROR)
        {
            sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
            UART_PutString(message); 
        }
        else
        {
            UART_PutString("Error occurred during I2C comm to set control register 1\r\n");   
        }
    }
    
    /***  CTRL_REG4 Writing in the right condition    ***/
    
    if(ctrl_reg4 != LIS3DH_CTRL_REG4_HR_MODE_BDU_ACTIVE)
    {
        ctrl_reg4 = LIS3DH_CTRL_REG4_HR_MODE_BDU_ACTIVE;
        
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4, ctrl_reg4);
        
        if(error == NO_ERROR)
        {
            sprintf(message, "CONTROL REGISTER 4 successfully written as: 0x%02X\r\n", ctrl_reg4);
            UART_PutString(message);
        }
        else 
        {
            UART_PutString("Error occurred during I2C comm to set control register 4\r\n");
        }
    }
    
    /***  TMP_CFG_REG Writing    ***/
    
    if(tmp_cfg_reg != LIS3DH_TEMP_CFG_REG_ADC_ACTIVE)
    {
        tmp_cfg_reg = LIS3DH_TEMP_CFG_REG_ADC_ACTIVE;
        
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_TEMP_CFG_REG, tmp_cfg_reg);
        
        if(error == NO_ERROR)
        {
            sprintf(message, "TEMPERATURE CONFIGURATION REGISTER  successfully written as: 0x%02X\r\n", tmp_cfg_reg);
            UART_PutString(message);
        }
        else
        {
            UART_PutString("Error occurred during I2C comm to set temperature config register to enable ADC\r\n");
        }
    }
    
    UART_PutString("\n\n");
    
    /******************************************/
    /*            I2C Reading                 */
    /******************************************/
    
    UART_PutString("\r\nReading new Registers' values..\r\n");
    
    error_R1 = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, &ctrl_reg1);
    error_R2 = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4, &ctrl_reg4);
    error_R3 = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_TEMP_CFG_REG, &tmp_cfg_reg);
    error_R4 = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_STATUS_REG, &status_reg);
    
    if ((error_R1 == NO_ERROR) && (error_R2 == NO_ERROR) && (error_R3 == NO_ERROR))
    {
        sprintf(message, "CONTROL REGISTER 1: 0x%02X\r\n", ctrl_reg1);
        UART_PutString(message);
        sprintf(message, "CONTROL REGISTER 4 : 0x%02X\r\n", ctrl_reg4);
        UART_PutString(message);
        sprintf(message, "TEMPERATURE CONFIGURATION REGISTER : 0x%02X\r\n", tmp_cfg_reg);
        UART_PutString(message);
        sprintf(message, "STATUS REGISTER : 0x%02X\r\n", status_reg);
        UART_PutString(message);
    }
    else
    {
        UART_PutString("Error occurred during I2C comm to read ctrl_reg1, ctrl_reg4, tmp_cfg_reg\r\n");   
    }
    
    

    for(;;)
    {
        CyDelay(100);
        
        error_R4 = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_STATUS_REG, &status_reg);
        
        if(error_R4 == NO_ERROR)
        {
            //if(status_reg == NEW_DATA_AVALIABLE)
            {
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_X_L, N_ADC_REGISTERS, AccelerometerData);
                
                if(error == NO_ERROR)
                {
                    OutAcc1 = (int16)((AccelerometerData[0] | (AccelerometerData[1] << 8))) >> 4;
                    OutAcc2 = (int16)((AccelerometerData[2] | (AccelerometerData[3] << 8))) >> 4;
                    OutAcc3 = (int16)((AccelerometerData[4] | (AccelerometerData[5] << 8))) >> 4;
                    
                    DataFrame[1] = (uint8_t)(OutAcc1 & 0xFF);
                    DataFrame[2] = (uint8_t)(OutAcc1 >> 8);
                    DataFrame[3] = (uint8_t)(OutAcc2 & 0xFF);
                    DataFrame[4] = (uint8_t)(OutAcc2 >> 8);
                    DataFrame[5] = (uint8_t)(OutAcc3 & 0xFF);
                    DataFrame[6] = (uint8_t)(OutAcc3 >> 8);
                    
                    UART_PutArray(DataFrame, DATA_FRAME_SIZE);
                }
                else
                {
                    UART_PutString("Error occurred during I2C comm to read ADCs / temperature output registers\r\n");
                }
            }
        }
    }
}

/* [] END OF FILE */
