#ifndef COMMUNICATION_INTERFACE_HPP
#define COMMUNICATION_INTERFACE_HPP

// #include "helpers/system.hpp"

#include <string>
#include <vector>
#include <functional>

#include "EmbeddedLib/util/status.hpp"


/**
 * @brief Describes the state of the communication (wire) interface
 * 
 */
enum class WireState
{
    READY,  // The stack is ready to recieve a new packet 
    ONGOING,  // The stack is currently recieving packets and is waiting for the rest of the packets to arrive  
    FINISHED  // The stack has recieved all of the needed packets
};


/**
 * @brief Barebones Parent class for all implemented Communication Protocols.
 * Examples are Serial, CAN, I2C, SPI, etc
 * 
 */
class CommunicationInterface
{

    public:

        CommunicationInterface() = default;
        virtual ~CommunicationInterface() = default;

        /**
         * @brief Assign the callback function to call when a packet is recieved
         * 
         * @param callback `std::function<status_utils::StatusCode(const std::vector<uint8_t>&)>` Function that takes in
         * a vector of bytes as a parameter and returns a `status_utils::StatusCode` for the status of the execution. OK if good
         */
        virtual void configure_on_receive(std::function<status_utils::StatusCode(const std::vector<uint8_t>&)> callback);

        /**
         * @brief The function to call when a packet is recieved from the backend implementation
         * 
         * @param buffer `uint8_t*` Dynamic byte array for the incoming data
         * @param length `uint32_t` The length of the array
         * @return `status_utils::StatusCode` OK if everything is good.  
         */
        virtual status_utils::StatusCode on_receive(uint8_t* buffer, int length);

        /**
         * @brief Pure virtual function, needs to be implemented for the communication protocol. This method is
         * used to send a vector of bytes to the host
         * 
         * @param bytes `const std::vector<uint8_t>&` The byte vector to send 
         * @return `status_utils::StatusCode` OK if everytihng is good 
         */
        virtual status_utils::StatusCode transmit_bytes(const std::vector<uint8_t>& bytes) = 0;

    // Protected since we want all child classes to have access
    protected:

        // The function callback
        std::function<status_utils::StatusCode(const std::vector<uint8_t>&)> m_receive_callback;

        // The byte vector of all read data
        std::vector<uint8_t> m_read_buffer;


}; // class CommunicationInterface


#endif // COMMUNICATION_INTERFACE_HPP