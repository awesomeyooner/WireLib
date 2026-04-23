#include "WireLib/communication/communication_interface.hpp"


using namespace status_utils;


void CommunicationInterface::configure_on_receive(std::function<StatusCode(const std::vector<uint8_t>&)> callback)
{
    m_receive_callback = callback;

} // end of "configure_on_receive(std::function<bool(const std::vector<uint8_t>&)>)"


StatusCode CommunicationInterface::on_receive(uint8_t* buffer, int length)
{
    // Fill the read buffer
    m_read_buffer.assign(buffer, buffer + length);

    // If the callback is set
    // Then call it
    if(m_receive_callback)
        return m_receive_callback(m_read_buffer);

    return StatusCode::OK;

} // end of "on_receive(uint8_t*, int)"