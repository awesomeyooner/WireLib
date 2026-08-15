#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <cstdint>
#include <functional>

#include "EmbeddedLib/status.hpp"

#include "WireLib/util/byte_converter.hpp"


// /**
//  * @brief Base abstraction for Requests, to be used for
//  * std::unordered_map
//  * 
//  */
// class RequestBase
// {
//     RequestBase() = default;
//     virtual ~RequestBase() = default;

//     virtual std::vector<uint8_t> get_bytes();

// }; // class RequestBase


/**
 * @brief An initial Request byte is sent to the microcontroller to let it know what
 * exactly to send, then the microcontroller (what you're writing the firmware for) sends the data back
 * to the host
 * 
 */
template <typename T>
class Request
{

    public:

        // The register byte
        uint8_t m_reg;

        // The length of the data packet to send
        int m_length;

        // The function to send the data back to the host. Returns the data type this request is assigned to.
        // Once this request has been updated, the returned value will be sent over the specifically assigned protocol
        // in RegisterManager
        std::function<status_utils::StatusedValue<T>()> m_runnable;

        Request(uint8_t reg, std::function<status_utils::StatusedValue<T>()> runnable);

        Request(uint8_t reg, std::function<T()> runnable);

        status_utils::StatusedValue<std::vector<uint8_t>> get_bytes();

}; // struct Request


// Include implementation file for template methods
#include "WireLib/registers/request.tpp"


#endif // REQUEST_STRUCT_HPP