/* * ======================================================================================================================
 * Damiano Tasso 944232
 * 
 * The only thing that the interrupt do is enable a flag when the button is pressed. This flag is used in the main.c 
 * to menage the change of the ADC sampling frequency. The reason about to execute the frequency change in the main.c 
 * is due tothe EEPROM. In particular, when the ADC frequency is changed, this implies that a new initilization of the  
 * CTRL_REG1 must be done ad also saved in a EEPROM address. So, the used EEPROM's fuctions are blockers and is inorrect
 * use them inside the isr. 
 * ======================================================================================================================
*/
#include "ServiceRoutines.h"

CY_ISR(custom_isr_BUTTON)
{      
    button_flag = HIGH;
}

/* [] END OF FILE */
