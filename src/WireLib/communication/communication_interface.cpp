#include "WireLib/communication/communication_interface.hpp"


void CommunicationInterface::configure_on_receive(std::function<bool(const std::vector<uint8_t>&)> callback)
{
    m_receive_callback = callback;

} // end of "configure_on_receive(std::function<bool(const std::vector<uint8_t>&)>)"


bool CommunicationInterface::on_receive(uint8_t* buffer, uint32_t length)
{
    // Fill the read buffer
    m_read_buffer.assign(buffer, buffer + length);

    // If the callback is set
    // Then call it
    if(m_receive_callback)
        return m_receive_callback(m_read_buffer);

    return true;

} // end of "on_receive(uint8_t*, uint32_t)"


bool CommunicationInterface::transmit_bytes(const std::vector<uint8_t>& bytes)
{
    // Implement!!
    
} // end of "transmit_bytes(const std::vector<uint8_t>&)"
