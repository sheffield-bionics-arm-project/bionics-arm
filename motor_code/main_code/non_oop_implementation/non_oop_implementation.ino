// for arduino nano
// arm motor controller code

//motor setup
#include <Servo.h>
Servo Thumb;
Servo Finger1; // name better naming each finger properly
Servo Finger2;
Servo Finger3;
Servo Finger4;
Servo ThumbToPinkey;

#define ThumbPin 6
#define Finger1Pin 10
#define Finger2Pin 9
#define Finger3Pin 8
#define Finger4Pin 7
#define ThumbToPinkeyPin 5

void ClenchFist();
void Thumbup();
void SpiderMan();
void Thumbtopinky();
void Pointerfinger();
void relax();
void Slowclose();
void Cycle();

//other setup



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Thumb.attach(ThumbPin);       //40 <--> 145 The L16-R servo linac works from a servo input of 40 (lower limit) to 145 (upper limit) 5cm extension|| linacs dont move outside of this range
  Finger1.attach(Finger1Pin);
  Finger2.attach(Finger2Pin);
  Finger3.attach(Finger3Pin);
  Finger4.attach(Finger4Pin);
  ThumbToPinkey.attach(ThumbToPinkeyPin);
  Serial.println("Initializing...");
//linac motor setup base position (relaxed hand) 
/*
 Thumb.write(140);
 Finger1.write(140);
 Finger2.write(130);
 Finger3.write(130);
 Finger4.write(130);
 ThumbToPinkey.write(130); // check physical setup and adjust this to fully relaxed position
 delay(2000);
 Serial.println("Intialized");
 */
 }

void loop() { // Each finger control for testing rn
 Thumb.write(45);
 Finger1.write(140);
 Finger2.write(140);
 Finger3.write(140);
 Finger4.write(140);
 delay(1000);

}






















void ClenchFist(){ // all fingers clenched so linacs at lower limit of 50 ish depends on physical set up (old hand was fully clenched at 50 ish)
  Thumb.write(45);
 Finger1.write(50);
 Finger2.write(50);
 Finger3.write(50);
 Finger4.write(50);
 ThumbToPinkey.write(50); 
 delay(20);
  
}

void Thumbup(){
  Thumb.write(130); // full extension at 13o on old hand
 Finger1.write(50);
 Finger2.write(50);
 Finger3.write(50);
 Finger4.write(50);
 ThumbToPinkey.write(50); 
 delay(20);
  
}

void Slowclose(){
 Finger4.write(50);
 delay(1000);
 Finger3.write(50);
 delay(1000);
 Finger2.write(50);
 delay(1000);
 Finger1.write(50);
 delay(1000);
 Thumb.write(70);
 delay(1000);
 ThumbToPinkey.write(50); 
 delay(20);
  
}

void SpiderMan(){
  Thumb.write(130);
 Finger1.write(130);
 delay(200);
 Finger2.write(45);
 Finger3.write(45);
 Finger4.write(130);
 ThumbToPinkey.write(130); 
 delay(20);
  
}

void Thumbtopinky(){
 Thumb.write(1300);
 Finger1.write(1300);
 Finger2.write(1300);
 Finger3.write(1300);
 Finger4.write(1300);
 ThumbToPinkey.write(1300); 
 delay(20);
 Thumb.write(45);
 Finger4.write(50);
 delay(200);
}


void Pointerfinger(){
  Thumb.write(45);
 Finger1.write(130);
 Finger2.write(50);
 Finger3.write(50);
 Finger4.write(50);
 ThumbToPinkey.write(130); 
 delay(20);
}
void relax(){
 Thumb.write(130);
 Finger1.write(130);
 Finger2.write(130);
 Finger3.write(130);
 Finger4.write(130);
 ThumbToPinkey.write(130); // check physical setup and adjust this to fully relaxed position
 delay(20);
}
