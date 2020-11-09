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
#ifndef __I2C_PROTOCOL_H__
    #define __I2C_PROTOCOL_H__
    
    #include "global.h"
    #include "I2C_Master.h"
    
    ErrorCode I2C_Peripheral_Start(void);
    
    ErrorCode I2C_Peripheral_Stop(void);
    
    /**
    *   \brief Read one byte over I2C.
    *   
    *   This function performs a complete reading operation over I2C from a single
    *   register.
    *   \param device_address I2C address of the device to talk to.
    *   \param register_address Address of the register to be read.
    *   \param data Pointer to a variable where the byte will be saved.
    */
    ErrorCode I2C_Peripheral_ReadRegister(uint8_t device_address, uint8_t register_address, uint8_t* data);
    
    /** 
    *   \brief Read multiple bytes over I2C.
    *   
    *   This function performs a complete reading operation over I2C from multiple
    *   registers.
    *   \param device_address I2C address of the device to talk to.
    *   \param register_address Address of the first register to be read.
    *   \param register_count Number of registers we want to read.
    *   \param data Pointer to an array where data will be saved.
    */
    ErrorCode I2C_Peripheral_ReadRegisterMulti(uint8_t device_address, uint8_t register_address, uint8_t register_count, uint8_t* data);
    
    /** 
    *   \brief Write a byte over I2C.
    *   
    *   This function performs a complete writing operation over I2C to a single 
    *   register.
    *   \param device_address I2C address of the device to talk to.
    *   \param register_address Address of the register to be written.
    *   \param data Data to be written
    */
    ErrorCode I2C_Peripheral_WriteRegister(uint8_t device_address, uint8_t register_address, uint8_t data);
    
#endif
/* [] END OF FILE */
