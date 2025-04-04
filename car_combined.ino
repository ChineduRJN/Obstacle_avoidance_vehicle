#include <Servo.h>

Servo myservo;
int pos = 0;

const int In1 = 7;
const int In2 = 8;
const int In3 = 9;
const int In4 = 10;
const int ENA = 5;
const int ENB = 4;
const int trigPin = 51;
const int echoPin = 53;

const int threshold = 1740;
const int SPEED = 210;


int left_distance;
int right_distance;
int movement_speed = 130;
int turning_speed = 180;
int right_turning_time = 665;
int left_turning_time = 650;
int reverse_time = 1000;

long duration, cm;


void setup() {
  // put your setup code here, to run once:
  myservo.attach(6);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); //optional. It's for the serial monitor
  myservo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  // convert the time into a distance
  cm = get_distance();
  move_forward();

if(cm<threshold){
  move_stop();
  left_distance = look_left();
  right_distance = look_right();
  if(right_distance > left_distance && right_distance > threshold){
  move_right();
  
  }
  else if(left_distance > right_distance && left_distance > threshold){
    move_left();    
  }
  else{
    move_backward();
    left_distance = look_left();
    right_distance = look_right();
      if(left_distance < threshold && right_distance < threshold){
        move_right();
        delay(500);
        move_right();
      }
  }
}


}

long get_distance(){
    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
 
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    return pulseIn(echoPin, HIGH);
}


int look_left(){
  myservo.write(90);
  delay(500);
  myservo.write(180);
  delay(15);
  //the loop princess had went to 165 instead of 180 for some reason.
  // Is it due to some physical limitation of the servo?
  delay(500);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  int cm = duration;

  myservo.write(90);
  delay(15);

  return cm;
}



int look_right(){
  myservo.write(90);
  delay(500);

  
  myservo.write(0);                   
  delay(500);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  int cm = duration;

  delay(100); 
  
  myservo.write(90);
  delay(15);
  
  return cm; 
}


void move_forward(){
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);

  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}


void move_backward(){
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);

  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);

  delay(reverse_time);
  
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  
}

void move_stop(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
 }

void move_right(){
  analogWrite(ENA, turning_speed);
  analogWrite(ENB, turning_speed);

  digitalWrite(In1, HIGH); //motors on the left. ie they're connected to out1 and out2
  digitalWrite(In2, LOW);
  
  digitalWrite(In3, LOW); //motors on the right
  digitalWrite(In4, HIGH);
  // Before the motor was turning left instead of right so adjusted it to high, low, low, high
  delay(right_turning_time);
  
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);  
  
}


void move_left(){
  analogWrite(ENA, turning_speed);
  analogWrite(ENB, turning_speed);

  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  
  digitalWrite(In3, HIGH); 
  digitalWrite(In4, LOW);

  delay(left_turning_time);
  
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);      
}
