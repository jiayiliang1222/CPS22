import processing.serial.*;
//import controlP5.*;
import oscP5.*;

OscP5 oscP5;  
Serial myPort;  // Create object from Serial class
//ControlP5 cp5;  //For testing and code safety, not useful in formal version

int Step = 0;
int totalStep = 0;
int totalStep_ = 0;
int gesture = 1;
int gesture_= 1;

String message;


//boolean calm = false; 
//boolean happy = false; 
//boolean sad = false; 
//boolean mad = false; 

void setup() {
  size(800, 400);
  //cp5 = new ControlP5(this);
  myPort = new Serial(this, "COM8", 9600);  // Replace "COM3" with your Arduino's port
  oscP5 = new OscP5(this, 12121);
  
  //cp5.addSlider("totalStep")
  //   .setPosition(50, 250)
  //   .setSize(600, 100)
  //   .setRange(-200, 200)
  //   .setValue(0);
  //   
}

void draw() {
  background(9,9,245);
  textSize(50);
  if (gesture  == 2){
   text("Jellyfish feels calm.",175,200);
  }  if (gesture  == 3){
   text("Jellyfish feels happy.",175,200);
  }
    if (gesture  == 4){
   text("Jellyfish feels sad.",175,200);
  }
    if (gesture  == 5){
   text("Jellyfish feels nervous.",175,200);
  }

  if (gesture_ != gesture)
  {
     String message = str(gesture) + "/n";
     println(gesture);
     gesture_ = gesture;
   //  print("gesture is: ");
   //  println(message);
     myPort.write(message);
    }
    
  //totalStep = int(cp5.getController("totalStep").getValue());
  //if (totalStep_ != totalStep)
  //{
  //   Step = totalStep-totalStep_;
  //   String message = str(Step);
  //   println("message: " + message);
  //   totalStep_ = totalStep;
  //  }
  //  text("Total Step: " + totalStep_, 50, 100);
}
void keyPressed() {
  if (key == '1') {
    println("1");
    gesture = 1; 
    myPort.write("1\n"); 
  }
   if (key == '2') {
    println("2");
        gesture = 2; 

    myPort.write("2\n"); 
  }
  if (key == '3') {
    println("3");
        gesture = 3; 

    myPort.write("3\n"); 
  }
  if (key == '4') {
    println("4");
        gesture = 4; 

    myPort.write("4\n"); 
  }
   if (key == '5') {
    println("5");
        gesture = 5; 

    myPort.write("5\n"); 
  }
}

void oscEvent(OscMessage msg) {
  
  // Check if the message has an address pattern of /wek/outputs
  if (msg.checkAddrPattern("/wek/outputs") == true) {
    
    
    // Get the first argument of the message as a float
    gesture = int(msg.get(0).floatValue());
  }
}
