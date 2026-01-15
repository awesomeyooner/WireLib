#ifndef BYTE_CONVERTER_HPP
#define BYTE_CONVERTER_HPP

#include <Wire.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdint>

union FloatsBytesConverter{
    float f_value;
    uint8_t bytes[4];
};

union DoublesBytesConverter{
    double d_value;
    uint8_t bytes[8];
};

// You must declare unions like this and define them in .cpp
extern FloatsBytesConverter f_to_b;
extern DoublesBytesConverter d_to_b;


class ByteConverter
{

    public:

        static float bytes_to_float(std::vector<uint8_t> v_bytes);
        static std::vector<uint8_t> float_to_bytes(float value);

        static double bytes_to_double(std::vector<uint8_t> v_bytes);
        static std::vector<uint8_t> double_to_bytes(double value);

}; // class ByteConverter


#endif // BYTE_CONVERTER_HPP