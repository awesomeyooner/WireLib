# WireLib
A PlatformIO based library that handles different types of wire communication, like I2C or CAN, and allows for creating registers.

## Usage

### Adding to Project

To include this library, please `git clone` or `git submodule add` this repo into the `\lib` folder of your project

You must also add `EmbeddedLib` and `ActionLib`!

Then add this to link the library

```cmake
# Add User Libraries
add_subdirectory(lib/EmbeddedLib)
add_subdirectory(lib/WireLib)
add_subdirectory(lib/ActionLib)

add_library(shared_library INTERFACE)

target_include_directories(shared_library INTERFACE
    ${CMAKE_SOURCE_DIR}/Core/Inc
    ${CMAKE_SOURCE_DIR}/USB_DEVICE/App
    ${CMAKE_SOURCE_DIR}/USB_DEVICE/Target
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    ${CMAKE_SOURCE_DIR}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
)

target_compile_definitions(shared_library INTERFACE
    STM32CUBE
    STM32F446xx
)

target_link_libraries(EmbeddedLib PRIVATE shared_library)
target_link_libraries(WireLib PRIVATE shared_library)
target_link_libraries(ActionLib PRIVATE shared_library)

...

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
    EmbeddedLib
    WireLib
    ActionLib
)
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