#ifndef COMMUNICATION_INTERFACE_HPP
#define COMMUNICATION_INTERFACE_HPP

// #include "helpers/system.hpp"

#include <string>
#include <vector>
#include <functional>
#include <cstdint>

#include "EmbeddedLib/status.hpp"


/**
 * @brief Describes the state of the communication (wire) interface
 * 
 */
enum class WireState
{
    READY,  // The stack is ready to recieve a new packet 
    ONGOING,  // The stack is currently recieving packets and is waiting for the rest of the packets to arrive  
    FINISHED // The stack has finished reading all packets and is ready to send the data out to be used
};


enum class ParseType
{
    RAW, // read buffer = raw data, no analyzing or anything
    PACKET //  Parse the raw data as a packet
};


/**
 * @brief Barebones Parent class for all implemented Communication Protocols.
 * Examples are Serial, CAN, I2C, SPI, etc
 * 
 */
class CommunicationInterface
{
    public:

        // Which index is the register byte at
        const int g_REGISTER_BYTE = 0;

        // Which index is the length byte at
        const int g_LENGTH_BYTE = 1;

        // The default max packet size in bytes
        const int g_DEFAULT_MAX_PACKET_SIZE = 256; // bytes


        CommunicationInterface() = default;

        CommunicationInterface(int max_packet_size, ParseType parse_type = ParseType::PACKET);

        virtual ~CommunicationInterface() = default;

        /**
         * @brief Assign the callback function to call when a packet is recieved
         * 
         * @param callback `std::function<status_utils::StatusCode(const std::vector<uint8_t>&)>` Function that takes in
         * a vector of bytes as a parameter and returns a `status_utils::StatusCode` for the status of the execution. OK if good
         */
        virtual void configure_on_receive(std::function<status_utils::StatusCode(const std::vector<uint8_t>&)> callback);

        /**
         * @brief Get the current read state of the device
         * 
         * @return `const WireState` The state of the read progress 
         */
        virtual const WireState get_read_state();

        /**
         * @brief Get the current write state of the device
         * 
         * @return `const WireState` The state of the write progress
         */
        virtual const WireState get_write_state();

        /**
         * @brief Gets the parse type of this stack, parsing as packets or just raw data
         * 
         * @return `const ParseType` The parse type. RAW means buffer = data, PACKET means
         * the raw data is expected to follow the Packet format (in notes) 
         */
        virtual const ParseType get_parse_type();

        /**
         * @brief Sets the parse type of this comm.
         * 
         * @param parse_type `ParseType` The new parse type
         * @return Returns `TRUE` if the old type did change. FALSE if it's already
         * at that type
         */
        virtual bool set_parse_type(ParseType parse_type);

        /**
         * @brief Gets the maximum number of bytes this protocol can handle per packet
         * 
         * @return `const int` The max number in bytes 
         */
        virtual const int get_max_packet_size();

        /**
         * @brief Sets the max number of bytes per package. This returns whether or not this did anything
         * 
         * @param size `int` The number of bytes
         * @return `true` If the previous max was different than the new one 
         * @return `false` If the previous max is already the new one 
         */
        virtual bool set_max_packet_size(int size);

        /**
         * @brief The function to call when a packet is recieved from the backend implementation. This is the RAW receive function,
         * the multi-packet parsing happens in handled in a different method but this method CALLS that method
         * 
         * @param buffer `uint8_t*` Dynamic byte array for the incoming data
         * @param length `uint32_t` The length of the array
         * @return `status_utils::StatusCode` OK if everything is good.  
         */
        virtual status_utils::StatusCode on_receive(uint8_t* buffer, int length);

        /**
         * @brief Pure virtual function, needs to be implemented for the communication protocol. This method is
         * used to send a vector of bytes to the host
         * 
         * @param bytes `const std::vector<uint8_t>&` The byte vector to send 
         * @return `status_utils::StatusCode` OK if everytihng is good 
         */
        virtual status_utils::StatusCode transmit_bytes(const std::vector<uint8_t>& bytes) = 0;

    // Protected since we want all child classes to have access
    protected:

        /**
         * @brief Parses an incoming raw data packet to fill the read buffer with the proper data.
         * This method handles multi-packet parsing
         * 
         * @param bytes `const std::vector<uint8_t>&` The byte buffer
         * @return `status_utils::StatusCode` OK if successful. FAILED otherwise
         */
        virtual status_utils::StatusCode parse_packet(const std::vector<uint8_t>& bytes);

        // The function callback
        std::function<status_utils::StatusCode(const std::vector<uint8_t>&)> m_receive_callback;

        // The byte vector of all read data
        std::vector<uint8_t> m_read_buffer;

        // The byte vector of all the write data
        std::vector<uint8_t> m_write_buffer;

        // The current read state of this device 
        WireState m_read_state = WireState::READY;

        // The current write state of this device
        WireState m_write_state = WireState::READY;

        // How this comm. parses data
        ParseType m_parse_type = ParseType::RAW;

        // The maximum amount of bytes per packet this protocol can handle
        int m_max_packet_size = g_DEFAULT_MAX_PACKET_SIZE;

        // The number of remaining bytes to read
        int m_remaining_read_bytes = 0;

        // The number of remaining bytes to write
        int m_remaining_write_bytes = 0;


}; // class CommunicationInterface


#endif // COMMUNICATION_INTERFACE_HPP