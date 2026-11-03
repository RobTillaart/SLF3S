//
//    FILE: SLF3S_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/SLF3S
//
//  To be used with Serial plotter.

#include "SLF3S.h"


SLF3S slf;
uint32_t lastTime = 0;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SLF3S_LIB_VERSION: ");
  Serial.println(SLF3S_LIB_VERSION);
  Serial.println();

  Wire.begin();

  slf.begin(600);  //  SLF3S-0600F
  slf.requestH2O();
  while (!slf.isReady()); //  wait for stable up to 60 ms.

  Serial.println("Flow \tTemperature");
}


void loop()
{
  uint32_t now = millis();
  if (now - lastTime >= 50)  //  ~20 samples / second.
  {
    lastTime += 50;
    slf.readFlowTemp();
    float flow = slf.getFlow();
    float temp = slf.getTemperature();
    Serial.print(flow);
    Serial.print("\t");
    Serial.println(temp);
    Serial.println();
  }
  delay(50);
}


//  -- END OF FILE --
