void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(12,INPUT);
pinMode(13,OUTPUT);
}
void loop() {
  digitalWrite(13,HIGH);
  delayMicroseconds(5000);
  digitalWrite(13,LOW);
  delayMicroseconds(3000);  
}
