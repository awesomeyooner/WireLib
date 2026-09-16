#include "WireLib/communication/protocols/i2c/i2c_api.hpp"
#include "gpio.h"


void HAL_I2C_AddrCallback(I2C_HandleTypeDef* hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);

    I2C.on_address(hi2c, TransferDirection, AddrMatchCode);

} // end of "HAL_I2C_AddrCallback(I2C_HandleTypeDef*, uint8_t, uint8_t)"


void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef* hi2c)
{
    I2C.on_listen_complete(hi2c);

} // end of "HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef*)"
