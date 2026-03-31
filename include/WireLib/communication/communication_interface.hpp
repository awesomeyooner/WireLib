#ifndef COMMUNICATION_INTERFACE_HPP
#define COMMUNICATION_INTERFACE_HPP

// #include "helpers/system.hpp"

#include <string>
#include <vector>
#include <functional>


class CommunicationInterface
{

    public:

        void configure_on_receive(std::function<bool(const std::vector<uint8_t>&)> callback);

        virtual bool on_receive(uint8_t* buffer, uint32_t length);

        virtual bool transmit_bytes(const std::vector<uint8_t>& bytes);

    private:

        std::function<bool(const std::vector<uint8_t>&)> m_receive_callback;

        std::vector<uint8_t> m_read_buffer;


}; // class CommunicationInterface


#endif // COMMUNICATION_INTERFACE_HPP