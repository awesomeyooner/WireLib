#include "WireLib/registers/register_manager.hpp"
#include "WireLib/communication/protocols/serial_interface.hpp"
#include "ActionLib/ActionManager.hpp"

// Initialize the static members
std::vector<uint8_t> RegisterManager::m_read_buffer;
std::vector<uint8_t> RegisterManager::m_write_buffer;

std::unordered_map<uint8_t, RequestVariant> RegisterManager::m_request_map;
std::unordered_map<uint8_t, CommandVariant> RegisterManager::m_command_map;


status_utils::StatusCode RegisterManager::update(uint8_t reg, const std::vector<uint8_t>& incoming_data)
{
    // If both the maps are empty, return FAILED
    if(m_request_map.empty() && m_command_map.empty())
        return status_utils::StatusCode::FAILED;

    // If the register exists, call its runnable
    if(m_request_map.find(reg) != m_request_map.end())
    {
        RequestVariant request_variant = m_request_map.at(reg);
        
        // Placeholder for the return value of `.get_bytes()`
        StatusedValue<vector<uint8_t>> request_call = {{}, StatusCode::FAILED};

        // Double
        if(holds_alternative<Request<double>>(request_variant))
            request_call = std::get<Request<double>>(request_variant).get_bytes();
        // Float
        else if(holds_alternative<Request<float>>(request_variant))
            request_call = std::get<Request<float>>(request_variant).get_bytes();
        // Int
        else if(holds_alternative<Request<int>>(request_variant))
            request_call = std::get<Request<int>>(request_variant).get_bytes();
        // String
        else if(holds_alternative<Request<string>>(request_variant))
            request_call = std::get<Request<string>>(request_variant).get_bytes();
        // Bytes
        else if(holds_alternative<Request<vector<uint8_t>>>(request_variant))
            request_call = std::get<Request<vector<uint8_t>>>(request_variant).get_bytes();

        if(!request_call.is_OK())
            return request_call.status;
        
        set_write_buffer(request_call.value);

        return StatusCode::OK;
    }
    
    // If the register exists, call its runnable
    if(m_command_map.find(reg) != m_command_map.end()){
        
        CommandVariant command_variant = m_command_map.at(reg);
        
        // Double
        if(holds_alternative<Command<double>>(command_variant))
        {
            auto command = std::get<Command<double>>(command_variant);

            // If using acknowledgement then send back the incoming bytes
            if(command.use_acknowledgement())
                set_write_buffer(incoming_data);

            double data = ByteConverter::from_bytes<double>(incoming_data);

            return command.run(data);
        }
        // Float
        else if(holds_alternative<Command<float>>(command_variant))
        {
            auto command = std::get<Command<float>>(command_variant);

            // If using acknowledgement then send back the incoming bytes
            if(command.use_acknowledgement())
                set_write_buffer(incoming_data);

            float data = ByteConverter::from_bytes<float>(incoming_data);

            return command.run(data);
        }
        // Int
        else if(holds_alternative<Command<int>>(command_variant))
        {
            auto command = std::get<Command<int>>(command_variant);

            // If using acknowledgement then send back the incoming bytes
            if(command.use_acknowledgement())
                set_write_buffer(incoming_data);

            int data = ByteConverter::from_bytes<int>(incoming_data);

            return command.run(data);
        }
        // String
        else if(holds_alternative<Command<string>>(command_variant))
        {
            auto command = std::get<Command<string>>(command_variant);

            // If using acknowledgement then send back the incoming bytes
            if(command.use_acknowledgement())
                set_write_buffer(incoming_data);

            string data = ByteConverter::from_bytes<string>(incoming_data);

            return command.run(data);
        }
        // Bytes
        else if(holds_alternative<Command<vector<uint8_t>>>(command_variant))
        {
            auto command = std::get<Command<vector<uint8_t>>>(command_variant);

            // If using acknowledgement then send back the incoming bytes
            if(command.use_acknowledgement())
                set_write_buffer(incoming_data);

            return command.run(incoming_data);
        }
    }

    return status_utils::StatusCode::FAILED;

} // end of "update"


status_utils::StatusCode RegisterManager::update()
{
    // 0 - Register
    // 1 - Length
    // 2... - Data
    if(m_read_buffer.size() < 2)
        return status_utils::StatusCode::FAILED;

    uint8_t reg = extract_register();
    std::vector<uint8_t> data = extract_data();

    return update(reg, data);

} // end of "update"


void RegisterManager::set_read_buffer(const std::vector<uint8_t>& data)
{
    m_read_buffer.assign(data.begin(), data.end());

} // end of "set_read_buffer(const std::vector<uint8_t>&)"


const std::vector<uint8_t>& RegisterManager::get_read_buffer()
{
    return m_read_buffer;

} // end of "get_read_buffer"


void RegisterManager::clear_read_buffer()
{
    m_read_buffer.clear();

} // end of "clear_read_buffer()"


void RegisterManager::set_write_buffer(const std::vector<uint8_t>& data)
{
    m_write_buffer.assign(data.begin(), data.end());

} // end of "set_read_buffer(const std::vector<uint8_t>&)"


std::vector<uint8_t>& RegisterManager::get_write_buffer()
{
    return m_write_buffer;

} // end of "get_write_buffer"


void RegisterManager::clear_write_buffer()
{
    m_write_buffer.clear();

} // end of "clear_write_buffer()"


uint8_t RegisterManager::extract_register()
{
    return m_read_buffer.at(0);

} // end of "extract_register"


std::vector<uint8_t> RegisterManager::extract_data()
{
    // Copy the read data to another buffer but skip the first two bytes 
    // since it's the register and length of packet
    std::vector<uint8_t> data(m_read_buffer.begin() + 2, m_read_buffer.end());

    // Return the buffer. It is the read buffer but without the first two bytes
    // which is / should be the register byte and length byte
    return data;

} // end of "extract_data"