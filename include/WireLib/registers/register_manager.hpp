#ifndef REGISTER_MANAGER_HPP
#define REGISTER_MANAGER_HPP

#include <map>
#include <unordered_map>

#include "WireLib/registers/command_struct.hpp"
#include "WireLib/registers/request_struct.hpp"

#include "WireLib/util/byte_converter.hpp"

#include "EmbeddedLib/util/status.hpp"


class RegisterManager
{

    public:

        // Buffer that contains all the bytes read from the host
        static std::vector<uint8_t> m_read_buffer;

        // Buffer that contains all the bytes to write to the host
        static std::vector<uint8_t> m_write_buffer;

        /**
         * @brief Runs the register associated with `reg` if it exists. Returns FAILED if it doesn't.
         * 
         * @param reg `uint8_t` The register to call
         * @param incoming_data `std::vector<uint8_t>*` The incoming data,
         * MUST be populated ONLY with the data to parse, it should not include the register byte
         * @return `status_utils::StatusCode` FAILED if neither maps contain the associated register or
         * if the runnable inside the register fails. OK otherwise 
         */
        static status_utils::StatusCode update(uint8_t reg, std::vector<uint8_t>* incoming_data);

        /**
         * @brief Gets the pointer to the read buffer
         * 
         * @return `std::vector<uint8_t>*` The pointer to the read buffer 
         */
        static std::vector<uint8_t>* get_read_buffer();

        /**
         * @brief Gets the pointer to the write buffer
         * 
         * @return `std::vector<uint8_t>*` The pointer to the write buffer 
         */
        static std::vector<uint8_t>* get_write_buffer();

        /**
         * @brief Add a request to the request map
         * 
         * @param request `Request` The request to add
         */
        static void add_request(Request request);

        /**
         * @brief Add a request to the request map
         * 
         * @param reg `uint8_t` The register
         * @param length `int` The length of the data to send in bytes
         * @param runnable `std::function<status_utils::StatusCode()>` The runnable that will send the data
         */
        static void add_request(uint8_t reg, int length, std::function<status_utils::StatusCode(std::vector<uint8_t>*)> runnable);

        /**
         * @brief Add a command to the command map
         * 
         * @param command `Command` The command to add
         */
        static void add_command(Command command);

        /**
         * @brief Add a command to the command map
         * 
         * @param reg `uint8_t` The register
         * @param length `int` The length of the data to recieve in bytes
         * @param runnable `std::function<status_utils::StatusCode(std::vector<uint8_t>*)>` The runnable that will use 
         * the recieved bytes
         */
        static void add_command(uint8_t reg, int length, std::function<status_utils::StatusCode(std::vector<uint8_t>*)> runnable);

        /**
         * @brief Extracts only the register byte of the read buffer (the first element)
         * 
         * @return `uint8_t` The register 
         */
        static uint8_t extract_register();

        /**
         * @brief Extracts only the data part of the read buffer (removes the first element)
         * 
         * @return `std::vector<uint8_t>` The data buffer 
         */
        static std::vector<uint8_t> extract_data();

    private:

        // Maps to get the request / command associated with a register (uint8_t)
        static std::unordered_map<uint8_t, Request> m_request_map;
        static std::unordered_map<uint8_t, Command> m_command_map;
        
}; // class RegisterManager

#endif // REGISTER_MANAGER_HPP