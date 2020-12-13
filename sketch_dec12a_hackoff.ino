// components used: Arduino Uno, Stepper Motor, Accelerometer and Servo motor
// in the code we have considered the use of stepper motor as its functionality is closer to that of linear actuator.
#include<Servo.h>
#include<Stepper.h>

int StepsPerRevol = 2048; //2048 steps to complete 360 degrees
int delaytime = 2000;
int motSpeed = 10; // motor Speed - revolutions per minute
// connect Driver board IN1 to pin 8, IN2 to pin 9, IN3 to pin 10 and IN$ to pin 11
Stepper myStepper(StepsPerRevol, 8, 10, 9, 11);
Servo servo;
int pin = 10;

int x_pin = A0;
int y_pin = A1;
int z_pin = A2;


// Volts per G-Force
float sensitivity = 0.206;

void setup() {
  
  myStepper.setSpeed(motSpeed);
  servo.attach(10);
  servo.write(0);
  delay(2000);
  analogReference(EXTERNAL);
  Serial.begin(9600);
}

void loop() {

  float x;
  float y;
  float z;

  // Read pins and convert to G
  x = (analogRead(x_pin) - 512) * 3.3 / (sensitivity * 1023);
  y = (analogRead(y_pin) - 512) * 3.3 / (sensitivity * 1023);
  z = (analogRead(z_pin) - 512) * 3.3 / (sensitivity * 1023);

  // Display acceleration
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);

  delay(100);
  
  servo.write(0);
  if(x>0 || y>0) // whenever the door moves, first the servo motor is signaled which sprays the sanitizer, then Stepper motor is signaled to wipe the handle 
  {
    servo.write(170);
    delay(4000);
    myStepper.step(StepsPerRevol);
    delay(delaytime);
    myStepper.step(-StepsPerRevol);
    delay(delaytime);
  }
  
}
