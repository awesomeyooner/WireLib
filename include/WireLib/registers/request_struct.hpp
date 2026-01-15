#ifndef REQUEST_STRUCT_HPP
#define REQUEST_STRUCT_HPP

#include <cstdint>
#include <functional>

#include "EmbeddedLib/util/status.hpp"

#include "WireLib/util/byte_converter.hpp"


/**
 * @brief An initial Request byte is sent to the microcontroller to let it know what
 * exactly to send, then the microcontroller (what you're writing the firmware for) sends the data back
 * to the host
 * 
 */
struct Request
{
    // The register byte
    uint8_t m_reg;

    // The length of the data packet to send
    int m_length;

    // The function to send the data back to the host
    std::function<status_utils::StatusCode()> m_runnable;


    /**
     * @brief Makes a request that sends the double associated with `value` and stores it
     * to the write buffer to write back to the host
     * 
     * @param reg `uint8_t` The register this is associated with
     * @param value `double*` The pointer to the value to send back to the host
     * @param write_buffer `std::vector<uint8_t>*` The pointer to the write buffer for
     * the specific communication layer of your choosing
     * @return `Request` The associated request struct 
     */
    static Request make_double(uint8_t reg, double* value, std::vector<uint8_t>* write_buffer);

    /**
     * @brief Makes a request that sends the float associated with `value` and stores it
     * to the write buffer to write back to the host
     * 
     * @param reg `uint8_t` The register this is associated with
     * @param value `float*` The pointer to the value to send back to the host
     * @param write_buffer `std::vector<uint8_t>*` The pointer to the write buffer for
     * the specific communication layer of your choosing
     * @return `Request` The associated request struct 
     */
    static Request make_float(uint8_t reg, float* value, std::vector<uint8_t>* write_buffer);

    /**
     * @brief Makes a request that sends the byte associated with `value` and stores it
     * to the write buffer to write back to the host
     * 
     * @param reg `uint8_t` The register this is associated with
     * @param value `int8_t*` The pointer to the value to send back to the host
     * @param write_buffer `std::vector<uint8_t>*` The pointer to the write buffer for
     * the specific communication layer of your choosing
     * @return `Request` The associated request struct 
     */
    static Request make_byte(uint8_t reg, int8_t* value, std::vector<uint8_t>* write_buffer);

    /**
     * @brief Makes a request that sends the byte associated with `value` and stores it
     * to the write buffer to write back to the host
     * 
     * @param reg `uint8_t` The register this is associated with
     * @param value `uint8_t*` The pointer to the value to send back to the host
     * @param write_buffer `std::vector<uint8_t>*` The pointer to the write buffer for
     * the specific communication layer of your choosing
     * @return `Request` The associated request struct 
     */
    static Request make_byte(uint8_t reg, uint8_t* value, std::vector<uint8_t>* write_buffer);

}; // struct Request

#endif // REQUEST_STRUCT_HPP