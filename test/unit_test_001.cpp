//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-11-02
// PURPOSE: unit tests for the SLF3S library
//     URL: https://github.com/RobTillaart/SLF3S
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>


#include "SLF3S.h"


unittest_setup()
{
  fprintf(stderr, "SLF3S_LIB_VERSION: %s\n", (char *) SLF3S_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, SLF3S_OK           );
  assertEqual(0x01, SLF3S_CRC_ERROR    );
  assertEqual(0x10, SLF3S_NOT_READY    );
  assertEqual(0x11, SLF3S_REQUEST_ERROR);
}


unittest(test_constructor)
{
  SLF3S slf;

  assertEqual(0x08, slf.getAddress())
}


unittest_main()


//  -- END OF FILE --

