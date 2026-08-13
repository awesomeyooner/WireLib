#ifndef COMMAND_STRUCT_HPP
#define COMMAND_STRUCT_HPP

#include <cstdint>
#include <functional>

#include "EmbeddedLib/status.hpp"

#include "WireLib/util/byte_converter.hpp"

/**
 * @brief Commands are sent TO the microcontroller (what you're writing the firmware on).
 * For example, a command can be a host can send a command to the microcontroller to
 * run the motor at the desired velocity, send via a data packet
 * 
 */
template<typename T>
class Command
{

    // If T is specifically void, then make the runnable
    // accept no arguments (you can have function<StatusCode(void)>)
    using RunnableType = std::conditional_t<
        std::is_void_v<T>,
        std::function<status_utils::StatusCode()>,
        std::function<status_utils::StatusCode(T)>
    >;

    public:

        Command(uint32_t reg, std::function<status_utils::StatusCode(T)> runnable);

        // Command(uint32_t reg, std::function<status_utils::StatusCode()> runnable);

        Command(uint32_t reg, std::function<void(T)> runnable);

        Command(uint32_t reg, std::function<void()> runnable);

        uint8_t get_register();

        int get_length();

        status_utils::StatusCode run(T data);

        status_utils::StatusCode run();

    private:

        // The register byte
        uint8_t m_reg;

        // The length of the data packet to recieve
        int m_length;

        // The runnable that uses the incoming data. The parameter is the datatype
        // sent from the host
        RunnableType m_runnable;

}; // struct Command


// Include implementation file for template methods
#include "WireLib/registers/command.tpp"


#endif // COMMAND_STRUCT_HPP