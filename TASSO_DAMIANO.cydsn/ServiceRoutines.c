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
#include "ServiceRoutines.h"

CY_ISR(custom_isr_BUTTON)
{
    EEPROM_UpdateTemperature();
    counter_button ++ ;
    
    switch(counter_button)
    {
        case 0:
            EEPROM_WriteByte(LIS3DH_CTRL_REG1_1_HZ, 0x00);
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, LIS3DH_CTRL_REG1_1_HZ);
            break;
        case 1:
            EEPROM_WriteByte(LIS3DH_CTRL_REG1_10_HZ, 0x00);
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, LIS3DH_CTRL_REG1_10_HZ);
            break;
        case 2:
            EEPROM_WriteByte(LIS3DH_CTRL_REG1_25_HZ, 0x00);
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, LIS3DH_CTRL_REG1_25_HZ);
            break;
        case 3:
            EEPROM_WriteByte(LIS3DH_CTRL_REG1_50_HZ, 0x00);
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, LIS3DH_CTRL_REG1_50_HZ);
            break;
        case 4:
            EEPROM_WriteByte(LIS3DH_CTRL_REG1_100_HZ, 0x00);
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, LIS3DH_CTRL_REG1_100_HZ);
            break;
        case 5:
            EEPROM_WriteByte(LIS3DH_CTRL_REG1_200_HZ, 0x00);
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, LIS3DH_CTRL_REG1_200_HZ);
            counter_button = 0;
            break;
    }
}

/* [] END OF FILE */
