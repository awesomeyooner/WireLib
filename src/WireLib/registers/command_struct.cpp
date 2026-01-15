#include "WireLib/registers/command_struct.hpp"



Command Command::make_double(uint8_t reg, double* value, std::function<void()> runnable)
{
    return Command{
        // Set the register equal to the register
        .m_reg = reg,

        // The length of the data packet to recieve is the size of a float (4 bytes)
        .m_length = sizeof(double),

        // The runnable will take in the incoming data, convert it to a float,
        // set the pointer's float value equal to that value, and run the runnable
        .m_runnable = [value, runnable](std::vector<uint8_t>* data) -> status_utils::StatusCode
        {
            // If the runnable isn't NULL, then run it
            if(runnable)
                runnable();

            // Convert the incoming bytes into a float
            float f_data = ByteConverter::bytes_to_double(*data);

            // Set the pointer's value equal to the incoming float
            *value = f_data;

            // Return OK
            return status_utils::StatusCode::OK;
        }
    };

} // end of "make_double"


Command Command::make_float(uint8_t reg, float* value, std::function<void()> runnable)
{
    return Command{
        // Set the register equal to the register
        .m_reg = reg,

        // The length of the data packet to recieve is the size of a float (4 bytes)
        .m_length = sizeof(float),

        // The runnable will take in the incoming data, convert it to a float,
        // set the pointer's float value equal to that value, and run the runnable
        .m_runnable = [value, runnable](std::vector<uint8_t>* data) -> status_utils::StatusCode
        {
            // If the runnable isn't NULL, then run it
            if(runnable)
                runnable();

            // Convert the incoming bytes into a float
            float f_data = ByteConverter::bytes_to_float(*data);

            // Set the pointer's value equal to the incoming float
            *value = f_data;

            // Return OK
            return status_utils::StatusCode::OK;
        }
    };

} // end of "make_float"


Command Command::make_runnable(uint8_t reg, std::function<void()> runnable)
{
    return Command{
        // Set the register equal to the register
        .m_reg = reg,

        // 0 since we aren't recieving any data
        .m_length = 0,
        
        // Run the runnable and return OK
        .m_runnable = [runnable](std::vector<uint8_t>* data) -> status_utils::StatusCode{
            runnable();
            return status_utils::StatusCode::OK;
        }
    };

} // end of "make_runnable"