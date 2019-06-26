
// compiler error handling
#include "Compiler_Errors.h"

// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

// touch behaviour definitions
#define firstPin 0
#define lastPin 11

char active = 'a';

void setup(){  
  Serial.begin(57600);

  while(!Serial) ; {} 
  
  pinMode(LED_BUILTIN, OUTPUT);

  if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);

  MPR121.setTouchThreshold(40);
  MPR121.setReleaseThreshold(20);

  Serial.flush();
}

void loop(){
  active = readTouchInputs();
  Serial.println(active);
  delay(100);
}


char readTouchInputs(){
  if(MPR121.touchStatusChanged()){
    
    MPR121.updateTouchData();
    
    if(MPR121.getNumTouches()<=1){
      for (int i=0; i < 12; i++){  // Check which electrodes were pressed
        if(MPR121.isNewTouch(i)){
              digitalWrite(LED_BUILTIN, HIGH);
              return 'D';       
        }else{
          if(MPR121.isNewRelease(i)){
            digitalWrite(LED_BUILTIN, LOW);
              return 'U';
         } 
        }
      }
    }
  }
  return 'a';
}

// port
// /dev/cu.usbmodem14401
