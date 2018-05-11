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


void setup() {
  Serial.begin(9600);

  Wire.begin(8);                 /* address */
  Wire.onReceive(receiveEvent);   /* metod (receiveEvent) som läser av meddelanden från plattformen */
  Wire.onRequest(requestEvent);   /* metod (requestEvent) som skickar meddelanden till plattformen */

  Serial.println("Waiting for cmd...");
}

void loop()
{
  // 0 = viloläge
  switch (currentState)
  {
    case BORJA_PLOCKA:
      delay(5000);
      send_buf[0] = LYCKAT_LYFT;
      break;

    case LAMNA_AV_OBJEKT:
      delay(5000);
      send_buf[0] = LYCKAD_AVLAMNING;
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
  Wire.write(send_buf[0]);
}


