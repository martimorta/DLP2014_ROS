#include <ros.h>
#include <Servo.h> 
#include <std_msgs/Float32.h>
#include <std_msgs/ColorRGBA.h>

#define PIN_LED_VERMELL 3
#define PIN_LED_VERD 5
#define PIN_LED_BLAU 6
#define PIN_MOTOR ??
#define PIN_POTENCIOMETRE ??

ros::NodeHandle nh;

// === publisher ===
std_msgs::Int32 motor_value;
ros::Publisher motorPub("/posicio", &motor_value);
Servo motor_servo;

// === subscriber ===
void colorCb( const std_msgs::ColorRGBA& color_value){
  // canvia el color del led
  // http://www.instructables.com/id/Fading-RGB-LED-Arduino/?ALLSTEPS
  analogWrite( PIN_LED_VERMELL, color_value.r );
  analogWrite( PIN_LED_VERD,    color_value.g );
  analogWrite( PIN_LED_BLAU,    color_value.b );
}
ros::Subscriber<::> colorSub("color", &colorCb );

// === estructura Arduino ===
void setup() {
  nh.initNode();
  nh.advertise(motorPub);
  nh.subscribe(colorSub);
 
  motor_servo.attach(PIN_MOTOR);
  motor_servo.write(90);  // set servo to mid-point
}
void loop() {
  // ========== MOTOR ===========
  // llegir estat del boto
  int posicio = analogRead(PIN_POTENCIOMETRE)*(5.0/255.0);
  posicio = max(posicio, 0);
  posicio = min(posicio, 255);
  // enviar el motor un pas mes enlla
  motor_servo.write(posicio);
  // enviar dades de posicio del motor pel topic
  motor_value.data  = servo.read();
  motorPub.publish( &motor_value );

  nh.spinOnce();
  delay(10);
}
