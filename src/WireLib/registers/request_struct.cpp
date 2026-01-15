#include "WireLib/registers/request_struct.hpp"


Request Request::make_double(uint8_t reg, double* value, std::vector<uint8_t>* write_buffer)
{
    return Request{
        // Sets the register equat to the given register
        .m_reg = reg,

        // The length is the size of a double (8 bytes)
        .m_length = sizeof(double),

        // Converts `value` into bytes and copies it to the write buffer
        .m_runnable = [value, write_buffer]() -> status_utils::StatusCode
        {
            // Convert the data to send into bytes
            std::vector<uint8_t> bytes = ByteConverter::double_to_bytes(*value);

            // Copy the values of the bytes to send into the write buffer to
            // later be written back to the host
            write_buffer->assign(bytes.begin(), bytes.end());
            
            // Return OK status
            return status_utils::StatusCode::OK;
        }
    };

} // end of "make_double"


Request Request::make_float(uint8_t reg, float* value, std::vector<uint8_t>* write_buffer)
{
    return Request{
        // Sets the register equat to the given register
        .m_reg = reg,

        // The length is the size of a float (4 bytes)
        .m_length = sizeof(float),

        // Converts `value` into bytes and copies it to the write buffer
        .m_runnable = [value, write_buffer]() -> status_utils::StatusCode
        {
            // Convert the data to send into bytes
            std::vector<uint8_t> bytes = ByteConverter::float_to_bytes(*value);

            // Copy the values of the bytes to send into the write buffer to
            // later be written back to the host
            write_buffer->assign(bytes.begin(), bytes.end());
            
            // Return OK status
            return status_utils::StatusCode::OK;
        }
    };

} // end of "make_float"


Request Request::make_byte(uint8_t reg, int8_t* value, std::vector<uint8_t>* write_buffer)
{
    return Request{
        // Sets the register equat to the given register
        .m_reg = reg,

        // The length is the size of a double (8 bytes)
        .m_length = sizeof(float),

        // Converts `value` into bytes and copies it to the write buffer
        .m_runnable = [value, write_buffer]() -> status_utils::StatusCode
        {
            // Since the value is already a byte, just convert it to unsigned
            std::vector<uint8_t> bytes = {(uint8_t)*value};

            // Copy the values of the bytes to send into the write buffer to
            // later be written back to the host
            write_buffer->assign(bytes.begin(), bytes.end());
            
            // Return OK status
            return status_utils::StatusCode::OK;
        }
    };

} // end of "make_byte"


Request Request::make_byte(uint8_t reg, uint8_t* value, std::vector<uint8_t>* write_buffer)
{
    return Request{
        // Sets the register equat to the given register
        .m_reg = reg,

        // The length is the size of a double (8 bytes)
        .m_length = sizeof(float),

        // Converts `value` into bytes and copies it to the write buffer
        .m_runnable = [value, write_buffer]() -> status_utils::StatusCode
        {
            // Since the value is already a byte, just populate the array with it
            std::vector<uint8_t> bytes = {*value};

            // Copy the values of the bytes to send into the write buffer to
            // later be written back to the host
            write_buffer->assign(bytes.begin(), bytes.end());
            
            // Return OK status
            return status_utils::StatusCode::OK;
        }
    };

} // end of "make_byte"