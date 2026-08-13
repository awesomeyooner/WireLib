#ifndef WIRE_MANAGER_HPP
#define WIRE_MANAGER_HPP

#include "WireLib/communication/communication_interface.hpp"

#include "WireLib/registers/register_manager.hpp"


class WireManager
{

    public:

        /**
         * @brief Callback function for what to do when the host sends data.
         * Internally, it stores the data in the read buffer and updates the registers. This should be
         * attached to any communication interface's callback
         * @param bytes `const std::vector<uint8_t>&` The read bytes
         */
        static status_utils::StatusCode on_receive(const std::vector<uint8_t>& bytes);

        /**
         * @brief Attach WireManager's on_receive callback to the given interface's callback
         * 
         * @param interface `CommunicationInterface&` The given interface
         */
        static void attach(CommunicationInterface& interface);

    private:

        static inline CommunicationInterface* m_interface = nullptr;


}; // class WireManager

#endif // WIRE_MANAGER_HPP