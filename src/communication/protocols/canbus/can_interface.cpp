// https://controllerstech.com/can-protocol-in-stm32/

#include "WireLib/communication/protocols/canbus/can_interface.hpp"


using namespace status_utils;
using namespace std;


CANInterface::CANInterface()
{
    m_TxHeader.IDE = CAN_ID_STD;
    m_TxHeader.RTR = CAN_RTR_DATA;

} // end of "CANInterface()"


void CANInterface::set_ID(uint32_t id)
{
    m_TxHeader.StdId = id;
    
    config_filter();

    enable_callback();

} // end of "set_ID(uint32_t)"


uint32_t CANInterface::get_ID()
{
    return m_TxHeader.StdId;

} // end of "get_ID()"


StatusCode CANInterface::config_filter()
{
    CAN_FilterTypeDef filter;

    filter.FilterActivation = CAN_FILTER_ENABLE;

    filter.FilterBank = 0;
    filter.SlaveStartFilterBank = 14;

    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;

    filter.FilterIdHigh = get_ID() << 5;
    filter.FilterIdLow = 0;

    filter.FilterMaskIdHigh = 0x7FF << 5;  // Mask All ID Bits, so only 1 ID is allowed
    filter.FilterMaskIdLow = 0x0000; // Ignore all 0 bits

    filter.FilterMode = CAN_FILTERMODE_IDMASK;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;

    return HAL_CAN_ConfigFilter(m_hcan, &filter) == HAL_OK ? StatusCode::OK : StatusCode::FAILED;

} // end of "config_filter()"


StatusCode CANInterface::enable_callback()
{
    return HAL_CAN_ActivateNotification(m_hcan, CAN_IT_RX_FIFO0_MSG_PENDING) == HAL_OK ? StatusCode::OK : StatusCode::FAILED;
     
} // end of "enable_callbacK()"


StatusCode CANInterface::transmit_bytes(const vector<uint8_t>& bytes)
{
    copy_to_write_buffer(bytes);

    // Set the length of the data packet in bytes
    m_TxHeader.DLC = bytes.size();

    HAL_StatusTypeDef status = HAL_CAN_AddTxMessage(m_hcan, &m_TxHeader, m_write_buffer.data(), &m_TxMailbox);

    switch(status)
    {
        case HAL_OK:
            return StatusCode::OK;
        case HAL_BUSY:
            return StatusCode::FAILED;
        default:
            return StatusCode::ERROR;
    }

} // end of "transmit_bytes(const vector<uint8_t>& bytes)"


CANInterface CAN = CANInterface();


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];

    if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
        return;

    if(RxHeader.StdId == CAN.get_ID())
        CAN.on_receive(RxData, sizeof(RxData));

} // end of "HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef*)"

