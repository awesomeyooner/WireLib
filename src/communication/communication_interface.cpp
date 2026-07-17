#include "WireLib/communication/communication_interface.hpp"


using namespace status_utils;


CommunicationInterface::CommunicationInterface(int max_packet_size, ParseType parse_type)
{
    m_max_packet_size = max_packet_size;
    m_parse_type = parse_type;

} // end of "CommunicationInterface"


void CommunicationInterface::configure_on_receive(std::function<StatusCode(const std::vector<uint8_t>&)> callback)
{
    m_receive_callback = callback;

} // end of "configure_on_receive(std::function<bool(const std::vector<uint8_t>&)>)"


const WireState CommunicationInterface::get_read_state()
{
    return m_read_state;

} // end of "get_read_state()"


const WireState CommunicationInterface::get_write_state()
{
    return m_write_state;

} // end of "get_write_state"


const ParseType CommunicationInterface::get_parse_type()
{
    return m_parse_type;

} // end of "get_parse_type"


bool CommunicationInterface::set_parse_type(ParseType parse_type)
{
    bool did_change = m_parse_type != parse_type;

    m_parse_type = parse_type;

    return did_change;

} // end of "set_parse_type(ParseType)"


const int CommunicationInterface::get_max_packet_size()
{
    return m_max_packet_size;

} // end of "get_max_packet_size()"


bool CommunicationInterface::set_max_packet_size(int size)
{
    bool did_change = m_max_packet_size != size;

    m_max_packet_size = size;

    return did_change;

} // end of "set_max_packet_size(int)"


StatusCode CommunicationInterface::parse_packet(const std::vector<uint8_t>& bytes)
{
    // If RAW
    // Then just assign all of the read buffer to the incoming bytes
    if(m_parse_type == ParseType::RAW)
    {
        // Populate the read buffer
        m_read_buffer.assign(bytes.begin(), bytes.end());
        m_remaining_read_bytes = 0;

        // We are finished, so we can call the callback
        m_read_state = WireState::FINISHED;

        return StatusCode::OK;
    }

    // Since there's only two ParseTypes
    // This point of the code means m_parse_type = ParseType::PACKET

    // If the packet is empty
    // Then return FAILED
    if(bytes.size() == 0)
        return StatusCode::FAILED;

    int current_packet_length = bytes.size();

    switch(m_read_state)
    {
        // When stack is ready to receive a new packet
        case WireState::READY:
        case WireState::FINISHED:
            {
                if(bytes.size() - 1 < g_LENGTH_BYTE)
                    return StatusCode::FAILED;
                    
                int total_packet_length = bytes.at(g_LENGTH_BYTE);

                // Fill the buffer since this is our FIRST packet
                // so any previous data is not needed
                m_read_buffer.assign(bytes.begin(), bytes.end());

                
                // The bytes we have left to read after this is
                // The TOTAL PACKET LENGTH - Current Packet Length
                /**
                 * Let's say the total packet length is 10 bytes and let's say
                 * this current packet is 8 bytes. This loop will
                 * read 8 bytes, so all we gotta do is read 2 bytes after.
                 * This also works if this is NOT multi-packet
                 */
                m_remaining_read_bytes = total_packet_length - current_packet_length;
            }
            break; // WireState::READY
        
        // If we received a multi-packet... 
        case WireState::ONGOING:
            {
                // Append incoming data to read buffer
                m_read_buffer.insert(
                    m_read_buffer.end(), // Append to the end of the read buffer
                    bytes.begin(), // Append the ENTIRE buffer (begin to end)
                    bytes.end()
                );

                // Reduce the remaining bytes to read by how many bytes we JUST read
                // This will be 0 if we read the remaining bytes
                m_remaining_read_bytes -= current_packet_length;
            }
            break; // WireState::ONGOING

        default:
            return StatusCode::FAILED;
    }

    // If we read all the bytes needed
    // Then set the state to FINISHED
    if(m_remaining_read_bytes == 0)
        m_read_state = WireState::FINISHED;
    // If there's still bytes left to read
    // Then flag the state as ONGOING
    else if(m_remaining_read_bytes > 0)
        m_read_state = WireState::ONGOING;
    // If, for whatever reason, the remaining is NEGATIVE
    // Then reset the system back to READY and return FAILED
    else if(m_remaining_read_bytes < 0)
    {
        m_read_state = WireState::READY;
        return StatusCode::FAILED;
    }

    // If code gets to here, that means everything should be A OK
    return StatusCode::OK;

} // end of "parse_packet(const std::vector<uint8_t>&)"


StatusCode CommunicationInterface::on_receive(uint8_t* buffer, int length)
{
    // Convert dyn. arr. to vector
    std::vector<uint8_t> bytes;
    bytes.assign(buffer, buffer + length);   

    // Parse bytes to handle multi-packet requests
    StatusCode packet_status = parse_packet(bytes);

    // If the callback is set
    // Then call it

    // If all the data has finished parsing and the receive callback exists
    // Then call it
    if(m_read_state == WireState::FINISHED && m_receive_callback)
    {
        m_read_state = WireState::READY;
        return m_receive_callback(m_read_buffer);
    }

    return packet_status;

} // end of "on_receive(uint8_t*, int)"