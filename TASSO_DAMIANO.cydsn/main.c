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
#include "ServiceRoutines.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    I2C_Peripheral_Start();
    UART_Start();
    EEPROM_Start();
    isr_BUTTON_StartEx(custom_isr_BUTTON);
    
    DataFrame[0] = HEADER;
    DataFrame[DATA_FRAME_SIZE - 1] = TAIL;
    
    //EEPROM_WriteByte(ctrl_reg1_odr_update, 0x0000);
    ctrl_reg1 = EEPROM_ReadByte(0x0000);
    
    
     CyDelay(5); //"The boot procedure is complete about 5 milliseconds after device power-up."
    
    // String to print out messages on the UART
    char message[50] = {'\0'};
    
    UART_Start();
    UART_PutString("**************\r\n");
    UART_PutString("** I2C Scan **\r\n");
    UART_PutString("**************\r\n");
    
    CyDelay(100);
    
    
    /******************************************/
    /*            I2C Writing                 */
    /******************************************/
       
    UART_PutString("\r\nWriting new Registers' values..\r\n");
    
    /***  CTRL_REG1 Writing in the start condition    ***/
    
    //ctrl_reg1 = EEPROM_ReadByte(0x0000);
    //error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
    //sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
    
    /*if (ctrl_reg1 != ctrl_reg1_odr_update)
    {
        ctrl_reg1 = ctrl_reg1_odr_update;
    
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
    }*/
    
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
        
        ctrl_reg1 = EEPROM_ReadByte(0x0000);
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
        if (error == ERROR)
            {
                UART_PutString("Error occurred during I2C comm to set control register 1\r\n"); 
            }

        /*
        if (ctrl_reg1 != ctrl_reg1_odr_update)
        {
            ctrl_reg1 = ctrl_reg1_odr_update;
        
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
            
            EEPROM_WriteByte(ctrl_reg1_odr_update, 0x0000);
        
            
        }
        */
        
        error_R4 = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_STATUS_REG, &status_reg);
        
        if(error_R4 == NO_ERROR)
        {
            if(status_reg & NEW_DATA_AVALIABLE)
            {
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_X_L, N_ADC_REGISTERS, AccelerometerData);
                
                if(error == NO_ERROR)
                {
                    OutAcc1 = (int16)((AccelerometerData[0] | (AccelerometerData[1] << 8))) >> 4;
                    OutAcc2 = (int16)((AccelerometerData[2] | (AccelerometerData[3] << 8))) >> 4;
                    OutAcc3 = (int16)((AccelerometerData[4] | (AccelerometerData[5] << 8))) >> 4;
                    
                    union{
                        float Out1_conv;
                        uint32 X;
                    }value_x;
                    
                    value_x.Out1_conv = (float)(OutAcc1 * CONVERTION);
                    final_x = value_x.X;
                    
                    union
                    {
                        float Out2_conv;
                        uint32 Y;
                    }value_y;
                    
                    value_y.Out2_conv = (float)(OutAcc2 * CONVERTION);
                    final_y = value_y.Y;
                    
                    union
                    {
                        float Out3_conv;
                        uint32 Z;
                    }value_z;
                    
                    value_z.Out3_conv = (float)(OutAcc3 * CONVERTION);
                    final_z = value_z.Z;
                    
                    
                    DataFrame[1]  = (final_x & 0xFF000000) >> 24;    //|
                    DataFrame[2]  = (final_x & 0x00FF0000) >> 16;    //|
                    DataFrame[3]  = (final_x & 0x0000FF00) >> 8;     //| ---------> pacchetto ADC1  
                    DataFrame[4]  = (final_x & 0x000000FF);          //|
                    DataFrame[5]  = (final_y & 0xFF000000) >> 24;    //|
                    DataFrame[6]  = (final_y & 0x00FF0000) >> 16;    //|
                    DataFrame[7]  = (final_y & 0x0000FF00) >> 8;     //| ---------> pacchetto ADC2  
                    DataFrame[8]  = (final_y & 0x000000FF);          //|
                    DataFrame[9]  = (final_z & 0xFF000000) >> 24;    //|
                    DataFrame[10] = (final_z & 0x00FF0000) >> 16;    //|
                    DataFrame[11] = (final_z & 0x0000FF00) >> 8;     //| ---------> pacchetto ADC3  
                    DataFrame[12] = (final_z & 0x000000FF);          //|
                    
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
