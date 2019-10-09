#include <SoftwareSerial.h>
String data;
SoftwareSerial mySerial(0, 1); // BTX, BRX

const int leftmotorA = 3;
const int leftmotorB = 5;
const int rightmotorA = 6;
const int rightmotorB = 11;

int carspeed = 204; //0-255

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(leftmotorA, OUTPUT);
  pinMode(leftmotorB, OUTPUT);
  pinMode(rightmotorA, OUTPUT);
  pinMode(rightmotorB, OUTPUT);
}
void loop() {
  Bluetooth();
}

void TurnLeft() {
  analogWrite(leftmotorA, carspeed);
  analogWrite(leftmotorB, 0);
  analogWrite(rightmotorA, carspeed);
  analogWrite(rightmotorB, 0);
}

void TurnRight() {
  analogWrite(leftmotorA, 0);
  analogWrite(leftmotorB, carspeed);
  analogWrite(rightmotorA, 0);
  analogWrite(rightmotorB, carspeed);
}


void Backward() {
  analogWrite(leftmotorA, 0);
  analogWrite(leftmotorB, carspeed);
  analogWrite(rightmotorA, carspeed);
  analogWrite(rightmotorB, 0);
}

void Forward() {
  analogWrite(leftmotorA, carspeed);
  analogWrite(leftmotorB, 0);
  analogWrite(rightmotorA, 0);
  analogWrite(rightmotorB, carspeed);
}

void Stop() {
  analogWrite(leftmotorA, 0);
  analogWrite(leftmotorB, 0);
  analogWrite(rightmotorA, 0);
  analogWrite(rightmotorB, 0);
}

void Bluetooth() {
  while (mySerial.available())
  {
    delay(10);
    char c = mySerial.read();
    if (c == '#') {
      break;
    }
    data += c;
  }

  if (data.length() > 0) {
    Serial.println(data);

    if (data == "forward")
    {
      Forward();
      delay(1000);
      Stop();
    }
    else if (data == "backwards")
    {
      Backward();
      delay(1000);
      Stop();
    }
    else if (data == "turn left")
    {
      TurnLeft();
      delay(500);
      Stop();
    }
    else if (data == "turn right")
    {
      TurnRight();
      delay(500);
      Stop();
    }
    else if (data == "stop")
    {
      Stop();
    }
  }
  data = "";
}
