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

    // Transmit any bytes that need to be sent
    return m_interface->transmit_bytes(RegisterManager::get_write_buffer());

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