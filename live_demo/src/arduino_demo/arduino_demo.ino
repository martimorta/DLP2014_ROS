#include <ros.h>
#include <Servo.h> 
#include <std_msgs/Int32.h>
#include <std_msgs/ColorRGBA.h>

#define PIN_LED_VERMELL 3
#define PIN_LED_VERD 5
#define PIN_LED_BLAU 6
#define PIN_MOTOR 9
#define PIN_POTENCIOMETRE A0

ros::NodeHandle nh;

// === publishers ===
std_msgs::Int32 pot_value;
ros::Publisher potenciometrePub("/potenciometre", &pot_value);
std_msgs::Int32 motor_value;
ros::Publisher motorPub("/posicio", &motor_value);
Servo motor_servo;

// === subscriber ===
void colorCb( const std_msgs::ColorRGBA& color_value){
  analogWrite( PIN_LED_VERMELL, color_value.r );
  analogWrite( PIN_LED_VERD,    color_value.g );
  analogWrite( PIN_LED_BLAU,    color_value.b );
}
ros::Subscriber<std_msgs::ColorRGBA> colorSub("color", &colorCb );

// === estructura Arduino ===
void setup() {
  nh.initNode();
  nh.advertise(potenciometrePub);
  nh.advertise(motorPub);
  nh.subscribe(colorSub);
  std_msgs::ColorRGBA c;
  colorCb(c);

  motor_servo.attach(PIN_MOTOR);
  motor_servo.write(90);  // set servo to mid-point
}
void loop() {
  // ========== MOTOR ===========
  // llegir estat del boto
  int posicio = int(analogRead(PIN_POTENCIOMETRE)*(255.0/1023.0));  
  posicio = max(posicio, 0);
  posicio = min(posicio, 255);
  pot_value.data = posicio;
  potenciometrePub.publish( &pot_value );
  // enviar el motor un pas mes enlla
  motor_servo.write(posicio);
  // enviar dades de posicio del motor pel topic
  motor_value.data  = motor_servo.read();
  motorPub.publish( &motor_value );

  nh.spinOnce();
  delay(10);
}
