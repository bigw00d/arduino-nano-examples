void setup() {
  //start serial connection
  Serial.begin(115200);
  //configure pin 2 as an input and enable the internal pull-up resistor
//  pinMode(2, INPUT_PULLUP);
//  pinMode(13, OUTPUT);
  pinMode(4, INPUT);

}

void SerialHexPrint(char n) {
  Serial.print("0x");
  if ( n >= 0 )Serial.print(n < 16 ? "0" : "");
  Serial.print((n & 0x000000FF), HEX);
}

void loop() {
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(4);
  //print out the value of the pushbutton
  Serial.println(sensorVal);
  // Serial.print("PORTD :");
  // SerialHexPrint(PORTD);
  Serial.print("PIND :");
  SerialHexPrint(PIND);
  Serial.print(", DDRD :");
  SerialHexPrint(DDRD);
  Serial.println("");

  delay(3000);
}
