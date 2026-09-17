#include "WireLib/communication/protocols/i2c/i2c_interface.hpp"


using namespace std;
using namespace status_utils;


I2CInterface::I2CInterface()
    : CommunicationInterface()
{
    m_raw_read_buffer.resize(DEFAULT_READ_BUFFER_SIZE);

} // end of "I2CInterface()"


void I2CInterface::set_i2c(I2C_HandleTypeDef* i2c)
{
    m_i2c = i2c;

    HAL_I2C_EnableListen_IT(m_i2c);

} // end of "set_i2c(I2C_HandleTypeDef*)"


// Just copy to the write buffer because `on_address` handles the actual data transmission
StatusCode I2CInterface::transmit_bytes(const std::vector<uint8_t>& bytes)
{
    copy_to_write_buffer(bytes);

    return StatusCode::OK;

} // end of "transmit_bytes(const std::vector<uint8_t>&)"


void I2CInterface::on_address(I2C_HandleTypeDef* hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
    // Check if it's the right i2c that triggered this
    if(m_i2c->Instance != hi2c->Instance)
        return;

    // Master wants to transmit data
    if(TransferDirection == I2C_DIRECTION_TRANSMIT)
        HAL_I2C_Slave_Seq_Receive_IT(hi2c, m_raw_read_buffer.data(), m_raw_read_buffer.size(), I2C_FIRST_AND_LAST_FRAME);

    // Master wants to receive data
    else if(TransferDirection == I2C_DIRECTION_RECEIVE)
        HAL_I2C_Slave_Seq_Transmit_IT(hi2c, m_write_buffer.data(), m_write_buffer.size(), I2C_FIRST_AND_LAST_FRAME);
        
        // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);

} // end of "on_address(I2C_HandleTypeDef*, uint8_t, uint8_t)"


void I2CInterface::on_listen_complete(I2C_HandleTypeDef* hi2c)
{
    // Check if it's the right i2c that triggered this
    if(m_i2c->Instance != hi2c->Instance)
        return;

    uint32_t num_bytes = m_raw_read_buffer.size() - hi2c->XferCount;

    // Only call the on_receive callback when there's bytes read
    if(num_bytes != 0)
    {
        on_receive(
            m_raw_read_buffer.data(),
            num_bytes
        );

    }

    HAL_I2C_EnableListen_IT(hi2c);
     
} // end of "on_listen_complete(I2C_HandleTypeDef*)"


I2CInterface I2C = I2CInterface();