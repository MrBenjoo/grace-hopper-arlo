/* Created by Stefan Angelov
    Date: 15.5.2017
*/

#include <Servo.h>
#include <Wire.h>

Servo myservo;
int I2C_POS_ADR = 16;

void setup()
{
  Serial.begin(9600);

  pinMode(13, OUTPUT);

  Wire.begin(I2C_POS_ADR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  myservo.attach(2);
  myservo.write(90);

  Serial.println("Waiting for cmd");
}

int x = 0;

void loop()
{
  delay(100);  
}

/* Receive event that activates once Master(Due) sends data. The switch function has different commands depending on what test was selected at Master menu*/
void receiveEvent(int howMany)
{
  int x = Wire.read();
  switch  (x)
  {
    case 1:
      Serial.println("1");
      digitalWrite(13, HIGH);
      break;

    case 2:
      Serial.println("2");
      digitalWrite(13, LOW);
      break;

    case 3:
      Serial.println("3");
      myservo.write(180);
      break;

    case 4:
      Serial.println("4");
      myservo.write(0);
      break;

    case 5:
      Serial.println("5");
      myservo.write(90);
      break;
  }
}

void requestEvent()
{                        // x1  y1  x2  y2  x3   y3  x4  y4   x5  y5
  const uint8_t sendBuf[] = "0123456789";
  Serial.println("READ");
  Wire.write(sendBuf, 10);
}
