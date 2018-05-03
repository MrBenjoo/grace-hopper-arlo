/* Created by Stefan Angelov
    Date: 15.5.2017
*/
#include <Wire.h>

const byte numChars = 32;
char receivedChars[numChars];
int menu_lvl[4];
int n = 0;
int i = 0;

int flag_startmenu = 1;
int flag_lvl_choice = 0;
int flag_lvl_one = 0;

void setup()
{
  Serial.begin(9600);

  Wire.begin();
  Serial.println("==================================");
  Serial.println("|| Welcome to iP7 test program! ||");
  Serial.println("==================================");
}

void loop()
{
  recvWithEndMarker();
}
void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (flag_startmenu == 1)
  {
    Serial.println("===============================");
    Serial.println("Please choose a test!");

    Serial.println("(1) Test I - Turn on LED");
    Serial.println("(2) Test II- Turn off LED");
    Serial.println("(3) Test III - Turn servo right");
    Serial.println("(4) Test IV - Turn servo left");
    Serial.println("(5) Test V - Stop servo");
    Serial.println("===============================");
    flag_startmenu = 0;
    flag_lvl_one = 1;
  }

  if (Serial.available() > 0 ) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      //Serial.println("2");
      i = atoi(receivedChars);
      menu_lvl[0] = i;

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
        send_msg(1);
        Serial.println("LED ON");
        flag_lvl_one = 0;
        flag_startmenu = 1;
        break;
      case 2:
        send_msg(2);
        Serial.println("LED OFF");
        flag_lvl_one = 0;
        flag_startmenu = 1;
        break;
      case 3:
        send_msg(3);
        Serial.println("Servo turning right");
        flag_lvl_one = 0;
        flag_startmenu = 1;
        break;
      case 4:
        send_msg(4);
        Serial.println("Servo turning left");
        flag_lvl_one = 0;
        flag_startmenu = 1;
        break;
      case 5:
        send_msg(5);
        Serial.println("Servo off");
        flag_lvl_one = 0;
        flag_startmenu = 1;
        break;
      default:
        Serial.println("");
        Serial.println("Not an option, please select a valid option");
        Serial.println("");
        flag_startmenu = 1;
        break;
    }
  }
}
/* Function for I2C communication, exists to group the relevant library functions. */
void send_msg(int msg)
{
  Wire.beginTransmission(8);
  Wire.write(msg);
  Wire.endTransmission();
}

