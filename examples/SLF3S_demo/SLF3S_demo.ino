//
//    FILE: SLF3S_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/SLF3S


#include "SLF3S.h"


SLF3S slf;


void setup()
{
  while(!Serial);
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
}


void loop()
{
  slf.readFlowTemp();
  float flow = slf.getFlow();
  float temp = slf.getTemperature();
  Serial.print(millis());
  Serial.print("\t");
  Serial.print(flow);
  Serial.print("\t");
  Serial.println(temp);
  Serial.println();
  delay(2000);
}


//  -- END OF FILE --
