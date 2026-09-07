#ifndef CAN_INTERFACE_HPP
#define CAN_INTERFACE_HPP


#include "can.h"
#include "stm32f4xx_hal_can.h"

#include "EmbeddedLib/system.hpp"
#include "EmbeddedLib/util/string_formatter.hpp"

#include "WireLib/communication/communication_interface.hpp"

#include <string>
#include <vector>
#include <functional>


class CANInterface : public CommunicationInterface
{

    public:

        CANInterface();

        void set_ID(uint32_t id);

        uint32_t get_ID();

        status_utils::StatusCode config_filter();

        status_utils::StatusCode enable_callback();

        status_utils::StatusCode transmit_bytes(const std::vector<uint8_t>& bytes) override;

    private:

        CAN_HandleTypeDef* m_hcan;

        CAN_TxHeaderTypeDef m_TxHeader;

        uint32_t m_TxMailbox;

}; // class CANInterface : public CommunicationInterface


// Global Object like Arduino
extern CANInterface CAN;


#endif // CAN_INTERFACE_HPP