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
    
    incremento = EEPROM_ReadByte(0x0000) >> 4;
    
    incremento ++;
    if(incremento > 7) incremento = 1;
    
    msb_incremento = (incremento) << 4; 
    
    ctrl_reg1_odr_update = LIS3DH_START_MODE_CTRL_REG1 | msb_incremento;
    
    EEPROM_WriteByte(ctrl_reg1_odr_update, 0x0000);
}

/* [] END OF FILE */
