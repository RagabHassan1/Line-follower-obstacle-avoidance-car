#include <NewPing.h>  //liberrary for uss

// ***Motor driver pins****
#define ENA 9       //ENA connected to digital pin 9
#define ENB 3       //ENB connected to digital pin 3
#define MOTOR_A1 7  // MOTOR_A1 connected to digital pin 7
#define MOTOR_A2 6  // MOTOR_A2 connected to digital pin 6
#define MOTOR_B1 5  // MOTOR_B1 connected to digital pin 5
#define MOTOR_B2 4  // MOTOR_B2 connected to digital pin 4

//*** IR sensor pins****
#define RIGHT A5  // RIGHT sensor connected to analog pin A5
#define LEFT A0   // LEFT sensor connected to analog pin A0

//*** USS pins***
#define TRIG A2                           // TRIG PIN connected to analog pin A2
#define ECHO A3                           // ECHO PIN connected to analog pin A3
#define MAX_DISTANCE 200                  // Define Maximum Distance
NewPing sonar(TRIG, ECHO, MAX_DISTANCE);  //creating a constructor **sonar** for the USS

//Robot parameters
#define ir_Treg 35
#define forwardspeed 120
#define turn_speed 165

void setup() {
  pinMode(ENA, OUTPUT);  // initialize ENA pin as an output
  pinMode(ENB, OUTPUT);  // initialize ENB pin as an output

  pinMode(MOTOR_A1, OUTPUT);  // initialize MOTOR_A1 pin as an output
  pinMode(MOTOR_A2, OUTPUT);  // initialize MOTOR_A2 pin as an output

  pinMode(MOTOR_B1, OUTPUT);  // initialize MOTOR_B1 pin as an output
  pinMode(MOTOR_B2, OUTPUT);  // initialize MOTOR_B2 pin as an output

  pinMode(RIGHT, INPUT);  // initialize RIGHT pin as an input
  pinMode(LEFT, INPUT);   // initialize LEFT pin as an input
}

void loop() {
  delay(70);

  int distance = sonar.ping_cm();  //calculating the distance between the USS and the obstacle in cm

  if (distance == 0) {  // because if the sensor did not sense anything in its range it returns zero
    distance = 30;
  }
  //***Robot movments on the line
  if (distance <= 10) {                    // if there is anything away 10 cm in front of the robot
    avoid(750, 75, 120);  // turn around the obstacle
  }
  if (analogRead(RIGHT) <= ir_Treg && analogRead(LEFT) <= ir_Treg) {
    moveForward(forwardspeed);

  } else if (!analogRead(RIGHT) <= ir_Treg && analogRead(LEFT) <= ir_Treg) {
    turnLeft(turn_speed);

  } else if (analogRead(RIGHT) <= ir_Treg && !analogRead(LEFT) <= ir_Treg) {
    turnRight(turn_speed);

  } else if (!analogRead(RIGHT) <= ir_Treg && !analogRead(LEFT) <= ir_Treg) {
    Stop();
  }
}



// ***code Functions***
void Stop() {
  analogWrite(ENA, 0);  //set right motors speed
  analogWrite(ENB, 0);  //set left motors speed
}

void turnLeft(int speed) {
  analogWrite(ENA, speed);  //set right motors speed
  analogWrite(ENB, speed);  //set left motors speed

  //run right motors clockwise
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);

  //run left motors anti-clockwise
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, HIGH);
}
void turnRight(int speed) {
  analogWrite(ENA, speed);  //set right motors speed
  analogWrite(ENB, speed);  //set left motors speed

  //run right motors anti-clockwise
  digitalWrite(MOTOR_A1, HIGH);
  digitalWrite(MOTOR_A2, LOW);
  //run left motors clockwise
  digitalWrite(MOTOR_B1, HIGH);
  digitalWrite(MOTOR_B2, LOW);
}

void moveForward(int speed) {
  analogWrite(ENA, speed);  // set right motors speed
  analogWrite(ENB, speed);  // set left motors speed

  //run right motors clockwise
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);

  //run left motors clockwise
  digitalWrite(MOTOR_B1, HIGH);
  digitalWrite(MOTOR_B2, LOW);
}

void avoid(int delayTime, int Fspeed, int Tspeed) {

  //a function  that givs the robot the right movments to turn around any obstical
  Stop();
  delay(100);

  turnRight(Tspeed);
  delay(350 + delayTime);

  moveForward(Fspeed);
  delay(1000 + delayTime);

  turnLeft(Tspeed);
  delay(200 + delayTime);

  moveForward(Fspeed);
  delay(1700 + delayTime);

  turnLeft(Tspeed);
  delay(300 + delayTime);

  while(analogRead(RIGHT) <= ir_Treg || analogRead(LEFT) <= ir_Treg){
    moveForward(Fspeed);
    if(!analogRead(RIGHT) <= ir_Treg || !analogRead(LEFT) <= ir_Treg){
      break;
    }
  }
  moveForward(Fspeed);
  delay(400+delayTime);
}  
  /*moveForward(Fspeed);
  delay(400+delayTime);
  turnRight(100);
  delay(400+delayTime);*/
