#include <NewPing.h>

int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

int led = 23; // LED

//Ultrasonic sensor
#define trigPin 14
#define echoPin 15
#define MAX_DISTANCE 200

NewPing sonic(trigPin, echoPin, MAX_DISTANCE);

/* Sensors */
int LS = A2; // left sensor
int RS = A3; // right sensor

void setup(){
  Serial.begin(115200);
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);

  pinMode(LS, INPUT);
  pinMode(RS, INPUT);

  startup();

  delay(1000);
}

void loop() {
  int lineLeft = analogRead(LS);
  int lineRight = analogRead(RS);

  if(lineLeft < 900 && lineRight > 930) {
    goForward(255);
  }
  else if(lineLeft > 930 && lineRight < 900) {
    goForward(255);
  }
  else {
  }

  //ultrasonic
	int distance = sonic.ping_cm();
	Serial.print("ping:");
	Serial.print (distance);
	Serial.print ("cm");
  Serial.println();

  startup();

  //search for the other sumobot
	if( distance <= 50 && distance > 5) {
		goForward(255);
	  delay(100);
	}
	//attack by spin
	else if(distance == 0){
		turnLeft(245, 245);
	}

/*  delay(1000); //go for 1 second
  stop(); //stop
  delay(250); //hold for 250ms until move again

  move(1, 128, 0); //motor 1, half speed, right
  move(2, 128, 0); //motor 2, half speed, right

  delay(1000);
  stop();
  delay(250);*/
}

void startup() {
  digitalWrite(STBY, HIGH);
}


void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void turnLeft(int speed1, int speed2) {
  // move(1, speed, 0);
  move(1, speed1, 0);
  move(2, speed2, 1);
}

void turnRight(int speed1, int speed2) {
  move(1, speed2, 1);
  move(2, speed1, 0);
}

void goForward(int speed) {
  move(1, speed, 1);
  move(2, speed, 1);
}

void goReverse(int speed) {
  move(1, speed, 0);
  move(2, speed, 0);
}

void turnAround() {
  turnLeft(255, 255);
  delay(1370);
}

void stop(){
//enable standby
  digitalWrite(STBY, LOW);
}
