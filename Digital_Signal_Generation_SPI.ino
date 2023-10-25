#include <SPI.h>
const int ClockPin = 13;
const int DataInputPin = 12;
const int DataOutputPin = 11;
const int FrameSyncPin = 10;
const int TestPin = 4;


void setup() {
  // put your setup code here, to run once:
  pinMode(FrameSyncPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  pinMode(DataInputPin, OUTPUT);
  pinMode(DataOutputPin, OUTPUT);
  pinMode(TestPin, OUTPUT);
  SPI.begin();
  SPI.setDataMode(SPI_MODE1);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(FrameSyncPin, LOW);
  //digitalWrite(TestPin, HIGH);
  SPI.transfer16(32768);
  digitalWrite(FrameSyncPin, HIGH);
  SPI.transfer16(32768);
  //digitalWrite(TestPin, LOW);
}
