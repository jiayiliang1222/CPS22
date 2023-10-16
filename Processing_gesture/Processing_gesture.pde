import oscP5.*;
import processing.serial.*;

OscP5 oscP5;  
Serial myPort;
color backgroundColor = color(0);  
int gesture = 0;

int debounceDuration = 1000;// Debounce duration in milliseconds
long lastChangeTime = 0;// Timestamp for the last change

boolean calm = false; 
boolean happy = false; 
boolean mad = false; 

void setup() {  
  size(400, 400);
  oscP5 = new OscP5(this, 12000);
  noStroke();
  
   printArray(Serial.list());
  // this prints out the list of all available serial ports on your computer.
  
 // myPort = new Serial(this, Serial.list()[ 4 ], 9600);
  // find the port "/dev/cu.usbmodem----" or "/dev/tty.usbmodem----" 
  
  
}

void draw() {  
  fill(backgroundColor, 10);
  rect(0, 0, width, height);
  
  textSize(64);
  fill(255);
  
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
  
  if (calm){
  text("Calm", 40, 120); 
 
  }
   if (happy){
  text("Happy", 40, 120); 

  }
   if (mad){
  text("Mad", 40, 120); 
  }
  
 //  myPort.write(gesture);

}

void oscEvent(OscMessage theOscMessage) {  
  int oscArg = int(theOscMessage.get(0).floatValue()); 
  gesture = oscArg;
 /*  if (millis() - lastChangeTime >= debounceDuration) {
      gesture = oscArg;  // if the duration is too short, ignore this change
    }
    lastChangeTime = millis(); */
}
