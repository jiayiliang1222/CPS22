float speed = 0;
float angle = 0;
int direction;
int gesture = 3;

boolean calm = false; 
boolean happy = false; 
boolean mad = false; 

void setup() {
  size(600, 600);
  background(0);
}

void draw() {
   background(0);
  textSize(64);
  fill(255);
  text(angle,20,100);
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
   speed = 0.1;
  }
   if (happy){
   speed = 0.3;
  }
   if (mad){
   speed = 0.5;
  }
  
  angle = angle + speed * direction;
  if (angle>=90){
    direction= -1;
  }else if(angle <= 0){
    direction = 1;
  }

}
