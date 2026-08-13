#include "WireLib/registers/register_manager.hpp"


template <typename T>
void RegisterManager::add_request(Request<T> request)
{
    m_request_map.insert({request.m_reg, request});

} // end of "add_request(Request<T>)"


template <typename T>
void RegisterManager::add_command(Command<T> command)
{
    m_command_map.insert({command.m_reg, command});

} // end of "add_command(Command<T>)"