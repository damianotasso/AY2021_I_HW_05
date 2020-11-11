/* ========================================
 * Damiano Tasso 944232
 *
 * This .c file is implemented the function which permits the initialization of:
 * - LIS3DH_CTRL_REG1
 * - LIS3DH_CTRL_REG4
 * - LIS3DH_TEMP_CFG_REG
 * 
 * In the functios are both implemented the writing and the reading of the registers.
 * The LIS3DH_CTRL_REG1 is set with the byte saved on the EEPROM(address 0x0000) set 
 * to 0x17 by defalut, which correspod to 1HZ ADC sampling frequancy and menaged with 
 * the button.
 * ========================================
*/
#include "RegisterInit.h"

void Register_Initialization(void)
{
    UART_Start();
    UART_PutString("**************\r\n");
    UART_PutString("** I2C Scan **\r\n");
    UART_PutString("**************\r\n");
    
    CyDelay(100);
    
    /******************************************/
    /*            I2C Writing                 */
    /******************************************/
    
    /***  CTRL_REG1 Writing in the start condition    ***/
    
    ctrl_reg1 = EEPROM_ReadByte(0x0000);
    
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
    
    if (error == ERROR)
    {
        UART_PutString("Error occurred during I2C comm to set control register 1\r\n");  
        }
    
    /***  CTRL_REG4 Writing in the right condition    ***/
    
    if(ctrl_reg4 != LIS3DH_CTRL_REG4_HR_MODE_BDU_ACTIVE)
    {
        ctrl_reg4 = LIS3DH_CTRL_REG4_HR_MODE_BDU_ACTIVE;
        
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4, ctrl_reg4);
        
        if(error == ERROR)
        {
            UART_PutString("Error occurred during I2C comm to set control register 4\r\n");;
        }
    }
    
    /***  TMP_CFG_REG Writing    ***/
    
    if(tmp_cfg_reg != LIS3DH_TEMP_CFG_REG_ADC_ACTIVE)
    {
        tmp_cfg_reg = LIS3DH_TEMP_CFG_REG_ADC_ACTIVE;
        
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_TEMP_CFG_REG, tmp_cfg_reg);
        
        if(error == ERROR)
        {
            UART_PutString("Error occurred during I2C comm to set temperature config register to enable ADC\r\n");
        }
    }
    
    UART_PutString("\n\n");
    
    /******************************************/
    /*            I2C Reading                 */
    /******************************************/
    
    UART_PutString("\r\nReading Registers' values..\r\n");
    
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
}
/* [] END OF FILE */