#include <Servo.h>

Servo myservox, myservoy; // create servo object to control a servo
// a maximum of eight servo objects can be created

void setup () {

  myservox.attach(9);
  myservoy.attach(8);
}
float anglex, angley;

void loop () {
  float anglex, angley;
  anglex = 90.0 - 20.0 * sin( (float) millis() / 1580.0 );
  angley = 40.0 - 40.0 * cos( (float) millis() / 580.0 );
  myservox.write(anglex);
  myservoy.write(angley);
  delay(15);
}
