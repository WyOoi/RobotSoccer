#include "BluetoothSerial.h"

//--------Pin on L298N---------//
int ENA = 25;
int IN1 = 33;
int IN2 = 32;
int ENB = 14;
int IN3 = 27;
int IN4 = 26;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

const int frequency = 500;
const int motorLeft = 0;
const int motorRight = 1;
const int resolution = 8;
BluetoothSerial SerialBT;
//================================================
unsigned char command, command_old;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("SoccerRobot_1"); // Robot Bluetooth Name

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  ledcSetup(motorLeft, frequency, resolution);
  ledcAttachPin(ENA, motorLeft);
  ledcSetup(motorRight, frequency, resolution);
  ledcAttachPin(ENB, motorRight);
}

void loop() {
 if (SerialBT.available()) {
command = SerialBT.read(); 
} 
//Handle command received
//======================================
if(command_old != command){
if(command == 'a'){
//Perform Task a here
forward();
}
else if(command == 'b'){
//Perform Task b here 
reverse();
}
else if(command == 'c'){
//Perform Task b here 
turn_Left();
}
else if(command == 'd'){
//Perform Task b here 
turn_Right();
}
else if(command == 'e'){
//Perform Task b here 
stop();
} 
command_old = command;
} 
//=======================================
}

void forward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(motorLeft, 150);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(motorRight, 200);
}

void reverse(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(motorLeft, 150);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  ledcWrite(motorRight, 200);
}

void turn_Left(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(motorLeft, 130);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(motorRight, 130);
}

void turn_Right(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(motorLeft, 130);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  ledcWrite(motorRight, 130);
}

void stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  ledcWrite(motorLeft, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(motorRight, 0);
}

void curve_Left(){
  //tactical
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(motorLeft, 110);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(motorRight, 130);
}

void curve_Right(){
  //tactical
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(motorLeft, 130);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  ledcWrite(motorRight, 110);
}