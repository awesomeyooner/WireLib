#ifndef WIRE_MANAGER_HPP
#define WIRE_MANAGER_HPP

#include <Wire.h>

#include "WireLib/registers/register_manager.hpp"

class WireManager
{

    public:

        static void initialize(int address);

        static void on_recieve(int num_bytes);

        static void on_request();

    private:


}; // class WireManager

#endif // WIRE_MANAGER_HPP