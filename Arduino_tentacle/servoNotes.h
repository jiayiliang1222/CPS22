
//      ******************************************************************
//      *                                                                *
//      *         An example for using the "CNC V3 Shield" board         *
//      *                                                                *
//      *            S. Reifel & Co.                6/24/2018            *
//      *                                                                *
//      ******************************************************************


// Available on Amazon at very low cost is a stepper driver board shield for 
// the Arduino Uno. It is called the "CNC V3 Shield".  It supports up to 
// 4 steppers.  This example shows how to use it.
//  
//
// Documentation at:
//         https://github.com/Stan-Reifel/FlexyStepper
//
//
// Note: FlexyStepper's companion library that supports faster step rates can 
// be found here:
//         https://github.com/Stan-Reifel/SpeedyStepper
//
//
// For all driver boards, it is VERY important that you set the motor 
// current before running the example.  This is typically done by adjusting
// a potentiometer on the board.  Read the driver board's documentation to 
// learn how.

// *********************************************************************** 


 // Note 1: It is assumed that you are using a stepper motor with a 
  // 1.8 degree step angle (which is 200 steps/revolution). This is the
  // most common type of stepper.
  //
  // Note 2: It is also assumed that your stepper driver board is  
  // configured for 1x microstepping.
  //
  // It is OK if these assumptions are not correct, your motor will just
  // turn less than a full rotation when commanded to. 
  //
  // Note 3: This example uses "relative" motions.  This means that each
  // command will move the number of steps given, starting from it's 
  // current position.


