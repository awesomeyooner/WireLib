#ifdef STM32CUBE

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
     * Add: `#include "EmbeddedLib/stm32/communication/usbfs_api.hpp"` at line 34
     *
     * Add the actual API Call
     * 
     * In File: `cube/USB_DEVICE/App/usbd_cdc_if.c`
     * 
     * Add: `USBFS_on_receive(uint8_t* buffer, uint32_t length)`
     */
    bool Serial_on_receive(uint8_t* buffer, uint32_t length);

#ifdef __cplusplus
}
#endif


#endif // SERIAL_API_HPP

#endif // STM32CUBE