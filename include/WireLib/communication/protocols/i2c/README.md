# I2C API

## Usage

In `CubeMX`, please enable NVIC interrupts (both error and event)

This is a simple example that prints the data you send to it

```c++
#include "core.hpp"

#include "gpio.h"
#include "i2c.h"

#include "EmbeddedLib/devices/gpio_device.hpp"

#include "WireLib/communication/protocols/serial_interface.hpp"
#include "WireLib/communication/protocols/i2c/i2c_interface.hpp"

#include "ActionLib/ActionManager.hpp"

#include <vector>


using namespace status_utils;
using namespace std;


void init()
{
    // Configure which I2C to use
    I2C.set_i2c(&hi2c1);

    // Configure the callback
    I2C.configure_on_receive(
        [](const vector<uint8_t>& bytes) -> StatusCode
        {
            ActionManager::add(
                Action::run_once(
                    [bytes](double)
                    {
                        Serial.println("Received Bytes");

                        for(int i = 0; i < bytes.size(); i++)
                        {
                            Serial.println(bytes.at(i));
                        }    
                    }
                )
            );

            return StatusCode::OK;
        }
    );

} // end of "init()"


void update()
{
    ActionManager::update();
    
} // end of "update()"
```
