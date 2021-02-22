/* Companion v.2.4
Created by luxnaut */

//Libraries
#include "Adafruit_APDS9960.h" //Color and gesture library
#include <Wire.h> //I2C library
#include <Adafruit_Sensor.h> //Adafruit Unified Sensor System library
#include <Adafruit_BNO055.h> //BNO055 library
#include <utility/imumaths.h> //IMU maths library
#include <WiFi.h> //Wifi library
#include <OSCMessage.h> //OSC message library

//Wifi setup
char ssid[] = "ssid"; //SSID
char pass[] = "pass"; //Password
const IPAddress outIP(127, 0, 0, 1); //Receiving IP address

//UDP 
WiFiUDP UDP; //Instance of UDP for messages

//OSC
const int outPort = 8000; //Port for sending message to receiving IP

//Sensor instances
Adafruit_APDS9960 apds; //Instance of the color/gesture sensor
Adafruit_BNO055 bno = Adafruit_BNO055(55); //Instance of BNO0ff sensor (0x28 or 0x29 I2C address)

//BNO055 sensor variables
float quatW, quatX, quatY, quatZ;
float eulerX, eulerY, eulerZ;
float linAccX, linAccY, linAccZ;
float accelX, accelY, accelZ;
float gyroX, gyroY, gyroZ;
float gravX, gravY, gravZ;
float magnetX, magnetY, magnetZ;

//Light color
uint16_t r, g, b, c;
float red, green, blue, clearL;

void setup() {
  Serial.begin(115200); //Begin serial communication (for testing)
  
  if(!apds.begin()){ //If sensor not found
    Serial.println("Failed to initialize color/gesture sensor");
  } else {
    Serial.println("Color/gesture sensor found!"); //If sensor found
  }

  if(!bno.begin()){ //If sensor not found
    Serial.println("Failed to find abs ori sensor");
  } else {
    Serial.println("Abs ori sensor found!"); //If sensor found
  }

  delay(2500);

  //Enable color/gesture sensors
  apds.enableColor(true); //Enables color sensing
  apds.enableProximity(true); //Enable proximity sensor
  apds.enableGesture(true); //Enable gesture sensor

  //Enable external crystal
  bno.setExtCrystalUse(true); //Enable external crystal use (increased accuracy)

  WiFi.begin(ssid, pass);
}

void loop() {
  imu::Quaternion quat = bno.getQuat();  //W,X,Y,Z Quaternions
  imu::Vector <3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER); //X/Y/Z Euler Angles (degrees)
  imu::Vector <3> linAcc = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL); //X/Y/Z Linear Acceleration (m/s^2)
  imu::Vector <3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);//X/Y/Z Acceleration (m/s^2)
  imu::Vector <3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE); //X/Y/Z Radian Orientation (rad/s)
  imu::Vector <3> grav = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY); //X/Y/Z Gravity (m/s^2)
  imu::Vector <3> magnet = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER); //X/Y/Z Magnetometer (uT)

  apds.getColorData(&r, &g, &b, &c); //Red, green, blue, and clear light

  //Data type conversion to float for OSC communication
  float quatW = (float) quat.w();
  float quatX = (float) quat.x();
  float quatY = (float) quat.y();
  float quatZ = (float) quat.z();

  float eulerX = (float) euler.x();
  float eulerY = (float) euler.y();
  float eulerZ = (float) euler.z();

  float linAccX = (float) linAcc.x();
  float linAccY = (float) linAcc.y();
  float linAccZ = (float) linAcc.z();

  float accX = (float) accel.x();
  float accY = (float) accel.y();
  float accZ = (float) accel.z();

  float gyroX = (float) gyro.x();
  float gyroY = (float) gyro.y();
  float gyroZ = (float) gyro.z();

  float gravX = (float) grav.x();
  float gravY = (float) grav.y();
  float gravZ = (float) grav.z();

  float magX = (float) magnet.x();
  float magY = (float) magnet.y();
  float magZ = (float) magnet.z();

  red = r; 
  green = g;
  blue = b;
  clearL = c;

  //OSC message setup
  OSCMessage msg("/Companion"); //Message tag
  msg.add(quatW).add(quatX).add(quatY).add(quatZ);
  msg.add(eulerX).add(quatY).add(quatZ);
  msg.add(linAccX).add(linAccY).add(linAccZ);
  msg.add(accX).add(accY).add(accZ);
  msg.add(gyroX).add(gyroY).add(gyroZ);
  msg.add(gravX).add(gravY).add(gravZ);
  msg.add(magX).add(magY).add(magZ);
  msg.add(red).add(green).add(blue).add(clearL);
  UDP.beginPacket(outIP, outPort); //UDP setup w/ outIP (address to send to) and outPort (port to send over)
  msg.send(UDP); //Send the message
  UDP.endPacket(); //Close the packet
  msg.empty(); //Empty the message for new data

  delay(10); //Sample rate delay for data smoothing
}
