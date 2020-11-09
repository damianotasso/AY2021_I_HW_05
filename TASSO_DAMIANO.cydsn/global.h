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
#ifndef __GLOBAL_H__
    #define __GLOBAL_H__
    
    #include "cytypes.h"
    #include "project.h"
    #include "EEPROM.h"
    #include "stdio.h"
    
    #define LOW 0 
    #define HIGH 1
    
    #define LIS3DH_DEVICE_ADDRESS 0x18
    #define LIS3DH_STATUS_REG 0x27
    #define LIS3DH_CTRL_REG1 0x20
    #define LIS3DH_START_MODE_CTRL_REG1 0x17  // --> 00010111 inizializza ad 1 Hz inizialmente, in più mette a zero Lpen e ad 1 Z-Y-X axis
    #define LIS3DH_CTRL_REG1_1_HZ 0x17
    #define LIS3DH_CTRL_REG1_10_HZ 0x27
    #define LIS3DH_CTRL_REG1_25_HZ 0x37
    #define LIS3DH_CTRL_REG1_50_HZ 0x47
    #define LIS3DH_CTRL_REG1_100_HZ 0x57
    #define LIS3DH_CTRL_REG1_200_HZ 0x67
    #define LIS3DH_CTRL_REG4 0x23
    //#define LIS3DH_HR_MODE_CTRL_REG4 0x08     
    #define LIS3DH_CTRL_REG4_HR_MODE_BDU_ACTIVE 0x88 // --> 10001000 inizializza ad 1 la BDU (per ADC) in più inizializza ad 1 il bit HR per High Resolution
    #define LIS3DH_TEMP_CFG_REG 0x1F 
    #define LIS3DH_TEMP_CFG_REG_ADC_ACTIVE 0x80
    #define LIS3DH_OUT_X_L 0x28
    #define LIS3DH_OUT_X_H 0x29
    /*#define LIS3DH_OUT_ADC2_L 0x0A
    #define LIS3DH_OUT_ADC2_H 0x0B
    #define LIS3DH_OUT_ADC3_L 0x0C
    #define LIS3DH_OUT_ADC3_H 0x0D*/
    
    #define NEW_DATA_AVALIABLE 0xFF
    #define N_ADC_REGISTERS 6
    #define BYTES_TO_SEND 6
    #define DATA_FRAME_SIZE 1 + BYTES_TO_SEND + 1
    #define HEADER 0xA0
    #define TAIL 0xC0
    #define m_s2_CONVERTER 9.8066
    #define CONVERTER 1000
    #define CONVERTION m_s2_CONVERTER * CONVERTER
        
    
    typedef enum {
        NO_ERROR,           ///< No error generated
        ERROR               ///< Error generated
    } ErrorCode;
    
    uint8_t error;
    uint8_t error_R1;
    uint8_t error_R2;
    uint8_t error_R3;
    uint8_t error_R4;
    uint8_t counter;
    uint8_t counter_button;
    uint8_t button_flag;
    char message[50];
    uint8_t ctrl_reg1;
    uint8_t ctrl_reg4;
    uint8_t tmp_cfg_reg;
    uint8_t status_reg;
    
    uint8_t DataFrame[DATA_FRAME_SIZE];
    uint8_t AccelerometerData[BYTES_TO_SEND];
    uint8_t AccelerometerDataConverted[BYTES_TO_SEND];
    int16 OutAcc1;
    int16 OutAcc2;
    int16 OutAcc3;
    float OutAcc1_conv;
    float OutAcc2_conv;
    float OutAcc3_conv;
    
    
    
#endif
/* [] END OF FILE */
