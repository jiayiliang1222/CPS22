#include <Servo.h>
#include "PCA9685.h"
#include <Wire.h>
#include <BasicTimer.h>
  //NOTE: install Basic Timer library https://github.com/rtnate/arduino-BasicTimer
#include <FlexyStepper.h>
//#include "servoNotes.h" //notes here

const int MOTOR_X_STEP_PIN = 2;
const int MOTOR_X_DIR_PIN = 5;
const int MOTOR_Y_STEP_PIN = 3;
const int MOTOR_Y_DIR_PIN = 6;
const int STEPPERS_ENABLE_PIN = 8;

FlexyStepper stepperX;
FlexyStepper stepperY;

ServoDriver servo;
int gesture;

struct Appendage {

  float smoothingFactor = 0.9; //the higher the value, the most smoothly movement and direction will change
  float destinationAngle;
  float lastDestinationAngle;
  float currentAngle;
  int direction;
  int lastDirection;
  float tentacleSpeed;
  int stepPin;
  int servoPin;
  int dirPin;

  init(int _servoPin) {
  servoPin= _servoPin;
  }
  void setAngle(float _angle) {
    destinationAngle = _angle;

    if (destinationAngle != lastDestinationAngle){
      destinationAngle = lastDestinationAngle;
    }
  }  

  void update() {
    if(currentAngle >= 180 || currentAngle <= 0) {  //we run this check first to make sure we don't send the servos out of bounds
      direction = direction * -1; 
      ///might get some bugs here, like its 180.1 now, and it is supposed to come back to 179. suddenly the speed changes and it becomes 180.05, it will be stuck forever hahaha...
    }
    currentAngle = (currentAngle*smoothingFactor) + (destinationAngle* (1-smoothingFactor));
    //currentAngle = currentAngle * direction;
    //servo.setAngle(servoPin, currentAngle);
  }
} tentacleOne,tentacleTwo, tentacleThree, tentacleFour;


/* tdj: create an enum to contain the gestures, so they can be referenced by name 
--create datatype to hold of user emotions
--create datatype to hold jellyfish human emotions
--create map to specify the reactions between them; i.e. is the jellyfish just a mirror, or something more? 
maybe it's calm when we're happy, and happy when we're calm (for instance)
*/

const int numberOfAnimalEmotions = 5;

enum Emotion { 
  CALM = 1,  //not an emotion, but useful
  HAPPY = 2,  //joyful
  MAD = 3, //angry
  SAD = 4,
  AFRAID = 5 //scared
};

struct animal {
  Emotion currentEmotion;
  float currentSpeed;
  float defaultSpeeds[4];
  void setEmotion(int _emotion) {
   currentEmotion = _emotion;
   currentSpeed = defaultSpeeds[_emotion];
  }
} jellyfish;


void setup() {
  Serial.begin(9600);
  pinMode(STEPPERS_ENABLE_PIN, OUTPUT);       

  // connect and configure the stepper motor to there IO pins
  stepperX.connectToPins(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);
  stepperY.connectToPins(MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN);
 
  // enable the stepper motors
  digitalWrite(STEPPERS_ENABLE_PIN, LOW);     

  tentacleOne.init(1); 
  tentacleTwo.init(2);
  tentacleThree.init(3);
  tentacleFour.init(4);

  jellyfish.currentEmotion = CALM; //starting emotion
  jellyfish.defaultSpeeds[CALM] = 0.05;
  jellyfish.defaultSpeeds[HAPPY] = 0.15;
  jellyfish.defaultSpeeds[MAD] = 0.3;
}


void loop() {

 if (Serial.available() > 0) {
    gesture = Serial.read();

    Serial.print("received [");
    Serial.print(gesture);
    Serial.println("] from computer");


    if(gesture == 0){
      freezeAllMotorFunctions();
    }

    if(gesture == 1) {
      resumeMotorFunctions(gesture);

    }
}

  jellyfish.setEmotion(gesture);

  // Serial.println("Running just the X stepper");
  runJustTheXStepper();

  //
  // now show how to run two stepper motors
  //
  // Serial.println("Running the X & Y steppers");
  runBothXAndYSteppers();

}

void freezeAllMotorFunctions(){
    stepperX.setSpeedInStepsPerSecond(0);
    stepperY.setSpeedInStepsPerSecond(0);
}

void resumeMotorFunctions(int _speed){

  if(_speed >100) _speed = 100;
   
   stepperX.setSpeedInStepsPerSecond(_speed);
  stepperY.setSpeedInStepsPerSecond(_speed);
}


