/* =====================================================================================================
 * Damiano Tasso 944232
 *
 * In this .h file there are the definition of registers, macro and variables used in the entire project  
 * 
 * =====================================================================================================
*/
#ifndef __GLOBAL_H__
    #define __GLOBAL_H__
    
    #include "cytypes.h"
    #include "project.h"
    #include "EEPROM.h"
    #include "stdio.h"
     
    #define LIS3DH_DEVICE_ADDRESS 0x18
    #define LIS3DH_STATUS_REG 0x27
    #define LIS3DH_CTRL_REG1 0x20
    #define LIS3DH_START_MODE_CTRL_REG1 0x07            // 00000111 This mask initializes only Z-Y-X axis, the 3rd bit (LPen) is 0 in order to have the High-resolutin mode
    #define LIS3DH_CTRL_REG1_1_HZ 0x17                                  
    #define LIS3DH_CTRL_REG1_10_HZ 0x27                                 
    #define LIS3DH_CTRL_REG1_25_HZ 0x37                                 
    #define LIS3DH_CTRL_REG1_50_HZ 0x47                                 
    #define LIS3DH_CTRL_REG1_100_HZ 0x57                                
    #define LIS3DH_CTRL_REG1_200_HZ 0x67                                
    #define LIS3DH_CTRL_REG4 0x23                                       
    #define LIS3DH_CTRL_REG4_HR_MODE_BDU_ACTIVE 0x88    // 10001000 This mask initializes the 3rd(HR --> for high-resolution mode) and 7th(BDU) bits to 1
    #define LIS3DH_TEMP_CFG_REG 0x1F 
    #define LIS3DH_TEMP_CFG_REG_ADC_ACTIVE 0x80         // 10000000 This mask initializes the 7th bit to 1 in order to anable the ADC 
    #define LIS3DH_OUT_X_L 0x28                         // It is defined only the OUT_X_L register because the MultiRead() function permits to read the contiguous registers
    
    #define LOW 0 
    #define HIGH 1
    #define NEW_DATA_AVALIABLE 0x08                                 // 00001000 This mask is used to control the 3rd bit (STATUS_REGISTER) which determines if new data are avaliable
    #define N_ADC_REGISTERS 6                                       // N^ of ADC registers which must be read
    #define BYTES_TO_SEND 12
    #define DATA_FRAME_SIZE 1 + BYTES_TO_SEND + 1
    #define HEADER 0xA0
    #define TAIL 0xC0
    #define m_s2_CONVERTER 9.8066                                   // 1 m/s^2 == 9.8066 * 1 g
    #define SENSITIVITY 1                                           // (from datasheet)[So]=[mg/digit] ---> corresponding Sensitivity from the chosen CTRL_REG4(bit 4-5) init.
    #define CONVERTER 0.001                                         // This macro is used to transform the Sensitivity from [mg/digit] --> [g/digit]  
    #define CONVERTION m_s2_CONVERTER * CONVERTER * SENSITIVITY     // This macro is used to convert the incoming data in the correct scale of [m/s^2] 
    
        
    
    typedef enum {
        NO_ERROR,           // No error generated
        ERROR               //< Error generated
    } ErrorCode;
    
    uint8_t error;
    uint8_t error_R1;
    uint8_t error_R2;
    uint8_t error_R3;
    uint8_t error_R4;
    uint8_t counter;
    uint8_t button_flag;
    char message[50];
    uint8_t increment;
    uint8_t msb_increment;
    uint8_t ctrl_reg1;
    uint8_t ctrl_reg1_odr_update;
    uint8_t ctrl_reg4;
    uint8_t tmp_cfg_reg;
    uint8_t status_reg;
    
    uint8_t DataFrame[DATA_FRAME_SIZE];
    uint8_t AccelerometerData[N_ADC_REGISTERS];
    int16 OutAcc1;
    int16 OutAcc2;
    int16 OutAcc3;
    int32 final_x;
    int32 final_y;
    int32 final_z;
    
    union
    {
        float Out1_conv;
        uint32 X;
    }value_x;
    
    union
    {
    float Out2_conv;
    uint32 Y;
    }value_y;
    
    union
                    {
    float Out3_conv;
    uint32 Z;
    }value_z;
    
    
    
#endif
/* [] END OF FILE */