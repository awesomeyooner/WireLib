#include "WireLib/communication/wire_manager.hpp"


void WireManager::initialize(int address)
{
    // Start the I2C interface with the given address
    Wire.begin(address);

    // Link the on recieve and request functions
    Wire.onReceive(on_recieve);
    Wire.onRequest(on_request);

} // end of "initialize"


void WireManager::on_recieve(int num_bytes)
{
    // Shorthand for the read buffer
    std::vector<uint8_t>* read_buffer = RegisterManager::get_read_buffer();

    // Clear the buffer
    read_buffer->clear();

    // Store all the read data into the buffer
    while(Wire.available())
    {
        uint8_t incoming = Wire.read();

        read_buffer->push_back(incoming);
    }

    // Update the registers using the incoming data
    RegisterManager::update();

} // end of "on_recieve"


void WireManager::on_request()
{
    // Write every byte in the buffer
    for(uint8_t byte : *RegisterManager::get_write_buffer())
    {
        Wire.write(byte);
    }

} // end of "on_request"