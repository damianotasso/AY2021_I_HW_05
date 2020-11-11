/* ====================================================================================================================================
 * Damiano Tasso 944232
 *
 * In the main.c before the infinite loop the UART, I2C, EEPROM, isr_BUTTON are enabled and thanks the Register_Initialization()
 * function, registers are initialized. Also the header and the tail in the DataFrame[] vector, are initialized before the for(;;).
 * 
 * Inside the infinite loop, if the button_flag is HIGH (so the button has been pressed), the program enters in the condition in which  
 * the sampling frequecy is changed, starting from the saved frequency in the EEPROM this is overwriting the new in the same address of 
 * the EEPROM(0x0000). The technique used to develop the updating of the sampling frequency in better explain in the 37-54 raws.
 *
 * After the sampling frequency updating, the code verifies if new data are avaliable thanks the appropriate mask. Inside this condition
 * the read data by the 3 ADC are manipulated in order to be packed in the DataFrame[]. When the data is converted in [m/s^2] a 
 * floating_point have to be sent. The used trick is the union type. The union allows to store different data types in the same memory 
 * location. In this way is possible to allocate the computed float32 (the result of passing in [m/s^2]) into an uint32. So, splittng
 * the 32bit in 4byte is possible to send them with the UART. With this trick, the DataFrame is composed by 14 bytes. The first and the
 * last are the HEADER and TAIL, from 2nd to 13th there are the 4 bytes respectively of the X, Y and Z ADC.
 * ====================================================================================================================================
*/
#include "I2C_protocol.h"
#include "ServiceRoutines.h"
#include "RegisterInit.h"

int main(void)
{
    CyGlobalIntEnable; 
    
    I2C_Peripheral_Start();
    UART_Start();
    EEPROM_Start();
    isr_BUTTON_StartEx(custom_isr_BUTTON);
    
    DataFrame[0] = HEADER;
    DataFrame[DATA_FRAME_SIZE - 1] = TAIL;
        
    CyDelay(10); //"The boot procedure is complete about 5 milliseconds after device power-up."
       
    Register_Initialization();
    
    for(;;)
    {   
        if(button_flag == HIGH)
        {
            button_flag = LOW;                                                             // |
            increment = EEPROM_ReadByte(0x0000) >> 4;                                      // | The variable 'increment' is set as the 8bit inside the 0x0000 EEPROM address
                                                                                           // | shifted on the right. In this way are considered the 4 less significant bits.    
            increment ++;                                                                  // | The variable 'incerment' is incremented by 1.
            if(increment > 6) increment = 1;                                               // | The incremented variable now is the binary coding of the CTRL_REG1 to set the
                                                                                           // | register and update the sampling frequency. But in order to set the right bits
            msb_increment = (increment) << 4;                                              // | in the CTRL_REG1 the binary coding must be re-shifted on the right. 
                                                                                           // | So, doing the 'or' bitwise with the LIS3DH_START_MODE_CTRL_REG1 is possible to
            ctrl_reg1_odr_update = LIS3DH_START_MODE_CTRL_REG1 | msb_increment;            // | obtain the complete byte which set the CTRL_REG1. At this point the new byte is
                                                                                           // | overwritten in the EEPROM, ready to be used for the next updating.
            EEPROM_UpdateTemperature();                                                    // |  
            EEPROM_WriteByte(ctrl_reg1_odr_update, 0x0000);                                // | LIS3DH_START_MODE_CTRL_REG1 -> 00000111 permits to have always enable X,Y,Z axis
                                                                                           // |
            
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1_odr_update);
        
            if (error == ERROR)
            {
                UART_PutString("Error occurred during I2C comm to set control register 1\r\n"); 
            }
        }
            
        error_R4 = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_STATUS_REG, &status_reg);
        
        if(error_R4 == NO_ERROR)
        {
            if(status_reg & NEW_DATA_AVALIABLE)
            {
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_X_L, N_ADC_REGISTERS, AccelerometerData);
                
                if(error == NO_ERROR)
                {
                    OutAcc1 = (int16)((AccelerometerData[0] | (AccelerometerData[1] << 8))) >> 4;
                    OutAcc2 = (int16)((AccelerometerData[2] | (AccelerometerData[3] << 8))) >> 4;
                    OutAcc3 = (int16)((AccelerometerData[4] | (AccelerometerData[5] << 8))) >> 4;
                    
                    value_x.Out1_conv = (float)(OutAcc1 * CONVERTION);
                    final_x = value_x.X;
                    
                    value_y.Out2_conv = (float)(OutAcc2 * CONVERTION);
                    final_y = value_y.Y;
                    
                    value_z.Out3_conv = (float)(OutAcc3 * CONVERTION);
                    final_z = value_z.Z;
                    
                    // DataFrame initialization
                    DataFrame[1]  = (final_x & 0xFF000000) >> 24;    //|
                    DataFrame[2]  = (final_x & 0x00FF0000) >> 16;    //|
                    DataFrame[3]  = (final_x & 0x0000FF00) >> 8;     //| ---------> X data  
                    DataFrame[4]  = (final_x & 0x000000FF);          //|
                    DataFrame[5]  = (final_y & 0xFF000000) >> 24;       //|
                    DataFrame[6]  = (final_y & 0x00FF0000) >> 16;       //|
                    DataFrame[7]  = (final_y & 0x0000FF00) >> 8;        //| ---------> Y data 
                    DataFrame[8]  = (final_y & 0x000000FF);             //|
                    DataFrame[9]  = (final_z & 0xFF000000) >> 24;          //|
                    DataFrame[10] = (final_z & 0x00FF0000) >> 16;          //|
                    DataFrame[11] = (final_z & 0x0000FF00) >> 8;           //| ---------> Z data  
                    DataFrame[12] = (final_z & 0x000000FF);                //|
                    
                    UART_PutArray(DataFrame, DATA_FRAME_SIZE);
                }
                else
                {
                    UART_PutString("Error occurred during I2C comm to read ADCs / temperature output registers\r\n");
                }
            }
        }
    }
}

/* [] END OF FILE */
