#include <FlexyStepper.h>

//X:Right —
//Y:Left -
//Z:Outward +
//A:Inward +
//+ clockwise
//- counterclockwise

int gesture = 1; 

const int MOTOR_X_STEP_PIN = 2;
const int MOTOR_Y_STEP_PIN = 3;
const int MOTOR_Z_STEP_PIN = 4;
const int MOTOR_A_STEP_PIN = 12;

const int MOTOR_X_DIR_PIN = 5;
const int MOTOR_Y_DIR_PIN = 6;
const int MOTOR_Z_DIR_PIN = 7;
const int MOTOR_A_DIR_PIN = 13;

const int STEPPERS_ENABLE_PIN = 8;

FlexyStepper stepperX;
FlexyStepper stepperY;
FlexyStepper stepperZ;
FlexyStepper stepperA;

float X_speed;//formal parameters
float Y_speed;
float Z_speed;
float A_speed;

float X_acceleration;
float Y_acceleration;
float Z_acceleration;
float A_acceleration;

int X_steps = 0; //run one motor
int Y_steps = 0;
int Z_steps = 0;
int A_steps = 0;


int valueFromProcessing;

int totalStepsX = 0; //for safety reason, when total steps achieve 200, stop running
int totalStepsY = 0;
int totalStepsZ = 0;
int totalStepsA = 0;

bool calm = false; 
bool happy = false; 
bool sad = false; 
bool mad = false;

int totalStep = 0;



void setup() 
{
  pinMode(STEPPERS_ENABLE_PIN, OUTPUT);       
  Serial.begin(9600);

  stepperX.connectToPins(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);
  stepperY.connectToPins(MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN);
  stepperZ.connectToPins(MOTOR_Z_STEP_PIN, MOTOR_Z_DIR_PIN);
  stepperA.connectToPins(MOTOR_A_STEP_PIN, MOTOR_A_DIR_PIN);

  digitalWrite(STEPPERS_ENABLE_PIN, LOW);    
}



void loop() 
{
    if (Serial.available()>0) {
     String receivedString = Serial.readStringUntil('\n');
     if (receivedString.length() > 0) {
       gesture = receivedString.toInt();
     }
    }
switch (gesture) {
        case 1:   //no movement
            break;
        case 2:  //Calm: Tentacles move left and right
           calm = true;
           happy = false;
           sad = false;
           mad = false;
           
    X_speed = 100;
    Y_speed = 100;

    X_acceleration = 50;
    Y_acceleration = 50;

    X_steps = -100; //1.8
    Y_steps = -150;

    runJustTheXStepper(X_speed, X_acceleration, X_steps);
    runJustTheXStepper(X_speed, X_acceleration, -X_steps);
    runJustTheYStepper(Y_speed, Y_acceleration, Y_steps); 
    runJustTheYStepper(Y_speed, Y_acceleration, -Y_steps);                  // Run gesture == 1 relevant motions
            break;
        case 3:
          happy = true;
          mad = false;
          sad = false;
          calm = false;
    Z_speed = 250;
    A_speed = 250;

    Z_acceleration = 150;
    A_acceleration = 150;

    Z_steps = 150;
    A_steps = 150;

    runJustTheZStepper(Z_speed, Z_acceleration, Z_steps);
       delay(2000); 
    runJustTheZStepper(Z_speed, Z_acceleration, -Z_steps);
    //runJustTheAStepper(A_speed, A_acceleration, A_steps); 
    //runJustTheAStepper(A_speed, A_acceleration, -A_steps);                 //  Run gesture == 2 relevant motions
            break;
        case 4:
          mad = false;
          happy = false;
          sad = true;
          calm = false;
          
    A_speed = 50;
    A_acceleration = 50;

    A_steps = 120;

    runJustTheAStepper(A_speed, A_acceleration, A_steps);
    runJustTheAStepper(A_speed, A_acceleration, -A_steps);  
    delay(2000);  //  Run gesture == 3 relevant motions
            break;
        case 5:
          mad = true;
          happy = false;
          sad = false;
          calm = false;
          
    Z_speed = 200;
    A_speed = 200;

    Z_acceleration = 200;
    A_acceleration = 200;

    Z_steps = 80;
    A_steps = 80;

    X_speed = 200;
    Y_speed = 200;

    X_acceleration = 200;
    Y_acceleration = 200;

    X_steps = -80; //1.8
    Y_steps = -80;

    runJustTheZStepper(Z_speed, Z_acceleration, Z_steps);
    runJustTheZStepper(Z_speed, Z_acceleration, -Z_steps);     //  Run gesture == 4 relevant motions
    
    runJustTheXStepper(X_speed, X_acceleration, X_steps);
    runJustTheXStepper(X_speed, X_acceleration, -X_steps);

    runJustTheYStepper(Y_speed, Y_acceleration, Y_steps); 
    runJustTheYStepper(Y_speed, Y_acceleration, -Y_steps);  

    runJustTheAStepper(A_speed, A_acceleration, A_steps); 
    runJustTheAStepper(A_speed, A_acceleration, -A_steps); 
            break;
        default:
            break;
    }
}


void runJustTheXStepper(float X_speed_, float X_acceleration_, float steps_) 
{
  if (totalStepsX < 200 && totalStepsX > -200 ){
  stepperX.setSpeedInStepsPerSecond(X_speed_);
  stepperX.setAccelerationInStepsPerSecondPerSecond(X_acceleration_);
  stepperX.moveRelativeInSteps(steps_);
  totalStepsX += steps_;
  }
  }

