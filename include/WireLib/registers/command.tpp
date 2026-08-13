#include "WireLib/registers/command.hpp"


using namespace std;
using namespace status_utils;


template <typename T>
Command<T>::Command(uint32_t reg, function<StatusCode(T)> runnable)
{
    m_reg = reg;

    // If the type is void
    if constexpr (std::is_void_v<T>)
        m_length = 0;
    else
        m_length = sizeof(T);

    m_runnable = runnable;

} // end of "Command(uint32_t, function<StatusCode(T)>)"


// template <typename T>
// Command<T>::Command(uint32_t reg, function<StatusCode()> runnable)
//     // : Command(reg, [runnable](){runnable(); return StatusCode::OK;})
// {
//     m_reg = reg;
   
//     // If the type is void
//     if constexpr (std::is_void_v<T>)
//         m_length = 0;
//     else
//         m_length = sizeof(T);

//     // Wrap the runnable to return a StatusCode
//     m_runnable = [runnable]()
//     {
//         runnable();

//         return StatusCode::OK;
//     };

// } // end of "Command(uint32_t, function<StatusCode()>)"


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