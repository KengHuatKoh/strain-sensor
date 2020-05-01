/* 
 * This is an example of reading the sensor analog input using StrainSensor object. 
 * It also uses the StrainSensor API to calibrate min max angle for knee joint
 */


/*
#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
*/
#include "StrainSensor.h"
/*
ros::NodeHandle nh;
std_msgs::Int16 s1_deg, s2_deg, s3_deg;
ros::Publisher s1deg_pub("s1_deg", &s1_deg);
ros::Publisher s2deg_pub("s2_deg", &s2_deg);
ros::Publisher s3deg_pub("s3_deg", &s3_deg);
std_msgs::Float32 s1_v, s2_v, s3_v;
ros::Publisher s1v_pub("s1_v", &s1_v);
ros::Publisher s2v_pub("s2_v", &s2_v);
ros::Publisher s3v_pub("s3_v", &s3_v);
*/
const int sitButton = 11, standButton = 12;
int sitButtonState, standButtonState;
float s1_voltage, s2_voltage, s3_voltage;
int16_t s1_degree, s2_degree, s3_degree;

StrainSensor s1(A8, 5);
StrainSensor s2(A9, 5);
StrainSensor s3(A10, 5);

void setup() { 
  pinMode(sitButton, INPUT);
  pinMode(standButton, INPUT);
/*  
  nh.initNode();
  nh.advertise(s1v_pub);
  nh.advertise(s2v_pub);
  nh.advertise(s3v_pub);
  nh.advertise(s1deg_pub);
  nh.advertise(s2deg_pub);
  nh.advertise(s3deg_pub);
*/
}

void loop() {
  sitButtonState = digitalRead(sitButton);
  if (sitButtonState == HIGH) {
    s1.angle90Calib();
    s2.angle90Calib();
    s3.angle90Calib();
  }
  standButtonState = digitalRead(standButton);
  if (standButtonState == HIGH) {
    s1.angle0Calib();
    s2.angle0Calib();
    s3.angle0Calib();
  }
  s1_voltage = s1.readVoltage(); s2_voltage = s2.readVoltage(); s3_voltage = s3.readVoltage();
  s1_degree = s1.readAngle(); s2_degree = s2.readAngle(); s3_degree = s3.readAngle();
/*
  s1_v.data = s1.readVoltage();  s1v_pub.publish(&s1_v);
  s2_v.data = s2.readVoltage();  s2v_pub.publish(&s2_v);
  s3_v.data = s3.readVoltage();  s3v_pub.publish(&s3_v);
  s1_deg.data = s1.readAngle();  s1deg_pub.publish(&s1_deg);
  s2_deg.data = s2.readAngle();  s2deg_pub.publish(&s2_deg);
  s3_deg.data = s3.readAngle();  s3deg_pub.publish(&s3_deg);
  nh.spinOnce();
*/
}
