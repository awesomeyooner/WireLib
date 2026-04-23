#ifndef SERIAL_API_HPP
#define SERIAL_API_HPP

#include <stdio.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

    bool Serial_on_receive(uint8_t* buffer, uint32_t length);

#ifdef __cplusplus
}
#endif


#endif // COMMUNICATION_API_HPP