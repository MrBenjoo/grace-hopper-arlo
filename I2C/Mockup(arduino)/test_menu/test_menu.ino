#include <Servo.h>

Servo myservo;

const byte numChars = 32;
char receivedChars[numChars];
int menu_lvl[4];
int n = 0;
int i = 0;

int flag_startmenu = 1;
int flag_lvl_choice = 0;
int flag_lvl_one = 1;
int flag_lvl_two = 0;
int flag_lvl_three = 0;
int flag_lvl_four = 0;

int adc_pin = 0;
int adc_value = 0;
int adc_flag = 0;

int pwm_pin = 0;
int pwm_speed = 0;
int pwm_flag = 0;

int dpio_pin = 0;
int dpio_flag = 0;

int servo_pin;
int servo_speed;
int servo_flag = 0;

int sonar_value;
int trig_pin;
int echo_pin;
int sonar_flag = 0;

void setup()
{
  Serial.begin(9600);

  Serial.println("==================================");
  Serial.println("|| Welcome to mockup test program! ||");
  Serial.println("==================================");
}
void loop()
{
  recvWithEndMarker();
  adc_function();
  pwm_function();
  dpio_function();
  servo_function();
}
void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (flag_startmenu == 1)
  {
    Serial.println("Please choose a test area!");

    Serial.println("(1) ADC");
    Serial.println("(2) PWM");
    Serial.println("(3) DPIO");
    Serial.println("(4) Servo");
    Serial.println("(5) HC-SR04");
    flag_startmenu = 0;
  }

  if (Serial.available() > 0 ) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
        Serial.println("1");
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      //Serial.println("2");
      i = atoi(receivedChars);
      menu_lvl[n] = i;
      n++;

      menu();
    }
  }
}
void menu()
{
  if (flag_lvl_one)
  {
    flag_lvl_choice = menu_lvl[0];
    switch (flag_lvl_choice)
    {
      case 1:
        Serial.println("");
        Serial.println("============================================");
        Serial.println("Please input the pin number for ADC reading.");
        Serial.println("============================================");
        flag_lvl_one = 0;
        flag_lvl_two = 1;
        break;
      case 2:
        Serial.println("====================================");
        Serial.println("Please input the pin number for PWM.");
        Serial.println("====================================");
        flag_lvl_one = 0;
        flag_lvl_two = 2;
        break;
      case 3:
        Serial.println("====================================");
        Serial.println("Please input the pin for digital I/O");
        Serial.println("====================================");
        flag_lvl_one = 0;
        flag_lvl_two = 3;
        break;
      case 4:
        Serial.println("===============================");
        Serial.println("Please input the pin for servo.");
        Serial.println("===============================");
        flag_lvl_one = 0;
        flag_lvl_two = 4;
        break;
      case 5:
        Serial.println("=================================================");
        Serial.println(" Please input the trigger pin for HC-SR04 sonar. ");
        Serial.println("=================================================");
        flag_lvl_one = 0;
        flag_lvl_two = 5;
        break;
      default:
        Serial.println("");
        Serial.println("Not an option, please select a valid option");
        Serial.println("");
        flag_startmenu = 1;
        break;
    }
  }

  // ADC MENU OPTION //
  else if (!flag_lvl_one && flag_lvl_two == 1)
  {
    adc_pin = menu_lvl[1];
    Serial.println(adc_pin);
    flag_lvl_choice = atoi(receivedChars);
    Serial.println("(1) Start reading.");
    Serial.println("(2) Stop reading.");
    Serial.println("(3) Reset");

    switch (flag_lvl_choice)
    {
      case 1:
        adc_flag = 1;
        break;
      case 2:
        adc_flag = 0;
        break;
      case 3:
        reset();
        break;
      default:

        break;
    }
  }
  // PWM MENU OPTION //
  // PWM pins on Uno are: (3, 5, 6, 9, 10, or 11)
  else if (!flag_lvl_one && flag_lvl_two == 2)
  {
    pwm_pin = menu_lvl[1];
    Serial.println("Please input PWM speed");
    flag_lvl_three = 2;
    flag_lvl_two = 0;
  }

  else if (!flag_lvl_one && flag_lvl_three == 2)
  {
    pwm_speed = menu_lvl[2];
    flag_lvl_choice = atoi(receivedChars);
    Serial.println("(1) Start PWM.");
    Serial.println("(2) Stop PWM.");
    Serial.println("(3) Reset");

    switch (flag_lvl_choice)
    {
      case 1:
        pwm_flag = 1;
        break;
      case 2:
        pwm_flag = 0;
        analogWrite(pwm_pin, 0);
        break;
      case 3:
        reset();
        break;
      default:

        break;
    }
  }
  else if (!flag_lvl_one && flag_lvl_two == 3)
  {
    dpio_pin = menu_lvl[1];
    flag_lvl_choice = atoi(receivedChars);
    Serial.println("(1) ON.");
    Serial.println("(2) OFF.");
    Serial.println("(3) Reset");

    switch (flag_lvl_choice)
    {
      case 1:
        dpio_flag = 1;
        break;
      case 2:
        dpio_flag = 0;
        digitalWrite(dpio_pin, LOW);
        break;
      case 3:
        reset();
        break;
      default:

        break;
    }
  }
  // SERVO MENU OPTION //
  else if (!flag_lvl_one && flag_lvl_two == 4)
  {
    servo_pin = menu_lvl[1];
    Serial.println("Please input servo speed");
    Serial.println("Servo values are the following: ");
    Serial.println("0-89 turns the servo counterclockwise, lower value = higher speed");
    Serial.println("90 is full stop.");
    Serial.println("91-180 turns the servo clockwise, higher value = higher speed");
    flag_lvl_three = 4;
    flag_lvl_two = 0;
  }

  else if (!flag_lvl_one && flag_lvl_three == 4)
  {
    servo_speed = menu_lvl[2];
    flag_lvl_choice = atoi(receivedChars);
    Serial.println("(1) Start rotating servo.");
    Serial.println("(2) Stop rotating servo.");
    Serial.println("(3) Reset");

    switch (flag_lvl_choice)
    {
      case 1:
        servo_flag = 1;
        break;
      case 2:
        servo_flag = 0;
        myservo.attach(servo_pin);
        myservo.write(90);
        break;
      case 3:
        reset();
        break;
      default:
        break;
    }
  }
  else if (!flag_lvl_one && flag_lvl_two == 4)
  {
    trig_pin = menu_lvl[1];
    Serial.println("Please input the echo pin for the sonar");
    flag_lvl_three = 4;
    flag_lvl_two = 0;
  }

  // SONAR MENU OPTION // 
  else if (!flag_lvl_one && flag_lvl_three == 4)
  {
    echo_pin = menu_lvl[2];
    flag_lvl_choice = atoi(receivedChars);
    Serial.println("(1) Start reading sonar distance.");
    Serial.println("(2) Stop reading sonar distance.");
    Serial.println("(3) Reset");

    switch (flag_lvl_choice)
    {
      case 1:
        sonar_flag = 1;
        break;
      case 2:
        sonar_flag = 0;
        break;
      case 3:
        reset();
        break;
      default:
        break;
    }
  }
}
void adc_function()
{
  if (adc_flag)
  {
    adc_value = analogRead(adc_pin);
    Serial.print("adc_value: ");
    Serial.println(adc_value);
    Serial.print("adc_pin: ");
    Serial.println(adc_pin);
    delay(100);
  }
}
void pwm_function()
{
  if (pwm_flag)
  {
    analogWrite(pwm_pin, pwm_speed);
  }
}

void dpio_function()
{
  if (dpio_flag)
  {
    pinMode(dpio_pin, OUTPUT);
    digitalWrite(dpio_pin, HIGH);
  }
}

void servo_function()
{
  if (servo_flag)
  {
    myservo.attach(servo_pin);
    myservo.write(servo_speed);
    delay(15);
  }
}

void sonar_function()
{
  long duration, cm;
  if (sonar_flag)
  {
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);

    digitalWrite(trig_pin, LOW);
    delayMicroseconds(5);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);

    pinMode(echo_pin, INPUT);
    duration = pulseIn(echo_pin, HIGH);

    cm = (duration / 2) / 29.1;

    Serial.print("Distance in cm: ");
    Serial.println(cm);
  }
}

void reset()
{
  flag_startmenu = 1;
  flag_lvl_choice = 0;
  flag_lvl_one = 1;
  flag_lvl_two = 0;
  flag_lvl_three = 0;
  flag_lvl_four = 0;

  adc_flag = 0;
  pwm_flag = 0;
  dpio_flag = 0;
}



