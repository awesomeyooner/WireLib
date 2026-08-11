#include "WireLib/communication/wire_manager.hpp"


using namespace status_utils;


StatusCode WireManager::on_receive(const std::vector<uint8_t>& bytes)
{
    // Copy the contents of the incoming bytes to RegisterManager's bytes
    RegisterManager::set_read_buffer(bytes);

    // Update the registers using the incoming data
    StatusCode update_status = RegisterManager::update();

    // If update isn't OK 
    // Then return early
    if(update_status != StatusCode::OK)
        return update_status;

    if(m_interface == nullptr)
        return StatusCode::FAILED;

    // Transmit any bytes that need to be sent
    StatusCode transmit_status = m_interface->transmit_bytes(RegisterManager::get_write_buffer());

    // Clear the buffer to prepare for other writes
    // This is safe because `transmit_bytes` copies the values, it doesn't use a pointer to the argument
    RegisterManager::clear_write_buffer();

    return transmit_status;

} // end of "on_recieve"


void WireManager::attach(CommunicationInterface& interface)
{
    // Attach the on_receive callback of the interface to WireManager
    interface.configure_on_receive(
        [](const std::vector<uint8_t>& bytes) -> StatusCode
        {
            return WireManager::on_receive(bytes);
        }
    );

    m_interface = &interface;
     
} // end of "attach(CommunicationInterface&)"