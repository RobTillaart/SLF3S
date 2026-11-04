
[![Arduino CI](https://github.com/RobTillaart/SLF3S/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SLF3S/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SLF3S/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SLF3S/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SLF3S/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SLF3S.svg)](https://github.com/RobTillaart/SLF3S/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SLF3S/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SLF3S.svg?maxAge=3600)](https://github.com/RobTillaart/SLF3S/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SLF3S.svg)](https://registry.platformio.org/libraries/robtillaart/SLF3S)


# SLF3S

Arduino library for the Sensirion I2C Low Flow sensor SLF3S,


## Description

**Experimental**

This library is to use the professional Sensirion I2C Low Flow sensor
**SLF3S_0600F** and **SLF3S_1300F**.
As the library is not tested with hardware yet, it is **Work In Progress**, so use with care.

Be sure to read the datasheet to understand the sensor.

The library will also work for the **SLF3C_1300F** and others however 
the library does not handle SLF3C's thermal conductivity command. 
If time permits a separate SLF3C class will be written.

Details see page3, table 1:

|  device     |  voltage  |  full scale  |  acc. H20  |  acc. IPA  |
|:------------|:---------:|-------------:|:----------:|:----------:|
| SLF3S-0600F | **3.3 V** |    2 ml/min  |     ±5%    |    ±10%    |
| SLF3S-1300F | **3.3 V** |   40 ml/min  |     ±5%    |    ±10%    |
| SLF3C-1300F | **3.3 V** |   40 ml/min  |     ±5%    |    ±10%    |
| SLF3S-0600D | **3.3 V** |    2 ml/min  |     ±5%    |    ±10%    |
| SLF3S-1300D | **3.3 V** |   40 ml/min  |     ±5%    |    ±10%    |
| SLF3S-4000B | **3.3 V** |  600 ml/min  |     ±5%    |    ±10%    |


To elaborate


- 25 ms power up time
- 60 ms stabilize output
- Recommended sensor read out frequency 10 - 2000 Hz (page 5 + section 3.1).

Note the SLF3S sensors are high precision instruments and therefore relative
expensive, few hundred EUR / USD. So use them with care (and 3.3V only).

Feedback as always is welcome.


### Datasheets

Datasheets used, for latest see Sensirion website:

- SLF3S-0600F - Version 1.2 – D1 – October 2023
- SLF3S-1300F - Version 1.1 – D1 – October 2022
- SLF3C-1300F - Version 1.1 – D1 – October 2022
- SLF3S-xxxxD - Version 1.0 – June 2026
- SLF3S-4000B - Version 1.2 – D1 – November 2022


### Special characters

µ == micro = ALT-0181 (Windows)


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment,
and any other applications that may cause personal injury due to the product's failure._


### Compatibles

The library is primary for the SLF3S-0600F and SLF3S-1300F but is expected to work
with the following devices too.

|  device     |  verified  |
|:------------|:----------:|
| SLF3C-1300F |     N      |
| SLF3S-0600D |     N      |
| SLF3S-1300D |     N      |
| SLF3S-4000B |     N      |


### Hardware

from left to right, see datasheet page 6

|  pin  |   name   |  description    |  Notes  |
|:-----:|:--------:|:----------------|:-------:|
|   1   |  IRQn    |  interrupt      |  See datasheet SLF3C-1300F page 9
|   2   |  SDA     |  I2C data       |  3.3 Volt
|   3   |  VDD     |  Power +3.3 V   |
|   4   |  GND     |  Ground         |
|   5   |  SCL     |  I2C clock      |  3.3 Volt
|   6   |   -      |  not connected  | connect to GND

The IRQn pin can be used to change the I2C address of the sensor.
The library does not support this, however a document describing the
procedure is available in the documents folder.
If no interrupts are used leave the IRQ line not connected (as it is an output).


### Related

Official Sensirion Library for SLF3X

- https://github.com/Sensirion/arduino-i2c-slf3x

Product page - data sheets and more.

- https://sensirion.com/products/catalog/SLF3S-0600F
- https://sensirion.com/products/catalog/SLF3S-1300F
- https://sensirion.com/products/catalog/SLF3C-1300F

Flow
- https://github.com/RobTillaart/PERIPUMP - peristaltic pump control
- https://github.com/RobTillaart/SLF3S - low flow measurement.
- https://github.com/RobTillaart/TSW10 - analog turbidity sensor

Other
- https://github.com/RobTillaart/PrintHelpers - hex(), print64() and more.
- https://github.com/RobTillaart/Temperature - converters


### Tested

TODO: Test with 3.3V MCU e.g. ESP32.


## I2C

### I2C Address

The device default has a fixed I2C address of 0x08 (8) so only one sensor per I2C bus
can be used. It is however possible to change the I2C address by using the IRQ pin.
See the documentation folder for details. This is not supported in the library.

The I2C communication supports **3.3V only** so any 3.3V MCU should be able to connect.
Do not use 5V MCU to connect without a voltage converter.
Do not forget appropriate **pull up** resistors on the I2C SDA and SCL lines.

If one needs more sensors there are some options.
- One could use an I2C multiplexer (see below)
- One could use an MCU with multiple I2C buses.
- One could use a (Two-Wire compatible) SW I2C (outside scope of this library).


### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up
to eight channels (think of it as I2C subnets) which can use the complete
address range of the device.

Drawback of using a multiplexer is that it takes more administration in
your code e.g. which device is on which channel.
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


### I2C Performance

The SLF3S support up to 1000 kHz I2C, in practise 400 kHz should work well.

Only test **readFlow()** and **readFlowTemp()** as that is the main function.

Timing in microseconds. The numbers below are indicative as these are from
a dry run with no sensor (UNO R3)

|  Clock     |  readFlow   |  readFlowTemp  |  Notes  |
|:----------:|:-----------:|:---------------|:--------|
|   100 kHz  |     152     |       168      |
|   200 kHz  |     96      |       108      |
|   300 kHz  |     80      |       88       |
|   400 kHz  |     72      |       84       |
|   600 kHz  |     64      |       80       |
|   800 kHz  |      -      |        -       |  failed in dry run
|  1000 kHz  |      -      |        -       |  failed in dry run

Note the gain above 400 kHz is not much.


## Interface

Note: The API can be subject to change.

```cpp
#include "SLF3S.h"
```

### Constructor

- **SLF3S(uint8_t address = 0x08, TwoWire \*wire = &Wire)** set address and select I2C bus. See I2C section below about address.
- **bool begin(uint16_t type = 600)** checks if device address is visible on the I2C bus.
Sets the type to 600, 1300 or 4000. All other values are mapped upon 600.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the device address, default 0x08 (8).

|  device     |  type  |
|:------------|:------:|
| SLF3S-0600F |   600  |
| SLF3S-1300F |  1300  |
| SLF3C-1300F |  1300  |
| SLF3S-0600D |   600  |
| SLF3S-1300D |  1300  |
| SLF3S-4000B |  4000  |


### Request

- **int requestH2O()** start continuous measurement for H2O.
Returns SLF3S_OK (0) or low level status.
- **int requestIPA()** start continuous measurement for IsoPropyl Alcohol (IPA).
Returns SLF3S_OK (0) or low level status.
- **bool isReady()** returns SLF3S_OK (0) when measurements are stable.
Returns SLF3S_NOT_READY if not stable, or SLF3S_NO_REQUEST when measurements
are not requested.
- **int stopMeasurement()** stops the measurement.
Returns SLF3S_OK (0) or low level status.


### Read

- **int readFlow()** reads only the flow (3 bytes) from the device.
This is the most used data
- **int readFlowTemp()** reads flow and temperature (6 bytes) from the device.
- **int readFlowTempSignal()** reads flow, temperature and signal flags (9 bytes)
from the device.
- **float getFlow()** converts the last read flow to uL/min. The conversion factor
depends on the device type 600, 1300 or 4000.
The returned value can be negative (reverse flow direction).
- **float getTemperature()** converts the last read temperature to degrees C.
The user has to convert to Kelvin or Fahrenheit themselves.
The temperature can be below zero.

steps table, details see page 14.

|  device     |   flow step    |  temp step  |
|:------------|:--------------:|:-----------:|
| SLF3S-0600F |    0.1 μl/min  |    0.005°C  |
| SLF3S-1300F |      2 μl/min  |    0.005°C  |
| SLF3C-1300F |      2 μl/min  |    0.005°C  |
| SLF3S-0600D |                |
| SLF3S-1300D |                |
| SLF3S-4000B |  31.25 μl/min  |


To check for certain events that might affect the measurement,
on can check the signal flags.
Use **readFlowTempSignal()** to read the signal flags as they
cannot be read independently.

- **uint16_t getSignalFlags()** see table below.

flags table, details see page 11.

|  bit  |  meaning           |  notes  |
|:-----:|:-------------------|:--------|
|   0   |  Air-in flag       |
|   1   |  High Flow flag    |
|  2-4  |  unused            |
|   5   |  smoothing active  |  exponential averaging used.
|  6-15 |  unused            |


### Product ID

This functions can be useful for e.g. log files.

- **uint32_t readProductID()** returns the 32 bit product ID

|  device     |  product ID  |
|:------------|:------------:|
| SLF3S-0600F |  0x07030302  |
| SLF3S-1300F |  0x07030402  |
| SLF3C-1300F |  0x07030202  |
| SLF3S-0600D |  0x07030901  |
| SLF3S-1300D |  0x07030801  |
| SLF3S-4000B |  0x07030501  |

See example SLF3S_product_serial.ino.


### Serial number

This functions can be useful for e.g. log files.

- **uint64_t readSerialNR()** returns 64 bit unique serial number.

Note: the return value of **readSerialNR()** is an uint64_t.
The Arduino framework cannot print this by default, so one need
either to split in two 32 bit integers or use e.g. **hex()** from
the printHelpers library. See example SLF3S_product_serial.ino.


### Error handling

- **int genericReset()** generic I2C reset call, will reset all devices
 on the I2C bus, so use with care.
- **int getLastError()** returns the last known error, see table below.

Error table

|  value   |  description         |  notes  |
|:--------:|:---------------------|:--------|
|   0x00   |  SLF3S_OK            |
|   0x01   |  SLF3S_CRC_ERROR     |  data might be corrupted
|   0x10   |  SLF3S_NOT_READY     |  device is in warming up
|   0x11   |  SLF3S_NO_REQUEST    |  no request started
|  other   |  e.g. low level I2C  |  see Wire documentation.


### Calibrating

**Use with care, read datasheets**.

These functions allow to override the conversion scales defined by the datasheets.
They can also be used to calibrate for other liquids.

- **void setFlowScale(float fs)**
- **float getFlowScale()**
- **void setTempScale(float ts)**
- **float getTempScale()**


### Debug

Retrieve last raw measurements for debugging.

- **int16_t getRawFlow()**
- **int16_t getRawTemp()**


## Future

#### Must

- improve documentation
  - elaborate description
  - run performance sketch on hardware and fill table above.
- get hardware to test


#### Should

- improve error handling
- implement SLF3C library.
  - derived / stand alone / add to this library?
- check if stopMeasurement() saves energy?
  - mandatory 60 ms to get stable again?

#### Could

- add **readFlowNoCRC()** to skip CRC (max performance)
- add examples
- add sketch to change I2C address
  - need hardware to test
- add unit tests (if possible)


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


