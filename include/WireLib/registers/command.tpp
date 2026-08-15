#include "WireLib/registers/command.hpp"


using namespace std;
using namespace status_utils;


template <typename T>
Command<T>::Command(uint8_t reg, function<StatusCode(T)> runnable)
{
    m_reg = reg;

    // If the type is string or byte vector
    // Then the length can vary, indicate with -1
    if constexpr (std::is_same_v<T, string> || std::is_same_v<T, vector<uint8_t>>)
        m_length = -1;
    else
        m_length = sizeof(T);

    m_runnable = runnable;

} // end of "Command(uint8_t, function<StatusCode(T)>)"


template <typename T>
Command<T>::Command(uint8_t reg, function<StatusCode()> runnable)
    : Command(reg, [runnable](T){return runnable();})
{} // end of "Command(uint8_t, function<StatusCode()>)"


template <typename T>
uint8_t Command<T>::get_register()
{
    return m_reg;

} // end of "get_register()"


template <typename T>
int Command<T>::get_length()
{
    return m_length;

} // end of "get_length()"


template <typename T>
StatusCode Command<T>::run(T data)
{
    return m_runnable(data);

} // end of "run(T)"