void runJustTheYStepper(float Y_speed_, float Y_acceleration_, float steps_) 
{
  if (totalStepsY < 200 && totalStepsY > -200 ){
  stepperY.setSpeedInStepsPerSecond(Y_speed_);
  stepperY.setAccelerationInStepsPerSecondPerSecond(Y_acceleration_);
  stepperY.moveRelativeInSteps(steps_);
  totalStepsY += steps_;
  }
  }
void runJustTheZStepper(float Z_speed_, float Z_acceleration_, float steps_) 
{
  if (totalStepsZ < 200 && totalStepsZ > -200 ){
  stepperZ.setSpeedInStepsPerSecond(Z_speed_);
  stepperZ.setAccelerationInStepsPerSecondPerSecond(Z_acceleration_);
  stepperZ.moveRelativeInSteps(steps_);
  totalStepsZ += steps_;
  }
  }
void runJustTheAStepper(float A_speed_, float A_acceleration_, float steps_) 
{
  if (totalStepsA < 200 && totalStepsA > -200 ){
  stepperA.setSpeedInStepsPerSecond(A_speed_);
  stepperA.setAccelerationInStepsPerSecondPerSecond(A_acceleration_);
  stepperA.moveRelativeInSteps(steps_);
  totalStepsA += steps_;
  }
  }

void runXYZASteppers(long stepsX,long stepsY,long stepsZ,long stepsA) 
{
  float speedInStepsPerSecond = 100;
  float accelerationInStepsPerSecondPerSecond = 100;
  moveXYZAWithCoordination(stepsX, stepsY, stepsZ,stepsA,speedInStepsPerSecond, accelerationInStepsPerSecondPerSecond);
  delay(1000);
}
void runXYZASteppers_(long stepsX,long stepsY,long stepsZ,long stepsA)  
{
  float speedInStepsPerSecond = 100;
  float accelerationInStepsPerSecondPerSecond = 100;
  moveXYZAWithCoordination(stepsX, stepsY, stepsZ, stepsA,speedInStepsPerSecond, accelerationInStepsPerSecondPerSecond);
  delay(1000);
}

void moveXYZAWithCoordination(long stepsX, long stepsY, long stepsZ, long stepsA,float speedInStepsPerSecond, float accelerationInStepsPerSecondPerSecond)
{
  float speedInStepsPerSecond_X;
  float accelerationInStepsPerSecondPerSecond_X;
  float speedInStepsPerSecond_Y;
  float accelerationInStepsPerSecondPerSecond_Y;
  float speedInStepsPerSecond_Z;
  float accelerationInStepsPerSecondPerSecond_Z;
  float speedInStepsPerSecond_A;
  float accelerationInStepsPerSecondPerSecond_A;

  long absStepsX;
  long absStepsY;
  long absStepsZ;
  long absStepsA;
  long maxStep;
  long maxStep_;

  //
  // setup initial speed and acceleration values
  //
  speedInStepsPerSecond_X = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond;
  
  speedInStepsPerSecond_Y = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond;

  speedInStepsPerSecond_Z = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_Z = accelerationInStepsPerSecondPerSecond;

  speedInStepsPerSecond_A = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_A = accelerationInStepsPerSecondPerSecond;


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

  if (stepsZ >= 0)
    absStepsZ = stepsZ;
  else
    absStepsZ = -stepsZ;

  if (stepsA >= 0)
    absStepsA = stepsA;
  else
    absStepsA = -stepsA;

  maxStep = max(absStepsX, max(absStepsY,max(absStepsZ,absStepsA)));
  if (absStepsX == maxStep){
  maxStep_ = stepsX;
  }else if (absStepsY == maxStep){
  maxStep_ = stepsY;
  }else if (absStepsY == maxStep){
  maxStep_ = stepsZ;
  }else if (absStepsA == maxStep){
  maxStep_ = stepsA;
  }

  if (maxStep_ != 0)
  {
    float scalerX = (float)maxStep / (float) absStepsX;
    float scalerY = (float)maxStep / (float) absStepsY;
    float scalerZ = (float)maxStep / (float) absStepsZ;
    float scalerA = (float)maxStep / (float) absStepsA;

    speedInStepsPerSecond_X = speedInStepsPerSecond_X * scalerX;
    accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond_X * scalerX;
    speedInStepsPerSecond_Y = speedInStepsPerSecond_Y * scalerY;
    accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond_Y * scalerY;
    speedInStepsPerSecond_Z = speedInStepsPerSecond_Z * scalerZ;
    accelerationInStepsPerSecondPerSecond_Z = accelerationInStepsPerSecondPerSecond_Z * scalerZ;
    speedInStepsPerSecond_A = speedInStepsPerSecond_A * scalerA;
    accelerationInStepsPerSecondPerSecond_A = accelerationInStepsPerSecondPerSecond_A * scalerA;
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
  // setup the motion for the Y motor
  //
  stepperZ.setSpeedInStepsPerSecond(speedInStepsPerSecond_Z);
  stepperZ.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_Z);
  stepperZ.setTargetPositionRelativeInSteps(stepsZ);

  stepperA.setSpeedInStepsPerSecond(speedInStepsPerSecond_A);
  stepperA.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_A);
  stepperA.setTargetPositionRelativeInSteps(stepsA);
  //
  // now execute the moves, looping until both motors have finished
  //
  while((!stepperX.motionComplete()) || (!stepperY.motionComplete())|| (!stepperZ.motionComplete())|| (!stepperA.motionComplete()))
  {
    stepperX.processMovement();
    stepperY.processMovement();
    stepperZ.processMovement();
    stepperA.processMovement();
  }
}

