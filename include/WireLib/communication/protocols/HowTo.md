# Serial API

## Adding to Project

Add to header file

```c++
// cube/USB_DEVICE/App/usbd_cdc_if.h

// Line 34
#include "WireLib/communication/protocols/serial_api.hpp"
```

Then add the actual call

```c++
// cube/USB_DEVICE/App/usbd_cdc_if.c

// Line 266
Serial_on_receive(Buf, Len);
// Add it at the end, right before the return statement
```

## Usage

This is a simple example that prints out the data you send!

```c++
init()
{
    // ...
    // It's RAW by default
    Serial.set_parse_type(ParseType::RAW); // or ParseType::PACKET

    Serial.configure_on_receive(
        [](const vector<uint8_t>& bytes) -> StatusCode
        {
            Action print_data = Action::run_once(
                [bytes]() -> void
                {
                    string text = ByteConverter::bytes_to_string(bytes);

                    Serial.println(text);
                }
            );

            ActionManager::add(print_data);

            return StatusCode::OK;
        }
    );
}

update()
{
    ActionManager::update();
}
```
