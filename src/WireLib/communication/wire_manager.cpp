#include "WireLib/communication/wire_manager.hpp"


using namespace status_utils;


void WireManager::initialize(int address)
{
    // Start the I2C interface with the given address
    // Wire.begin(address);

    // Link the on recieve and request functions
    // Wire.onReceive(on_recieve);
    // Wire.onRequest(on_request);

} // end of "initialize"


StatusCode WireManager::on_receive(const std::vector<uint8_t>& bytes)
{
    // Shorthand for the read buffer
    std::vector<uint8_t>* read_buffer = RegisterManager::get_read_buffer();

    // Copy the contents of the incoming bytes to RegisterManager's bytes
    read_buffer->assign(bytes.begin(), bytes.end());

    // Update the registers using the incoming data
    return RegisterManager::update();

} // end of "on_recieve"


StatusCode WireManager::on_request()
{
    // Write every byte in the buffer
    // for(uint8_t byte : *RegisterManager::get_write_buffer())
    // {
    //     Wire.write(byte);
    // }

} // end of "on_request"


void WireManager::attach(CommunicationInterface& interface)
{
    // Attach the on_receive callback of the interface to WireManager
    interface.configure_on_receive(
        [](const std::vector<uint8_t>& bytes) -> StatusCode
        {
            return WireManager::on_receive(bytes);
        }
    );
}