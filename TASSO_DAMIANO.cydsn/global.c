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

#include "global.h"

uint8_t error = 0;
uint8_t error_R1 = 0;
uint8_t error_R2 = 0;
uint8_t error_R3 = 0;
uint8_t error_R4 = 0;
uint8_t counter = 0;
uint8_t counter_button = 0;
uint8_t button_flag = LOW;
char message[50] = {'\0'};
uint8_t ctrl_reg1 = 0;
uint8_t ctrl_reg4 = 0;
uint8_t tmp_cfg_reg = 0;
uint8_t status_reg = 0;
int32 final_x = 0;
int32 final_y = 0;
int32 final_z = 0;

/* [] END OF FILE */
