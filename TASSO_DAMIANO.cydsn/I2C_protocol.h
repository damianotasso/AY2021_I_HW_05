/* ====================================================================================
 * Damiano Tasso 944232
 *
 * The same function, seen during lessons, are used in order to Read & Write Registers.
 * In this file there is the declaration of the prototyme of functions.
 * ====================================================================================
*/
#ifndef __I2C_PROTOCOL_H__
    #define __I2C_PROTOCOL_H__
    
    #include "global.h"
    #include "I2C_Master.h"
    
    ErrorCode I2C_Peripheral_Start(void);
    
    ErrorCode I2C_Peripheral_Stop(void);
    
    // Read one byte over I2C.
    ErrorCode I2C_Peripheral_ReadRegister(uint8_t device_address, uint8_t register_address, uint8_t* data);
    
    // Read multiple bytes over I2C.
    ErrorCode I2C_Peripheral_ReadRegisterMulti(uint8_t device_address, uint8_t register_address, uint8_t register_count, uint8_t* data);
    
    // Write a byte over I2C.
    ErrorCode I2C_Peripheral_WriteRegister(uint8_t device_address, uint8_t register_address, uint8_t data);
    
#endif
/* [] END OF FILE */
