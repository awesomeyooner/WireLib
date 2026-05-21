#include "WireLib/communication/protocols/serial_interface.hpp"

#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "usbd_def.h"


using namespace status_utils;
using namespace string_util;


StatusCode SerialInterface::transmit_bytes(const std::vector<uint8_t>& bytes)
{
    // Transmit via USB FS
    uint8_t transmit_status = CDC_Transmit_FS(
        const_cast<uint8_t*>(bytes.data()), bytes.size()
    );

    // If OK return OK
    return transmit_status == USBD_OK ? StatusCode::OK : StatusCode::FAILED;

} // end of "transmit_bytes(const std::vector<uint8_t>&))"


StatusCode SerialInterface::print(std::string text)
{
    // Convert to byte vector
    std::vector<uint8_t> buffer(text.begin(), text.end());

    // Send the data over
    // Return true if trasmit was USBD_OK
    return transmit_bytes(buffer);

} // end of "print(std::string)"


StatusCode SerialInterface::print(double data)
{
    // Convert data to string and send it over
    return print(to_string(data));

} // end of "print(double)"


StatusCode SerialInterface::println(std::string text)
{
    // Add carriage return and newline
    return print(text + "\r\n");

} // end of println(std::string)


StatusCode SerialInterface::println(double data)
{
    // Convert data to string and send it over
    return println(to_string(data));
    
} // end of println(double)


StatusCode SerialInterface::print_header(std::string header, std::string text)
{
    return println(
        timestamped_header(header, text)
    );

} // end of "print_header(std::string, std::string)"


StatusCode SerialInterface::print_header(std::string header, double data)
{
    return print_header(header, to_string(data));

} // end of "print_header(std::string, std::string)"


StatusCode SerialInterface::info(std::string text)
{
    return print_header("INFO", text);

} // end of "info(std::string)"


StatusCode SerialInterface::info(double data)
{
    return info(to_string(data));

} // end of "info(double)"


StatusCode SerialInterface::debug(std::string text)
{
    return print_header("DEBUG", text);

} // end of "debug(std::string)"


StatusCode SerialInterface::debug(double data)
{
    return debug(to_string(data));

} // end of "debug(double)"


StatusCode SerialInterface::error(std::string text)
{
    return print_header("ERROR", text);

} // end of "error(std::string)"


StatusCode SerialInterface::error(double data)
{
    return error(to_string(data));

} // end of "error(double)"


SerialInterface Serial;