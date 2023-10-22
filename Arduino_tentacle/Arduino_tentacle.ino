#include <Servo.h>
#include "PCA9685.h"
#include <Wire.h>

ServoDriver servo;

int gesture = 1;

float speed = 0;

float angle = 0;
int direction;

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


   if (gesture == 2){
    calm = true;
    happy = false;
    mad = false;
  }
    if (gesture == 3){
    happy = true;
    mad = false;
    calm = false;
  }
    if (gesture == 4){
    mad = true;
    happy = false;
    calm = false;
  }

    //3 states
  if (calm){
   speed = 0.05;
  }
   if (happy){
   speed = 0.15;
  }
   if (mad){
   speed = 0.3;
  }
  
  if (gesture>1){
  angle = angle + speed * direction;
  if (angle>=180){
    direction= -1;
  }else if(angle <= 0){
    direction = 1;
  }
   servo.setAngle(1, angle);
   servo.setAngle(2, angle);
   servo.setAngle(3, angle);
   servo.setAngle(4, angle);


  }


 // Serial.write(angle);
 // delay(1000);



}
