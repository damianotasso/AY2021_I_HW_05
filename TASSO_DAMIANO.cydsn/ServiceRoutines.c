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
    
    button_flag = HIGH;
    
}

/* [] END OF FILE */
