String incomingString = "";   //for incoming serial data
int stopBit = 0;
int resetCounter = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  //Serial.write(45); // send a byte with the value 45

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingString = Serial.readString();

    //Serial.print("qabot#received: ");
    //Serial.println(incomingString);

    if (incomingString=="qabot#stop") {
      int bytesSent = Serial.write("\x02qabot#stop\x03"); //send the signal to stop processing
      stopBit = 1;
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  // Let's just fix to write only once
  Serial.write("\x02qabot#start\x03"); //send the signal to stop processing
  stopBit = 1;
  
  if (stopBit==0) {
    int bytesSent = Serial.write("\x02qabot#start\x03"); //send the signal to stop processing
    digitalWrite(LED_BUILTIN, HIGH);
  }

  ++resetCounter;
  String displayCounter = String(resetCounter);
  //Serial.println("Reset counter: " + displayCounter);
  
  if (resetCounter>150) {
    // after 100 times of delay (for 500 milli-seconds), send the qabot start signal again.
    resetCounter = 1;
    stopBit = 0;
  }
  
  delay(500);                  // waits for 35 milli-second?
}
