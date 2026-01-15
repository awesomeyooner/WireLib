#ifndef COMMAND_STRUCT_HPP
#define COMMAND_STRUCT_HPP

#include <cstdint>
#include <functional>

#include "EmbeddedLib/util/status.hpp"

#include "WireLib/util/byte_converter.hpp"

/**
 * @brief Commands are sent TO the microcontroller (what you're writing the firmware on).
 * For example, a command can be a host can send a command to the microcontroller to
 * run the motor at the desired velocity, send via a data packet
 * 
 */
struct Command
{
    // The register byte
    uint8_t m_reg;

    // The length of the data packet to recieve
    int m_length;

    // What runs after the register is called
    std::function<status_utils::StatusCode(std::vector<uint8_t>*)> m_runnable;


    /**
     * @brief Makes a command that takes in incoming bytes as a `double` and sets it to `value`.
     * Also runs an optional runnable once the register is called
     * 
     * @param reg `uint8_t` The register this is associated with
     * @param value `double*` The pointer to the value to set
     * @param runnable `std::function<void()>` Runnable to run when the command is recieved
     * @return `Command` The associated command struct 
     */
    static Command make_double(uint8_t reg, double* value, std::function<void()> runnable = NULL);

    /**
     * @brief Makes a command that takes in incoming bytes as a `float` and sets it to `value`.
     * Also runs an optional runnable once the register is called
     * 
     * @param reg `uint8_t` The register this is associated with
     * @param value `float*` The pointer to the value to set
     * @param runnable `std::function<void()>` Runnable to run when the command is recieved
     * @return `Command` The associated command struct 
     */
    static Command make_float(uint8_t reg, float* value, std::function<void()> runnable = NULL);

    /**
     * @brief Makes a command that runs the runnable when the register is called.
     * You would typically use this when the register acts as a "button"
     * 
     * @param reg `uint8_t` The register this is associated with
     * @param runnable `std::function<void()>` Runnable to run whent he command is recieved
     * @return `Command` The associated command struct 
     */
    static Command make_runnable(uint8_t reg, std::function<void()> runnable);

}; // struct Command

#endif // COMMAND_STRUCT_HPP