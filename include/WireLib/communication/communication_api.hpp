#ifndef COMMUNICATION_API_HPP
#define COMMUNICATION_API_HPP

#include <stdio.h>
#include <stdbool.h>
#include <cstdint>


#ifdef __cplusplus
extern "C" {
#endif

    bool Communication_on_receive(uint8_t* buffer, uint32_t length);

#ifdef __cplusplus
}
#endif


#endif // COMMUNICATION_API_HPP