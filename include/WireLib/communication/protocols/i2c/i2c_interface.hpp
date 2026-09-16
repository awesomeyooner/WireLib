#ifndef I2C_INTERFACE_HPP
#define I2C_INTERFACE_HPP


#include "i2c.h"

#include "EmbeddedLib/system.hpp"
#include "EmbeddedLib/util/string_formatter.hpp"

#include "WireLib/communication/communication_interface.hpp"

#include <string>
#include <vector>
#include <functional>


/**
 * @brief I2C abstraction to be used as slave. Please call `set_i2c()` before using any methods
 * 
 * Please enable the NVIC interrupts (both event and error)
 */
class I2CInterface : public CommunicationInterface
{
    
    public:

        I2CInterface();

        void set_i2c(I2C_HandleTypeDef* i2c);

        status_utils::StatusCode transmit_bytes(const std::vector<uint8_t>& bytes) override;

        void on_address(I2C_HandleTypeDef* hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);

        void on_listen_complete(I2C_HandleTypeDef* hi2c);

    private:

        // The default size of the raw read buffer in bytes
        static constexpr int DEFAULT_READ_BUFFER_SIZE = 64;

        // The I2C handle pointer, like &hi2c1
        I2C_HandleTypeDef* m_i2c = nullptr;

        // The buffer to store the raw data when using `HAL_I2C_Slave_Seq_Receive_IT`
        std::vector<uint8_t> m_raw_read_buffer;

        // The default timeout in milliseconds
        int m_timeout_ms = 100;

}; // class I2CInterface : public CommunicationInterface


// Global Object like Arduino
extern I2CInterface I2C;


#endif // I2C_INTERFACE_HPP