#include "WireLib/registers/request.hpp"


using namespace std;
using namespace status_utils;


template <typename T>
Request<T>::Request(uint32_t reg, function<StatusedValue<T>> runnable)
{
    m_reg = reg;
    m_length = sizeof(T);
    m_runnable = runnable;
    
} // end of "Request(uint32_t, function<StatusedValue<T>>)"


template <typename T>
Request<T>::Request(uint32_t reg, function<T> runnable)
{
    m_reg = reg;
    m_length = sizeof(T);

    // Wrap the runnable in StatusedValue
    m_runnable = [runnable]()
        {
            return StatusedValue<T>(runnable(), StatusCode::OK);
        };
    
} // end of "Request(uint32_t, function<StatusedValue<T>>)"


template<typename T>
StatusedValue<vector<uint8_t>> Request<T>::get_bytes()
{
    StatusedValue<T> runnable_status = m_runnable();

    StatusCode status = runnable_status.status;
    T value = runnable_status.value;


    // Explicilty check the data type to return
    if constexpr (std::is_same_v<T, double>)
        return StatusedValue<vector<uint8_t>>(ByteConverter::double_to_bytes(value), status);
    else if constexpr (std::is_same_v<T, float>)
        return StatusedValue<vector<uint8_t>>(ByteConverter::float_to_bytes(value), status);
    else if constexpr (std::is_same_v<T, int>)
        return StatusedValue<vector<uint8_t>>(ByteConverter::int_to_bytes(value), status);
    else
        return StatusedValue<vector<uint8_t>>({}, StatusCode::FAILED);

} // end of "get_bytes()"