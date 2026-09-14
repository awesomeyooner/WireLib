#include "WireLib/communication/protocols/serial_api.hpp"

#include "WireLib/communication/protocols/serial_interface.hpp"


bool Serial_on_receive(uint8_t* buffer, uint32_t length)
{
    // Call the C++ version
    return Serial.on_receive(buffer, static_cast<int>(length)) == status_utils::StatusCode::OK;

} // end of "Serial_on_receive(uint8_t*, int*)"


void Serial_update_connection_status(uint8_t* pbuf)
{
    // Call the C++ version
    return Serial.update_connection_status(pbuf);

} // end of Serial_udpate_connection_status