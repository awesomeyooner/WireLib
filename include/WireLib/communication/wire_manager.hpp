#ifndef WIRE_MANAGER_HPP
#define WIRE_MANAGER_HPP

#include "WireLib/communication/communication_interface.hpp"

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
         * Internally, it stores the data in the read buffer and updates the registers. This should be
         * attached to any communication interface's callback
         * @param bytes `const std::vector<uint8_t>&` The read bytes
         */
        static status_utils::StatusCode on_receive(const std::vector<uint8_t>& bytes);

        /**
         * @brief Callback function for what to do when the host requests data.
         * Internally, it writes whatevers in the write buffer
         * 
         */
        static status_utils::StatusCode on_request();

        /**
         * @brief Attach WireManager's on_receive callback to the given interface's callback
         * 
         * @param interface `CommunicationInterface&` The given interface
         */
        static void attach(CommunicationInterface& interface);

    private:

        // static CommunicationInterface m_interface;


}; // class WireManager

#endif // WIRE_MANAGER_HPP