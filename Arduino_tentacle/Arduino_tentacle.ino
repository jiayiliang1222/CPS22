#include <Servo.h>
#include "PCA9685.h"
#include <Wire.h>

ServoDriver servo;

int gesture = 1;

//tjd: change name of variable "speed" to "tenticleSpeed"
float speed = 0;

//tjd: change angle to "tenticleRetractionAngle"
float angle = 0;

//tjd: change directinon
int direction;


/* tdj: create an enum to contain the gestures, so they can be referenced by name 

--create datatype to hold of user emotions
--create datatype to hold jellyfish human emotions
--create map to specify the reactions between them; i.e. is the jellyfish just a mirror, or something more? 
maybe it's calm when we're happy, and happy when we're calm (for instance)


*/

bool calm = false; 
bool happy = false; 
bool mad = false; 

/* tdj create struct for servos */


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

/*
// jtd: add averaging to angle. (e.g. angle = (new angle * 0.1) + (lastAngle * 0.9) )

// tjd: add clock/timing library
// tjd: loop to go thru servos could update the order of which servo is adjusted first (randomly) whenever there is a change in emotion 

 */

   servo.setAngle(1, angle);
   servo.setAngle(2, angle);
   servo.setAngle(3, angle);
   servo.setAngle(4, angle);


  }


 // Serial.write(angle);
 // delay(1000);



}
