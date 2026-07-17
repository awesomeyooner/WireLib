#ifndef COMMUNICATION_API_HPP
#define COMMUNICATION_API_HPP

#include <stdio.h>
#include <stdbool.h>
#include <cstdint>


#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief The Native C callback function that is placed in the HAL code. Used to call user-defined C++ code.
     * 
     * @param buffer `uint8_t*` Byte Buffer
     * @param length `uint32_t` The length of the buffer
     * @return `true` If successful parse
     * @return `false` If failed to parse
     */
    bool Communication_on_receive(uint8_t* buffer, uint32_t length);

#ifdef __cplusplus
}
#endif


#endif // COMMUNICATION_API_HPP