#include <Servo.h>
#include "PCA9685.h"
#include <Wire.h>

ServoDriver servo;

int gesture = 0;

bool calm = false; 
bool happy = false; 
bool mad = false; 

void setup() {
  Wire.begin();
  Serial.begin(9600);
  servo.init(0x7f);
}

void loop() {
 while (Serial.available()) {
  gesture = Serial.read();
  }
   if (gesture == 1){
    calm = true;
    happy = false;
    mad = false;
  }
    if (gesture == 2){
    happy = true;
    mad = false;
    calm = false;
  }
    if (gesture == 3){
    mad = true;
    happy = false;
    calm = false;
  }

  //3 states
  if (calm){
    //no general movement
  }
   if (happy){
   servo.setAngle(1, 0);
   delay(1000);
  /* servo.setAngle(2, 0);
   delay(1000);
   servo.setAngle(3, 0);
   delay(1000);

   servo.setAngle(1, 60);
   delay(1000);
   servo.setAngle(2, 60);
   delay(1000);
   servo.setAngle(3, 60);
   delay(1000);
  }
   if (mad){
   servo.setAngle(1, 0);
   delay(1000);
   servo.setAngle(2, 0);
   delay(1000);
   servo.setAngle(3, 0);
   delay(1000);

   servo.setAngle(1, 90);
   delay(1000);
   servo.setAngle(2, 90);
   delay(1000);
   servo.setAngle(3, 90);
   delay(1000);
  }

}