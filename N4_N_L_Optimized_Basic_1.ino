//#include <Arduino.h>


void setup() {

  for (int l = 22; l < 38; l++) {
    pinMode((l), INPUT_PULLUP);
  }
  pinMode(3, INPUT_PULLUP);
  for (int k = 38; k < 54; k++) {
    pinMode((k), OUTPUT);
  }
  for (int m = 0; m < 16; m++) {
    pinMode(("A" + (m)), INPUT_PULLUP);
  }
  pinMode(13, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(10, OUTPUT);

  Serial.begin(9600);
  Serial2.begin(9600);

  for (int i = 17; i < 33; i++) {
    Serial2.print((String)"t" + i + ".txt=\"""" + (i - 16) + ". OFF\"" + char(255) + char(255) + char(255));
  }

}


String command;
String str_buffer;
int CurrentChar = 0;
bool IsValveOK = true;
bool StateIsGoodForWork = false;

void loop() {

  Serial2.available() == 0;
  int val1 = Serial2.read();

  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    str_buffer += c; //makes the String readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (str_buffer.length() > 0) {
    command = str_buffer;
    command.trim();
    str_buffer = "";

    int QuestionPos = command.indexOf("?");
    if (QuestionPos > 0) {
      readValves(command);
      StateIsGoodForWork = false;
      command = "";
    }
    else
      StateIsGoodForWork = true;
    Serial2.print((String)"t34.txt=\"""\"" + char(255) + char(255) + char(255));
  }

  if (digitalRead(3) == 1) {
    if (digitalRead(8) == 0) {
      //STATION IS OPEN
      Serial2.print((String)"t35.txt=\"""ATTENTION\"" + char(255) + char(255) + char(255));
      delay(1000);
      Serial2.print((String)"t35.txt=\"""JIG OPEN !\"" + char(255) + char(255) + char(255));
      delay(1000);
      Serial2.print((String)"t35.txt=\"""RESETING\"" + char(255) + char(255) + char(255));
      delay(1000);
      Serial2.print((String)"t35.txt=\"""TASK!\"" + char(255) + char(255) + char(255));
      delay(1500);
      delay(1000);
      Serial2.print((String)"t35.txt=\"""\"" + char(255) + char(255) + char(255));
      StateIsGoodForWork = false;
      delay(500);
    }

    if (digitalRead(A0) == 1) {
      //SMA IS UP
      Serial2.print((String)"t35.txt=\"""ATTENTION\"" + char(255) + char(255) + char(255));
      delay(1000);
      Serial2.print((String)"t35.txt=\"""SMA OPEN !\"" + char(255) + char(255) + char(255));
      delay(1000);
      Serial2.print((String)"t35.txt=\"""\"" + char(255) + char(255) + char(255));
      StateIsGoodForWork = false;
      delay(500);
    }
    if (digitalRead(A1) == 1) {
      Serial2.print((String)"t35.txt=\"""ATTENTION\"" + char(255) + char(255) + char(255));
      delay(1000);
      Serial2.print((String)"t35.txt=\"""SMA OPEN !\"" + char(255) + char(255) + char(255));
      delay(1000);
      Serial2.print((String)"t35.txt=\"""\"" + char(255) + char(255) + char(255));
      StateIsGoodForWork = false;
      delay(500);
    }
  }

  //EMERGENCY
  if (digitalRead(13) == 0) {
    digitalWrite(10, HIGH);
    delay(1000);
    digitalWrite(10, LOW);
    Serial2.print((String)"t34.txt=\"""CANCELED\"" + char(255) + char(255) + char(255));
    ClearALLs();
    delay(500);
    StateIsGoodForWork = false;
  }

  if (StateIsGoodForWork) {
    int tmpDelayInCycle = 0;
    IsValveOK = true;
    Serial.println("START");
    digitalWrite(10, HIGH);
    for (int charIndex = 0; charIndex < command.length(); charIndex++) {
      CurrentChar = command[charIndex];
      switch (CurrentChar) {
        case 49 ... 57:
          // CurrentChar + 1 = 50.
          tmpDelayInCycle = ((CurrentChar + 2) - 50) * 500;  // each next character is incremented by 500 up to 4.5 sec
          delay(tmpDelayInCycle);
          break;
        case 65 ... 80: {
            // valve from 38 until 53   65-27=38
            digitalWrite((CurrentChar - 27), HIGH);
            Serial2.print((String)"t" + (CurrentChar - 48) + ".txt=\"""" + (CurrentChar - 64) + ". ON\"" + char(255) + char(255) + char(255));
            // sensor from 22 until 37  65-43=22
            if (getSensorStatus((CurrentChar - 43), LOW) == false) {
              // if sensor not closed in 5 sec.... print ERROR and exit from cycle.
              Serial2.print((String)"t" + (CurrentChar - 48) + ".txt=\"""" + (CurrentChar - 64) + ". ERR\"" + char(255) + char(255) + char(255));
              Serial2.print((String)"t34.txt=\"""V " + (CurrentChar - 64) + " ERR\"" + char(255) + char(255) + char(255));
              Serial.println(CurrentChar - 64);
              IsValveOK = false;
              ClearALLs();
              break;
            }
            else {
              // print from t17 until t38  65-48=17
              //Serial2.print((String)"t" + (CurrentChar - 48) + ".txt=\"""" + (CurrentChar - 64) + ". ON\"" + char(255) + char(255) + char(255));
              Serial2.print((String)"t34.txt=\"""\"" + char(255) + char(255) + char(255));
            }
          }
          break;
        case 97 ... 112: {
            digitalWrite((CurrentChar - 59), LOW);
            // valve from 38 until 53   97-59=38
            if (getSensorStatus((CurrentChar - 75), HIGH) == false) {
              IsValveOK = false;
              Serial2.print((String)"t" + (CurrentChar - 80) + ".txt=\"""" + (CurrentChar - 96) + ". ERR\"" + char(255) + char(255) + char(255));
              Serial2.print((String)"t34.txt=\"""V " + (CurrentChar - 96) + " ERR\"" + char(255) + char(255) + char(255));
              Serial.println(CurrentChar - 96);
            }
            else {

              // from t17 until t38  97-80=17
              Serial2.print((String)"t" + (CurrentChar - 80) + ".txt=\"""" + (CurrentChar - 96) + ". OFF\"" + char(255) + char(255) + char(255));
            }
          }
          break;
      }
      if (IsValveOK == false) {
        break;
      }
      CanWePowerOFF_LAMP();

    }
    if (IsValveOK != false)
      Serial.println("0");

    Serial.println("STOP");
    command = "";
    StateIsGoodForWork = false;
  }

  if (digitalRead(3) == 0) {
    Serial2.print((String)"t40.txt=\"""Test Mode\"" + char(255) + char(255) + char(255));
    delay(50);
    if ((val1 > 64) && (val1 < 81)) {
      digitalWrite((val1 - 27), HIGH);
      //Serial.println("Valve is ON");
    }
    if ((val1 > 96) && (val1 < 113)) {
      digitalWrite((val1 - 59), LOW);
      //   Serial.println("Valve is OFF");
    }

  }
  else {
    Serial2.print((String)"t40.txt=\"""\"" + char(255) + char(255) + char(255));
    delay(50);
  }
  if (val1 == 83) {
    digitalWrite(10, HIGH);
  }
  if (val1 == 115) {
    digitalWrite(10, LOW);
  }
  for (int PortNumber = 22; PortNumber < 38; PortNumber++) {
    int PortValue = digitalRead(PortNumber);
    if (PortValue == 0) {
      Serial2.print((String)"t" + (PortNumber - 22) + ".txt=\"""" + (PortNumber - 21) + ". OK\"" + char(255) + char(255) + char(255));

    }
    else {
      Serial2.print((String)"t" + (PortNumber - 22) + ".txt=\"""--\"" + char(255) + char(255) + char(255));

    }
    delay(10);
  }

}


