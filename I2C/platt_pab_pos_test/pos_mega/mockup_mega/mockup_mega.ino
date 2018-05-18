#include <Wire.h>

void setup()
{
  Serial.begin(9600);

  Wire.begin(16);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  Serial.println("Waiting for cmd");
}

uint8_t sendBuf[] = {200, 200, 40, 40, 54, 65, 99, 115, 0, 0};

void loop()
{
  if (sendBuf[8] > 250 || sendBuf[9] > 250)
  {
    sendBuf[8] = 0;
    sendBuf[9] = 0;
  }
  else
  {
    sendBuf[8] += random(1, 4);
    sendBuf[9] += random(1, 4);
    Serial.print("x = ");
    Serial.println(sendBuf[8]);
    Serial.print("y = ");
    Serial.println(sendBuf[9]);
    Serial.println("");
  }
  delay(200);
}


void receiveEvent(int howMany)
{
  // Do nothing 
}

void requestEvent()
{
  Serial.println("READ");
  Wire.write(sendBuf, 10);
}
