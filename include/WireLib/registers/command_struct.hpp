#ifndef COMMAND_STRUCT_HPP
#define COMMAND_STRUCT_HPP

#include <cstdint>
#include <functional>

struct Command
{
    uint8_t reg;
    int length;
    std::function<StatusCode(std::vector<uint8_t>*)> runnable;

}

#endif // COMMAND_STRUCT_HPP