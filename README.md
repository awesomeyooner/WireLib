# WireLib
A PlatformIO based library that handles different types of wire communication, like I2C or CAN, and allows for creating registers.

## Adding to Project

To include this library, please `git clone` or `git submodule add` this repo into the `\lib` folder of your project

You must also add `EmbeddedLib` and `ActionLib`!

Then add this to link the library

```cmake
# Add WireLib
add_subdirectory(lib/WireLib)
target_link_libraries(WireLib PRIVATE shared_library)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    shared_library # Main Library Interface

    WireLib
    # Other Libs
)
```

## Usage

### Protocols

Here's a list of implemented protocols

Each one links to their respective setup guides

- [`Serial`](include/WireLib/communication/protocols/README.md)
- `CAN` (Planned)
- `I2C` (Planned)

### Registers

There are two types of Registers:

1. `Command` - These receive data from the host
    - Ex: Sending a position command from a PC to controller (MCU)
2. `Request` - These receive a request packet from the host to then send data back to the host
    - Ex: Requesting position data from the MCU to send to the PC

Registers are handled via `RegisterManager`, but the communication side is handled via `WireManager`. 

Here's a very basic example:

> **NOTE** Be sure to add the `Serial` callback in HAL!

```c++
void init()
{
    Serial.set_parse_type(ParseType::PACKET);

    WireManager::attach(Serial);

    RegisterManager::add_command(
        Command<double>(
            100, // Register Byte
            [](double data) -> StatusCode
            {
                // Do something with `data`
                
                return StatusCode::OK;
            }
        )
    );

    RegisterManager::add_request(
        Request<double>(
            101, // Register Byte
            []() -> double
            {
                return System::get_seconds();
            }
        )
    );

} // end of "init()"
```

## Implementation

For all communication types, we define a **universal packet**

Since `CAN` and `I2C` usually have max packet sizes of 8 Bytes, this implementation will need to take care of multi-packet parsing 

A packet consists of

| Byte # | Data Type | Name | What it does
| --- | --- | --- | --- |
| 1 | `uint8_t` | Register | Tells controller what to do with the data
| 2 | `uint8_t` | Length | Tells the controller how long the total packet is (min is 2 bytes, one for Register, other for Length)
| 3...| Any | Data | The actual data of the packet. This can be interpreted in different ways, but typically it's either 6 (4 bytes of data to be a `float` or standard `int`) or 10 (2 for Register and Length and 8 for `double`) 