void runJustTheXStepper() 
{
  //
  // set the speed and acceleration rates for the stepper motor
  //
  stepperX.setSpeedInStepsPerSecond(100);
  stepperX.setAccelerationInStepsPerSecondPerSecond(100);

  //
  // Rotate the motor in the forward direction one revolution (200 steps). 
  // This function call will not return until the motion is complete.
  //
  stepperX.moveRelativeInSteps(200);

  //
  // now that the rotation has finished, delay 1 second before starting 
  // the next move
  //
  delay(1000);

  //
  // rotate backward 1 rotation, then wait 1 second
  //
  stepperX.moveRelativeInSteps(-200);
  delay(1000);

  //
  // This time speedup the motor, turning 10 revolutions.  Note if you
  // tell a stepper motor to go faster than it can, it just stops.
  //
  stepperX.setSpeedInStepsPerSecond(800);
  stepperX.setAccelerationInStepsPerSecondPerSecond(800);
  stepperX.moveRelativeInSteps(200 * 10);
  delay(2000);
}



void runBothXAndYSteppers() 
{
  //
  // use the function below to move two motors with speed coordination
  // so that both stop at the same time, even if one moves farther than
  // the other
  //

  //
  // turn both motors 200 steps, but in opposite  directions
  //
  long stepsX = -200 * 1;
  long stepsY = 200 * 1;
  float speedInStepsPerSecond = 100;
  float accelerationInStepsPerSecondPerSecond = 100;
  moveXYWithCoordination(stepsX, stepsY, speedInStepsPerSecond, accelerationInStepsPerSecondPerSecond);
  delay(1000);

  //
  // turn one motor 5 revolutions, the other motor just 1
  //
  stepsX = -200 * 1;
  stepsY = 200 * 5;
  speedInStepsPerSecond = 500;
  accelerationInStepsPerSecondPerSecond = 500;
  moveXYWithCoordination(stepsX, stepsY, speedInStepsPerSecond, accelerationInStepsPerSecondPerSecond);
  delay(3000);
}

// move both X & Y motors together in a coordinated way, such that they each 
// start and stop at the same time, even if one motor moves a greater distance
//
void moveXYWithCoordination(long stepsX, long stepsY, float speedInStepsPerSecond, float accelerationInStepsPerSecondPerSecond)
{
  float speedInStepsPerSecond_X;
  float accelerationInStepsPerSecondPerSecond_X;
  float speedInStepsPerSecond_Y;
  float accelerationInStepsPerSecondPerSecond_Y;
  long absStepsX;
  long absStepsY;

  //
  // setup initial speed and acceleration values
  //
  speedInStepsPerSecond_X = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond;
  
  speedInStepsPerSecond_Y = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond;


  //
  // determine how many steps each motor is moving
  //
  if (stepsX >= 0)
    absStepsX = stepsX;
  else
    absStepsX = -stepsX;
 
  if (stepsY >= 0)
    absStepsY = stepsY;
  else
    absStepsY = -stepsY;


  //
  // determine which motor is traveling the farthest, then slow down the
  // speed rates for the motor moving the shortest distance
  //
  if ((absStepsX > absStepsY) && (stepsX != 0))
  {
    //
    // slow down the motor traveling less far
    //
    float scaler = (float) absStepsY / (float) absStepsX;
    speedInStepsPerSecond_Y = speedInStepsPerSecond_Y * scaler;
    accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond_Y * scaler;
  }
  
  if ((absStepsY > absStepsX) && (stepsY != 0))
  {
    //
    // slow down the motor traveling less far
    //
    float scaler = (float) absStepsX / (float) absStepsY;
    speedInStepsPerSecond_X = speedInStepsPerSecond_X * scaler;
    accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond_X * scaler;
  }

  
  //
  // setup the motion for the X motor
  //
  stepperX.setSpeedInStepsPerSecond(speedInStepsPerSecond_X);
  stepperX.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_X);
  stepperX.setTargetPositionRelativeInSteps(stepsX);


  //
  // setup the motion for the Y motor
  //
  stepperY.setSpeedInStepsPerSecond(speedInStepsPerSecond_Y);
  stepperY.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_Y);
  stepperY.setTargetPositionRelativeInSteps(stepsY);


  //
  // now execute the moves, looping until both motors have finished
  //
  while((!stepperX.motionComplete()) || (!stepperY.motionComplete()))
  {
    stepperX.processMovement();
    stepperY.processMovement();
  }
}





