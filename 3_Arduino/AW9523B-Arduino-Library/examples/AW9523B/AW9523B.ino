#include "DEV_Config.h"
#include "AW9523B.h"


void setup() {
  if(AW9523B_Init() != 0){
      Serial.print("init err!!!");
      return 0;
  }

  Serial.println("test:Connect the 0 port to the 1 port");
  //ouput
  PortMode(0, 0);
  // PortOutput(0, 0xf0);
  // PortMode(1, 0);
  // PortOutput(1, 0xff);
  // PortInput(1);

  //input  
  PortMode(1, 1);

  UBYTE tm = 1;
  UBYTE readpin;
  for(UBYTE x =0; x<8; x++){
    PortOutput(0, 1<<x);
    if(ReadIntPin() == 0){
      while(ReadIntPin() != 0){
        Serial.println("int");
        }
      readpin =  PortInput(1);
      Serial.println(1<<x);
      Serial.println(readpin);
      Serial.print("read is change, Trigger interrupted");
      Serial.println(tm);
      }
      tm = tm + 1;
    }

}

void loop() {

  
}
