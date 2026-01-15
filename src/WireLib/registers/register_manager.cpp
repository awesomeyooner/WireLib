#include "WireLib/registers/register_manager.hpp"


// Initialize the static members
std::vector<uint8_t> RegisterManager::m_read_buffer;
std::vector<uint8_t> RegisterManager::m_write_buffer;

std::unordered_map<uint8_t, Request> RegisterManager::m_request_map;
std::unordered_map<uint8_t, Command> RegisterManager::m_command_map;


status_utils::StatusCode RegisterManager::update(uint8_t reg, std::vector<uint8_t>* incoming_data)
{
    // If both the maps are empty, return FAILED
    if(m_request_map.empty() && m_command_map.empty())
        return status_utils::StatusCode::FAILED;

    // If the register exists, call its runnable
    if(m_request_map.find(reg) != m_request_map.end()){
        // Serial.println("Request Map Called");
        return m_request_map.at(reg).m_runnable(&m_write_buffer);
    }
    
    // If the register exists, call its runnable
    if(m_command_map.find(reg) != m_command_map.end()){
        // Serial.println("Command Map Called");
        return m_command_map.at(reg).m_runnable(incoming_data);
    }

    return status_utils::StatusCode::FAILED;

} // end of "update"


std::vector<uint8_t>* RegisterManager::get_read_buffer()
{
    return &m_read_buffer;

} // end of "get_read_buffer"


std::vector<uint8_t>* RegisterManager::get_write_buffer()
{
    return &m_write_buffer;

} // end of "get_write_buffer"


void RegisterManager::add_request(Request request)
{
    // register, request
    m_request_map.insert({request.m_reg, request});

} // end of "add_request"


void RegisterManager::add_request(uint8_t reg, int length, std::function<status_utils::StatusCode(std::vector<uint8_t>*)> runnable)
{
    Request request = 
    {
        .m_reg = reg,
        .m_length = length,
        .m_runnable = runnable
    };

    add_request(request);

} // end of "add_request"


void RegisterManager::add_command(Command command)
{
    // register, command
    m_command_map.insert({command.m_reg, command});

} // end of "add_command"


void RegisterManager::add_command(uint8_t reg, int length, std::function<status_utils::StatusCode(std::vector<uint8_t>*)> runnable)
{
    Command command = 
    {
        .m_reg = reg,
        .m_length = length,
        .m_runnable = runnable
    };

    add_command(command);

} // end of "add_command"


std::vector<uint8_t> RegisterManager::extract_data()
{
    // Copy the read data to another buffer
    std::vector<uint8_t> data = m_read_buffer;

    // Remove the first element (the register byte)
    data.erase(data.begin());

    // Return the buffer. It is the read buffer but without the first byte
    // which is / should be the register byte
    return data;

} // end of "extract_data"