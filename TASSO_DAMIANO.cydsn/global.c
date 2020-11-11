/** ====================================================================================
 * Damiano Tasso 944232
 *
 * In this .c file there are the initializations of variables used in the entire project  
 * 
 * =====================================================================================
*/

#include "global.h"

uint8_t error = 0;
uint8_t error_R1 = 0;
uint8_t error_R2 = 0;
uint8_t error_R3 = 0;
uint8_t error_R4 = 0;
uint8_t counter = 0;
uint8_t increment = 0;
uint8_t msb_increment = 0;
uint8_t button_flag = LOW;
char message[50] = {'\0'};
uint8_t ctrl_reg1 = 0;
uint8_t ctrl_reg4 = 0;
uint8_t ctrl_reg1_odr_update;
uint8_t tmp_cfg_reg = 0;
uint8_t status_reg = 0;
int32 final_x = 0;
int32 final_y = 0;
int32 final_z = 0;

/* [] END OF FILE */