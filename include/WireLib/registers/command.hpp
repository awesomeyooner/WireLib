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

    public:

        /**
         * @brief Create a new command at the given register and runnable action
         * 
         * Example: Print the a number sent to the MCU
         * 
         * ```
         * Command<double>(101,
         *  [](double data) -> StatusCode
         *  {
         *      Serial.println(data);
         *  
         *      return StatusCode::OK;
         *  }
         * );
         * ```
         * 
         * @param reg `uint8_t` The register to use
         * @param runnable `std::function<status_utils::StatusCode()` A function that returns a StatusCode that takes in
         * a parameter of type T
         * @param use_acknowledgement `bool = false` Set to true to enable the usage of acknowledge packet
         */
        Command(uint8_t reg, std::function<status_utils::StatusCode(T)> runnable, bool use_acknowledgement = false);

        /**
         * @brief Create a new command at the given register and runnable action that doesn't use the data given.
         * This is typically used for debugging.
         * Example: Print the a number sent to the MCU
         * 
         * ```
         * Command<double>(101,
         *  []() -> StatusCode
         *  {
         *      Serial.println("Testing!!!");
         *  
         *      return StatusCode::OK;
         *  }
         * );
         * ```
         * 
         * @param reg `uint8_t` The register to use
         * @param runnable `std::function<status_utils::StatusCode()` A function that returns a StatusCode without
         * any parameters
         * @param use_acknowledgement `bool = false` Set to true to enable the usage of acknowledge packet
         */
        Command(uint8_t reg, std::function<status_utils::StatusCode()> runnable, bool use_acknowledgement = false);

        /**
         * @brief Get the register this Command is associated with
         * 
         * @return `uint8_t` 
         */
        uint8_t get_register();

        /**
         * @brief Get the length of the data type this command accepts in bytes
         * 
         * @return `int` 
         */
        int get_length();

        /**
         * @brief Run the internal runnable with the given argument
         * 
         * @param data `T`
         * @return `status_utils::StatusCode` 
         */
        status_utils::StatusCode run(T data);

        /**
         * @brief Get the flag for whether acknowledgement is enabled or not
         * 
         * @return `true` 
         * @return `false` 
         */
        bool use_acknowledgement();

    private:

        // The register byte
        uint8_t m_reg;

        // The length of the data packet to recieve
        int m_length;

        // Flag to send back the bytes given. Set to true to enable
        bool m_use_acknowledgement = false;

        // The runnable that uses the incoming data. The parameter is the datatype
        // sent from the host
        std::function<status_utils::StatusCode(T)> m_runnable;


}; // class Command


// Include implementation file for template methods
#include "WireLib/registers/command.tpp"


#endif // COMMAND_STRUCT_HPP