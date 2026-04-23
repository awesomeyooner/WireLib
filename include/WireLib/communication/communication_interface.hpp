#ifndef COMMUNICATION_INTERFACE_HPP
#define COMMUNICATION_INTERFACE_HPP

// #include "helpers/system.hpp"

#include <string>
#include <vector>
#include <functional>

#include "EmbeddedLib/util/status.hpp"

using namespace status_utils;


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


class CommunicationInterface
{

    public:

        void configure_on_receive(std::function<bool(const std::vector<uint8_t>&)> callback);

        virtual StatusCode on_receive(uint8_t* buffer, uint32_t length);

        virtual StatusCode transmit_bytes(const std::vector<uint8_t>& bytes);

    private:

        std::function<StatusCode(const std::vector<uint8_t>&)> m_receive_callback;

        std::vector<uint8_t> m_read_buffer;


}; // class CommunicationInterface


#endif // COMMUNICATION_INTERFACE_HPP