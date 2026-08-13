#ifndef REGISTER_MANAGER_HPP
#define REGISTER_MANAGER_HPP

#include <map>
#include <unordered_map>
#include <variant>

#include "WireLib/registers/command.hpp"
#include "WireLib/registers/request.hpp"

#include "WireLib/util/byte_converter.hpp"

#include "EmbeddedLib/status.hpp"


using CommandVariant = std::variant<Command<int>, Command<float>, Command<double>>;
using RequestVariant = std::variant<Request<int>, Request<float>, Request<double>>;


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
        static status_utils::StatusCode update(uint8_t reg, const std::vector<uint8_t>& incoming_data);

        /**
         * @brief Runs the register associated with the one defined in the read buffer and uses the data
         * inside of it as well. Returns FAILED if something goes wrong.
         * 
         * @return `status_utils::StatusCode` FAILED if neither maps contain the associated register or
         * if the runnable inside the register fails. OK otherwise 
         */
        static status_utils::StatusCode update();
        
        /**
         * @brief Assign the values of the read buffer
         * 
         * @param data `const std::vector<uint8_t>&` The new values 
         */
        static void set_read_buffer(const std::vector<uint8_t>& data);

        /**
         * @brief Gets the pointer to the read buffer
         * 
         * @return `std::vector<uint8_t>&` 
         */
        static const std::vector<uint8_t>& get_read_buffer();

        /**
         * @brief Clears the read buffer
         * 
         */
        static void clear_read_buffer();

        /**
         * @brief Assign the values of the write buffer
         * 
         * @param data `const std::vector<uint8_t>&` The new values 
         */
        static void set_write_buffer(const std::vector<uint8_t>& data);

        /**
         * @brief Gets the pointer to the write buffer
         * 
         * @return `std::vector<uint8_t>&` 
         */
        static std::vector<uint8_t>& get_write_buffer();

        /**
         * @brief Clears the write buffer
         * 
         */
        static void clear_write_buffer();

        /**
         * @brief Add a request to the request map
         * 
         * @param request `Request` The request to add
         */
        template <typename T>
        static void add_request(Request<T> request);

        /**
         * @brief Add a command to the command map
         * 
         * @param command `Command` The command to add
         */
        template <typename T>
        static void add_command(Command<T> command);

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
        static std::unordered_map<uint8_t, RequestVariant> m_request_map;
        static std::unordered_map<uint8_t, CommandVariant> m_command_map;
        
}; // class RegisterManager


// Include implementation file for template methods
#include "WireLib/registers/register_manager.tpp"


#endif // REGISTER_MANAGER_HPP