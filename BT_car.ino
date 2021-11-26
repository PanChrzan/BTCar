#include <Servo.h>

#define pin_DC_11 6
#define pin_DC_12 5
#define pin_DC_21 8
#define pin_DC_22 7
#define pin_servo 9

Servo mServo;
char receive[10];
uint8_t i = 0;

void setup() {
  Serial.begin(9600);
  mServo.attach(pin_servo);
  pinMode(pin_DC_11, OUTPUT);
  pinMode(pin_DC_12, OUTPUT);
  pinMode(pin_DC_21, OUTPUT);
  pinMode(pin_DC_22, OUTPUT);
}

void loop() {
  if (Serial.available() > 0)
  {
    char c = (char)Serial.read();
    if (c == '\n')
    {
      receive[i] = 0;
      switch(receive[0])
      {
        case 'm':
          servo();
          break;
        case 'f':
          motor_f();
          break;
        case 'b':
          motor_b();
          break;
        case 's':
          motor_s();
          break;
      }
      i = 0;
    }
    else
    {
      receive[i] = c;
      i++;
    }
  }
}

void servo()
{
  unsigned int val = atoi(receive + 2);
  mServo.write(val);
}

void motor_f()
{
  switch(receive[1])
  {
    case '1':
      digitalWrite(pin_DC_11, HIGH);
      break;
    case '2':
      digitalWrite(pin_DC_21, HIGH);
      break;
  }
}

void motor_b()
{
  switch(receive[1])
  {
    case '1':
      digitalWrite(pin_DC_12, HIGH);
      break;
    case '2':
      digitalWrite(pin_DC_22, HIGH);
      break;
  }
}

void motor_s()
{
  switch(receive[1])
  {
    case '1':
      digitalWrite(pin_DC_11, LOW);
      digitalWrite(pin_DC_12, LOW);
      break;
    case '2':
      digitalWrite(pin_DC_21, LOW);
      digitalWrite(pin_DC_22, LOW);
      break;
  }
}
