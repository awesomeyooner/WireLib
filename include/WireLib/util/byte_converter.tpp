#include "WireLib/util/byte_converter.hpp"


using namespace std;


template <typename T>
T ByteConverter::from_bytes(const vector<uint8_t>& v_bytes)
{
    if constexpr (std::is_same_v<T, int>)
        return bytes_to_int(v_bytes);
    else if constexpr (std::is_same_v<T, float>)
        return bytes_to_float(v_bytes);
    else if constexpr (std::is_same_v<T, double>)
        return bytes_to_double(v_bytes);
    else
        return T{};
        
} // end of "from_bytes(const vector<uint8_t>&)"


template <typename T>
vector<uint8_t> ByteConverter::to_bytes(T value)
{
    if constexpr (std::is_same_v<T, int>)
        return int_to_bytes(value);
    else if constexpr (std::is_same_v<T, float>)
        return float_to_bytes(value);
    else if constexpr (std::is_same_v<T, double>)
        return double_to_bytes(value);
    else
        return {};

} // end of "to_bytes(T)"