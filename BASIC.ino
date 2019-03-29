
const int button1Pin = 22;
const int button2Pin = 23;
const int button3Pin = 24;
const int button4Pin = 25;
const int button5Pin = 26;
const int button6Pin = 27;
const int button7Pin = 28;
const int button8Pin = 29;
const int button9Pin = 30;
const int button10Pin = 31;
const int button11Pin = 32;
const int button12Pin = 33;
const int button13Pin = 34;
const int button14Pin = 35;
const int button15Pin = 36;
const int button16Pin = 37;
const int button19Pin = A0;
const int button20Pin = A1;
const int button21Pin = A2;
const int button22Pin = A3;
const int button23Pin = A4;
const int button24Pin = A5;
const int button25Pin = A6;
const int button26Pin = A7;
const int button27Pin = A8;
const int button28Pin = A9;
const int button29Pin = A10;
const int button30Pin = A11;
const int button31Pin = A12;
const int button32Pin = A13;
const int button33Pin = A14;
const int button34Pin = A15;
const int button17Pin = 13;
const int button18Pin = 10;
const int button35Pin = 3;
int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;
int button5State = 0;
int button6State = 0;
int button7State = 0;
int button8State = 0;
int button9State = 0;
int button10State = 0;
int button11State = 0;
int button12State = 0;
int button13State = 0;
int button14State = 0;
int button15State = 0;
int button16State = 0;
int button17State = 0;
int button18State = 0;
int button19State = 0;
int button20State = 0;
int button21State = 0;
int button22State = 0;
int button23State = 0;
int button24State = 0;
int button25State = 0;
int button26State = 0;
int button27State = 0;
int button28State = 0;
int button29State = 0;
int button30State = 0;
int button31State = 0;
int button32State = 0;
int button33State = 0;
int button34State = 0;
int button35State = 0;



void setup() {
  pinMode(button17Pin, INPUT_PULLUP);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
  pinMode(button5Pin, INPUT_PULLUP);
  pinMode(button6Pin, INPUT_PULLUP);
  pinMode(button7Pin, INPUT_PULLUP);
  pinMode(button8Pin, INPUT_PULLUP);
  pinMode(button9Pin, INPUT_PULLUP);
  pinMode(button10Pin, INPUT_PULLUP);
  pinMode(button11Pin, INPUT_PULLUP);
  pinMode(button12Pin, INPUT_PULLUP);
  pinMode(button13Pin, INPUT_PULLUP);
  pinMode(button14Pin, INPUT_PULLUP);
  pinMode(button15Pin, INPUT_PULLUP);
  pinMode(button16Pin, INPUT_PULLUP);
  pinMode(button18Pin, INPUT_PULLUP);
  pinMode(button19Pin, INPUT_PULLUP);
  pinMode(button20Pin, INPUT_PULLUP);
  pinMode(button21Pin, INPUT_PULLUP);
  pinMode(button22Pin, INPUT_PULLUP);
  pinMode(button23Pin, INPUT_PULLUP);
  pinMode(button24Pin, INPUT_PULLUP);
  pinMode(button25Pin, INPUT_PULLUP);
  pinMode(button26Pin, INPUT_PULLUP);
  pinMode(button27Pin, INPUT_PULLUP);
  pinMode(button28Pin, INPUT_PULLUP);
  pinMode(button29Pin, INPUT_PULLUP);
  pinMode(button30Pin, INPUT_PULLUP);
  pinMode(button31Pin, INPUT_PULLUP);
  pinMode(button32Pin, INPUT_PULLUP);
  pinMode(button33Pin, INPUT_PULLUP);
  pinMode(button34Pin, INPUT_PULLUP);
  pinMode(button35Pin, INPUT_PULLUP);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(53, OUTPUT);
  pinMode(8, OUTPUT);

  Serial.begin(9600);
  Serial2.begin(9600);

  for (int i = 17; i < 33; i++) {
    Serial2.print((String)"t" + i + ".txt=\"""" + (i - 16) + ". OFF\"" + char(255) + char(255) + char(255));
  }

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


  button17State = digitalRead(button17Pin);
  button1State = digitalRead(button19Pin);
  button2State = digitalRead(button20Pin);
  button3State = digitalRead(button21Pin);
  button4State = digitalRead(button22Pin);
  button5State = digitalRead(button23Pin);
  button6State = digitalRead(button24Pin);
  button7State = digitalRead(button25Pin);
  button8State = digitalRead(button26Pin);
  button9State = digitalRead(button27Pin);
  button10State = digitalRead(button28Pin);
  button11State = digitalRead(button29Pin);
  button12State = digitalRead(button30Pin);
  button13State = digitalRead(button31Pin);
  button14State = digitalRead(button32Pin);
  button15State = digitalRead(button33Pin);
  button16State = digitalRead(button34Pin);
  button35State = digitalRead(button35Pin);

  if (button35State == HIGH) {
    if (digitalRead(10) == 0) {
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
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(8, LOW);
    Serial2.print((String)"t34.txt=\"""CANCELED\"" + char(255) + char(255) + char(255));
    ClearALLs();
    delay(500);
    StateIsGoodForWork = false;
  }

  if (StateIsGoodForWork) {
    int tmpDelayInCycle = 0;
    IsValveOK = true;
    Serial.println("START");
    digitalWrite(8, HIGH);
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

  if (button35State == LOW) {
    if ((val1 > 64) && (val1 < 81)) {
      digitalWrite((val1 - 27), HIGH);
      //Serial.println("Valve is ON");
    }
    if ((val1 > 96) && (val1 < 113)) {
      digitalWrite((val1 - 59), LOW);
      //   Serial.println("Valve is OFF");
    }

  }
  if (val1 == 83) {
    digitalWrite(8, HIGH);
  }
  if (val1 == 115) {
    digitalWrite(8, LOW);
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

  if (button35State == LOW) {
    Serial2.print((String)"t40.txt=\"""Test Mode\"" + char(255) + char(255) + char(255));
    delay(50);
  }
  else {
    Serial2.print((String)"t40.txt=\"""\"" + char(255) + char(255) + char(255));
    delay(50);
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
  for(int i = 22; i < 38; i++){
    if(digitalRead(i) == LOW){
      SensorON = false;  
      continue;
    }
  }

  if (SensorON == false){
    digitalWrite(8, HIGH);
    //Serial.println("LAMP On");
    }
 else{
    digitalWrite(8, LOW);
    //Serial.println("LAMP Off");
  }
  
  return SensorON;
}