void ClearALLs() {
  for (int x = 53; x > 37; x--) {
    if (digitalRead(x) == LOW) {
      continue;
    }
    else {
      digitalWrite(x, LOW);
      Serial2.print((String)"t" + (x - 20) + ".txt=\"""" + (x - 37) + ". OFF\"" + char(255) + char(255) + char(255));
      delay(500);
      CanWePowerOFF_LAMP();
    }
  }
}


void res() {
  while (Serial.available())
    Serial.read();
}

bool getSensorStatus(int SensorValue, int ValvePosition) {
  int loopDelay = 0;
  while (loopDelay < 5) {
    if (digitalRead(SensorValue) == ValvePosition) { // if sensor OK result = true and exit
      return true;
      break;
    }
    else
      delay(1000);
    loopDelay++;
  }
  if (loopDelay == 5)
    return false;
}


bool CanWePowerOFF_LAMP() {
  bool SensorON = true;
  for (int i = 22; i < 38; i++) {
    if (digitalRead(i) == LOW) {
      SensorON = false;
      continue;
    }
  }

  if (SensorON == false) {
    digitalWrite(10, HIGH);
    //Serial.println("LAMP On");
  }
  else {
    digitalWrite(10, LOW);
    //Serial.println("LAMP Off");
  }

  return SensorON;
}
void readValves(String command) {
  int ValveStatus;
  int CurrentChar = 0;
  command.toUpperCase();
  command.trim();
  Serial.println("START");
  for (int charIndex = 0; charIndex < command.length() - 1; charIndex++) {
    CurrentChar = command[charIndex];
    ValveStatus = digitalRead(CurrentChar - 43);
    if (ValveStatus == 0)
      Serial.println("1");
    if (ValveStatus == 1)
      Serial.println("0");


  }
  Serial.println("STOP");


}


