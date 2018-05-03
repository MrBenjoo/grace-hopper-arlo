/* Created by Stefan Angelov
    Date: 15.5.2017
*/

#include <Servo.h>
#include <Wire.h>

Servo myservo;
int I2C_PAB_ADR = 8;

void setup()
{
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  //pinMode(4, OUTPUT);

  Wire.begin(I2C_PAB_ADR);
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
   
  while(Wire.available()) 
  {
    int aByte = Wire.read();
    Serial.println(aByte);
  }
  
  int x = Wire.read();
  switch  (x)
  {
    case 1:
      Serial.println("1");
      digitalWrite(13, HIGH);
      break;

    case '1':
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

    case 6:
      Serial.println("6");
      digitalWrite(4, HIGH);
      break;
  }
}

void requestEvent()
{
  Serial.println("READ");
  Wire.write(2);
}

