#include <Wire.h>

/* ---------- MEDDELANDEN ---------- */

/* Från plattformen */
const uint8_t BORJA_PLOCKA = 0x22;
const uint8_t LAMNA_AV_OBJEKT = 0x25;
/* ---------------- */


/* Från påbyggnaden */
const uint8_t LYCKAT_LYFT = 0x14;
const uint8_t MISSLYCKAT_LYFT = 0x15;

const uint8_t LYCKAD_AVLAMNING = 0x16;
const uint8_t MISSLYCKAD_AVLAMNING = 0x17;
/* ---------------- */

/* --------------------------------- */


uint8_t currentState = 0;
uint8_t send_buf[] = {0};
uint8_t I2C_KUB_ADDRESS = 15;

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
    case BORJA_PLOCKA:
      Serial.println("plockar...");
      delay(5000);
      send_buf[0] = LYCKAT_LYFT;
      currentState = 0;
      Serial.println("klar med plockningen.");
      break;

    case LAMNA_AV_OBJEKT:
      Serial.println("lämnar objeketet...");
      delay(5000);
      send_buf[0] = LYCKAD_AVLAMNING;
      currentState = 0;
      Serial.println("objeketet lämnat.");
      break;
  }
}

void receiveEvent(int nbrOfBytes)
{
  uint8_t cmd = Wire.read();

  switch (cmd)
  {
    case BORJA_PLOCKA:
      Serial.println("BORJA_PLOCKA");
      currentState = BORJA_PLOCKA;
      break;

    case LAMNA_AV_OBJEKT:
      Serial.println("LAMNA_AV_OBJEKT");
      currentState = LAMNA_AV_OBJEKT;
      break;
  }
}

void requestEvent()
{
  Serial.println("requestEvent");
  switch (send_buf[0])
  {
    case LYCKAT_LYFT:
      Serial.println("SEND LYCKAT_LYFT");
      Wire.write(LYCKAT_LYFT);
      send_buf[0] = 0;
      break;

    case LYCKAD_AVLAMNING:
      Serial.println("SEND LYCKAD_AVLAMNING");
      Wire.write(LYCKAD_AVLAMNING);
      send_buf[0] = 0;
      break;
  }
}


