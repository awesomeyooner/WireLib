#ifndef SERIAL_INTERFACE_HPP
#define SERIAL_INTERFACE_HPP


#include "EmbeddedLib/system.hpp"
#include "EmbeddedLib/util/string_formatter.hpp"

#include "WireLib/communication/communication_interface.hpp"

#include <string>
#include <vector>
#include <functional>


class SerialInterface : public CommunicationInterface
{

    public:

        /**
         * @brief Transmit Raw Bytes over USB / Serial
         * 
         * @param bytes `const std::vector<uint8_t>&` Byte Vector to send
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode transmit_bytes(const std::vector<uint8_t>& bytes) override;

        /**
         * @brief Send a string over USB / Serial
         * 
         * @param text `std::string` The string to send
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode print(std::string text);

        /**
         * @brief Send a double over USB / Serial
         * 
         * @param data `double` The double to send
         * @param decimals `int = 3` The number of decimals to print. Only goes up to `9`
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode print(double data, int decimals = 3);

        /**
         * @brief Send a string over USB / Serial with CRLF
         * 
         * @param text `std::string` The string to send
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode println(std::string text);

        /**
         * @brief Send a double over USB / Serial with CRLF
         * 
         * @param data `double` The double to send
         * @param decimals `int = 3` The number of decimals to print. Only goes up to `9`
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode println(double data, int decimals = 3);

        /**
         * @brief Send a string over USB / Serial with a timestamped header and CRLF
         * 
         * @param header `std::string` The header to use
         * @param text `std::string` The string to send
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode print_header(std::string header, std::string text);

        /**
         * @brief Send a double over USB / Serial with a timestamped header and CRLF
         * 
         * @param header `std::string` The header to use
         * @param data `double` The double to send
         * @param decimals `int = 3` The number of decimals to print. Only goes up to `9`
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode print_header(std::string header, double data, int decimals = 3);

        /**
         * @brief Send a string over USB / Serial with a timestamped header of INFO and CRLF
         * 
         * @param text `std::string` The string to send
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode info(std::string text);

        /**
         * @brief Send a double over USB / Serial with a timestamped header of INFO and CRLF
         * 
         * @param data `double` The double to send
         * @param decimals `int = 3` The number of decimals to print. Only goes up to `9`
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode info(double data, int decimals = 3);

        /**
         * @brief Send a string over USB / Serial with a timestamped header of DEBUG and CRLF
         * 
         * @param text `std::string` The string to send
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode debug(std::string text);

        /**
         * @brief Send a double over USB / Serial with a timestamped header of DEBUG and CRLF
         * 
         * @param data `double` The double to send
         * @param decimals `int = 3` The number of decimals to print. Only goes up to `9`
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode debug(double data, int decimals = 3);

        /**
         * @brief Send a string over USB / Serial with a timestamped header of ERROR and CRLF
         * 
         * @param text `std::string` The string to send
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode error(std::string text);

        /**
         * @brief Send a double over USB / Serial with a timestamped header of DEBUG and CRLF
         * 
         * @param data `double` The double to send
         * @param decimals `int = 3` The number of decimals to print. Only goes up to `9`
         * @return `status_utils::StatusCode` `OK` if transmit was successful. `FAILED` otherwise
         */
        status_utils::StatusCode error(double data, int decimals = 3);

        /**
         * @brief HAL level update function to check whether a COM port is opened. This updates `m_is_connected()`
         * and the status can be gotten with `is_connected()`
         * 
         * @param pbuf `uint8_t*`
         */
        void update_connection_status(uint8_t* pbuf);

        /**
         * @brief Get whether the COM port is opened or not. This doesn't check if the USB is connected, but if it is connected
         * AND an active COM port terminal is opened too
         * 
         * @return `true` If COM port opened
         * @return `false` Otherwise
         */
        bool is_connected();
    
    private:

        // True if the USB is connected and COM port is opened
        bool m_is_connected = false;

}; // class Serial


// Global Object like Arduino
extern SerialInterface Serial;


#endif // SERIAL_INTERFACE_HPP