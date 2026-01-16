#ifndef WIRE_MANAGER_HPP
#define WIRE_MANAGER_HPP

#include <Wire.h>

#include "WireLib/registers/register_manager.hpp"

class WireManager
{

    public:

        /**
         * @brief Initializes the I2C bus and links the 
         * on_recieve and on_request functions to the callbacks
         * 
         * @param address `int` The address this device is associated with
         */
        static void initialize(int address);

        /**
         * @brief Callback function for what to do when the host sends data.
         * Internally, it stores the data in the read buffer and updates the registers
         * @param num_bytes `int` The number of bytes to read
         */
        static void on_recieve(int num_bytes);

        /**
         * @brief Callback function for what to do when the host requests data.
         * Internally, it writes whatevers in the write buffer
         * 
         */
        static void on_request();

    private:


}; // class WireManager

#endif // WIRE_MANAGER_HPP