void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(12,INPUT);
pinMode(13,OUTPUT);
}
void loop() {
  digitalWrite(13,HIGH);
  delay(50);
  digitalWrite(13,LOW);
  delayMicroseconds(50);  
}
