#include "WireLib/registers/request.hpp"


using namespace std;
using namespace status_utils;


template <typename T>
Request<T>::Request(uint8_t reg, function<StatusedValue<T>()> runnable)
{
    m_reg = reg;

    // If the type is string or byte vector
    // Then the length can vary, indicate with -1
    if constexpr (std::is_same_v<T, string> || std::is_same_v<T, vector<uint8_t>>)
        m_length = -1;
    else
        m_length = sizeof(T);

    m_runnable = runnable;
    
} // end of "Request(uint8_t, function<StatusedValue<T>>)"


template <typename T>
Request<T>::Request(uint8_t reg, function<T()> runnable)
    : Request(reg, [runnable](){return StatusedValue<T>(runnable(), StatusCode::OK);})
{} // end of "Request(uint8_t, function<StatusedValue<T>>)"


template<typename T>
StatusedValue<vector<uint8_t>> Request<T>::get_bytes()
{
    StatusedValue<T> runnable_status = m_runnable();

    StatusCode status = runnable_status.status;
    T value = runnable_status.value;

    return StatusedValue<vector<uint8_t>>(
        ByteConverter::to_bytes<T>(value),
        status
    );

} // end of "get_bytes()"