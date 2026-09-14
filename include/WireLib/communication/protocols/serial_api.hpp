#ifndef SERIAL_API_HPP
#define SERIAL_API_HPP

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief C++ Entrypoint for the USBFS receive callback
     * 
     * Include this header in the USB CDC HAL code
     * 
     * In File: `cube/USB_DEVICE/App/usbd_cdc_if.h`
     * 
     * Add: `#include "WireLib/communication/protocols/serial_api.hpp"` at line 34
     *
     * Add the actual API Call
     * 
     * In File: `cube/USB_DEVICE/App/usbd_cdc_if.c`
     * 
     * Under: `static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)`
     * 
     * Add: `Serial_on_receive(Buf, *Len);`
     */
    bool Serial_on_receive(uint8_t* buffer, uint32_t length);

    /**
     * @brief C++ Entrypoint for the USBFS DTR state change
     * 
     * This function allows for the connection state to be monitored through
     * `Serial.is_connected()`
     * 
     * Include this header in the USB CDC HAL code
     * 
     * In File: `cube/USB_DEVICE/App/usbd_cdc_if.h`
     * 
     * Add: `#include "WireLib/communication/protocols/serial_api.hpp"` at line 34
     * 
     * Add the actual API Call
     * 
     * In File: `cube/USB_DEVICE/App/usbd_cdc_if.c`
     * 
     * Under: `static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length)`
     * 
     * Add: `Serial_update_connection_status(pbuf)` at Line 231
     * 
     * Add it inside CDC_SET_CONTROL_LINE_STATE
     * 
     * @param pbuf `uint8_t*`
     */
    void Serial_update_connection_status(uint8_t* pbuf);

#ifdef __cplusplus
}
#endif


#endif // SERIAL_API_HPP