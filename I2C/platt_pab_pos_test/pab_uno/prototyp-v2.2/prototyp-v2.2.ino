#include <Wire.h>

/* ---------- MEDDELANDEN ---------- */

/* Från plattformen */
const uint8_t BORJA_PLOCKA = 0x22; // 34
const uint8_t LAMNA_AV_OBJEKT = 0x25; // 37
const uint8_t SKICKA_ID = 0x23; // 23
/* ---------------- */


/* Från påbyggnaden */
const uint8_t LYCKAT_LYFT = 0x14; // 20
const uint8_t MISSLYCKAT_LYFT = 0x15; // 21

const uint8_t LYCKAD_AVLAMNING = 0x16; // 22
const uint8_t MISSLYCKAD_AVLAMNING = 0x17; // 23
/* ---------------- */

const uint8_t OUR_ID = 0x30;

/* --------------------------------- */


uint8_t currentState = 0;
uint8_t send_buf[] = {0};

void setup() {
  Serial.begin(9600);

  Wire.begin(8);                  /* address */
  Wire.onReceive(receiveEvent);   /* metod (receiveEvent) som läser av meddelanden från plattformen */
  Wire.onRequest(requestEvent);   /* metod (requestEvent) som skickar meddelanden till plattformen  */

  Serial.println("Waiting for cmd...");
}

void loop()
{
  switch (currentState)
  {
    case SKICKA_ID:
      Serial.println("-CASE ID-");
      send_buf[0] = SKICKA_ID;
      currentState = 0;
      break;

    case BORJA_PLOCKA:
      Serial.println("-pickup started-");
      delay(5000);
      if (random(0, 2) == 1)
      {
        Serial.println("pickup success");
        send_buf[0] = LYCKAT_LYFT;
      }
      else
      {
        Serial.println("pickup fail");
        send_buf[0] = MISSLYCKAT_LYFT;
      }
      currentState = 0;
      break;

    case LAMNA_AV_OBJEKT:
      Serial.println("-start dropoff-");
      delay(5000);
      if (random(0, 2) == 1)
      {
        Serial.println("dropoff success");
        send_buf[0] = LYCKAD_AVLAMNING;
      }
      else
      {
        Serial.println("dropoff fail");
        send_buf[0] = MISSLYCKAD_AVLAMNING;
      }
      currentState = 0;
      break;
  }
}

void receiveEvent(int nbrOfBytes)
{
  uint8_t cmd = Wire.read();

  switch (cmd)
  {
    case BORJA_PLOCKA:
      Serial.println("rec: BORJA_PLOCKA");
      currentState = BORJA_PLOCKA;
      break;

    case LAMNA_AV_OBJEKT:
      Serial.println("rec: LAMNA_AV_OBJEKT");
      currentState = LAMNA_AV_OBJEKT;
      break;

    case SKICKA_ID:
      Serial.println("rec: SKICKA_ID");
      currentState = SKICKA_ID;
      break;
  }
}

void requestEvent()
{
  switch (send_buf[0])
  {
    case SKICKA_ID:
      Serial.println("Sending SKICKA_ID");
      Wire.write(OUR_ID);
      send_buf[0] = 0;
      break;

    case LYCKAT_LYFT:
      Serial.println("Sending LYCKAT_LYFT\n");
      Wire.write(LYCKAT_LYFT);
      send_buf[0] = 0;
      break;

    case MISSLYCKAT_LYFT:
      Serial.println("Sending MISSLYCKAT_LYFT\n");
      Wire.write(MISSLYCKAT_LYFT);
      send_buf[0] = 0;
      break;

    case LYCKAD_AVLAMNING:
      Serial.println("Sending LYCKAD_AVLAMNING\n");
      Wire.write(LYCKAD_AVLAMNING);
      send_buf[0] = 0;
      break;

    case MISSLYCKAD_AVLAMNING:
      Serial.println("Sending MISSLYCKAD_AVLAMNING\n");
      Wire.write(MISSLYCKAD_AVLAMNING);
      send_buf[0] = 0;
      break;
  }
}


