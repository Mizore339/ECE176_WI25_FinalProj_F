#include <Servo.h>
#include<stdio.h>
#include<stdlib.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
char result = '1';
int pos = 0;    // variable to store the servo position
int active = 3;
int side = -1;
const int trigPin = 9;
const int echoPin = 10;
int origDistance = 0;
int duration = 0;
int distance = 0;
int lightlevel_ori = 40;
int lightlevel = 0;
unsigned long myTime;
int darkObject = 0;
int ready = 0;
char test;
void setup() {
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  myservo.write(90);
  delay(4000);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //delay(2000);
  origDistance = calibrate();
  pinMode(A0, INPUT);
  lightlevel_ori = analogRead(A0);
  //pinMode(2,INPUT);
}

void loop() {
  
/* lightlevel = analogRead(A0);
 //Serial.println(lightlevel-lightlevel_ori);
 if ((lightlevel - lightlevel_ori)>50)
 {
    if (darkObject == 0)
    {
      myTime = millis();
      darkObject = 1;
    }
    else
    {
      if ((millis() - myTime) > 4000)
      {
          ready = 1;
      }
    }
    
 }
 else
 {
    darkObject = 0;
    ready = 0;
 }*/
 if (Serial.available() > 0) {
    //while (Serial.available() > 1) { // Clear buffer
    //    Serial.read();
    //}
    test = Serial.read();
    Serial.println(test);
    
    if (test == '1') {
        lightlevel = analogRead(A0);
        if (lightlevel < lightlevel_ori*5){
          Serial.println("Plastic");
        }
        else{
          Serial.println("Could be paper wrap or can");
        }
        side = 1;
        myservo.write(180);
        delay(2000);
        myservo.write(90);
        delay(4000);
        darkObject = 0;
        ready = 0;
    }      
    else if (test == '0') {
        side = 0;
        myservo.write(0);
        delay(2000);
        myservo.write(90);
        delay(4000); 
        darkObject = 0;
        ready = 0;
    }
  }
 /* else if (ready)
  {
        myservo.write(0);
        delay(2000);
        myservo.write(90);
        delay(4000); 
        darkObject = 0;
        ready = 0;
  }*/
}

int calibrate()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  origDistance = distance;
  return origDistance;
}

int sense()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}

//if (active >= 2)
//  {
//    if (side == 0){
//      myservo.write(0);
//      delay(2000);
//      myservo.write(90);
//      delay(4000);
//    }
//    else
//    {
//      myservo.write(180);
//      delay(2000);
//      myservo.write(90);
//      delay(4000);
//    }
