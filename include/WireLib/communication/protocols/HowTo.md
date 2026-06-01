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

