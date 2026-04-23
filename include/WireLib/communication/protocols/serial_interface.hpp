#ifndef SERIAL_HPP
#define SERIAL_HPP

#include "EmbeddedLib/System.hpp"
#include "EmbeddedLib/util/string_util.hpp"

#include "WireLib/communication/communication_interface.hpp"

#include <string>
#include <vector>
#include <functional>


class SerialInterface : public CommunicationInterface
{

    public:

        status_utils::StatusCode transmit_bytes(const std::vector<uint8_t>& bytes) override;

        status_utils::StatusCode print(std::string text);

        status_utils::StatusCode print(double data);

        status_utils::StatusCode println(std::string text);

        status_utils::StatusCode println(double data);

        status_utils::StatusCode print_header(std::string header, std::string text);

        status_utils::StatusCode print_header(std::string header, double data);

        status_utils::StatusCode info(std::string text);

        status_utils::StatusCode info(double data);

        status_utils::StatusCode debug(std::string text);

        status_utils::StatusCode debug(double data);

        status_utils::StatusCode error(std::string text);

        status_utils::StatusCode error(double data);

}; // class Serial


#endif // SERIAL_HPP