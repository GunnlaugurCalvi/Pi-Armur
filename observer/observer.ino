/*
         author:
Doddi
*/

#include <Servo.h>

//Define pin numbers 

//LA's og skynjarar
const int LA1_forwards = 3;
const int LA1_backwards = 2;//assign relay INx pin to arduino pin
const int LA2_forwards = 5;
const int LA2_backwards = 4;
const int DC_haegri = 7;
const int DC_vinstri = 6;
const int Servo_Pin = 8; 
const int trigger_1 = 22;//face left
const int trigger_2 = 24;//face front
const int trigger_3 = 26;//face right
const int trigger_4 = 28;//left
const int trigger_5 = 30;//right
const int trigger_6 = 32;//bottom
const int echo_1 = 23;//face left
const int echo_2 = 25;//face front
const int echo_3 = 27;//face right
const int echo_4 = 29;//left
const int echo_5 = 31;//right
const int echo_6 = 33;//bottom
const int feedback_1 = A0; //potentiometer from LA1
const int feedback_2 = A1; //potentiometer from LA2

// defines variables
long duration1;
long duration2;
long duration3;
long duration4;
long duration5;
long duration6;
int distance_1;
int distance_2;
int distance_3;
int distance_4;
int distance_5;
int distance_6;
char value;
int val[3];
int len;
int direc;

int MIN_DISTANCE = 20;

//test
int tala1;
int tala2;
int looper = 0;


int bottomSensor() {
  // Clears the trigger_1
  digitalWrite(trigger_1, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_1, LOW);
  
  // Reads the echo_1, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echo_1, HIGH);
  
  // Calculating the distance
  distance_1= duration1*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.println(distance_1);

  return distance_1;
}

int frontSensorCenter () {
  // Clears the trigger_2
  digitalWrite(trigger_2, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_2, LOW);
  
  // Reads the echo_1, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echo_2, HIGH);
  
  // Calculating the distance
  distance_2= duration2*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.println(distance_2);

  return distance_2;
}


int sideSensorLeft() {
  // Clears the trigger_3
  digitalWrite(trigger_3, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_3, LOW);
  
  // Reads the echo_1, returns the sound wave travel time in microseconds
  duration3 = pulseIn(echo_3, HIGH);
  
  // Calculating the distance
  distance_3= duration3*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.println(distance_3);

  return distance_3;
}

int frontSensorLeft() {
  // Clears the trigger_4
  digitalWrite(trigger_4, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_4, LOW);
  
  // Reads the echo_1, returns the sound wave travel time in microseconds
  duration4 = pulseIn(echo_4, HIGH);
  
  // Calculating the distance
  distance_4= duration4*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.println(distance_4);

  return distance_4;
}

int frontSensorRight() {
  // Clears the trigger_5
  digitalWrite(trigger_5, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_5, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_5, LOW);
  
  // Reads the echo_1, returns the sound wave travel time in microseconds
  duration5 = pulseIn(echo_5, HIGH);
  
  // Calculating the distance
  distance_5= duration5*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.println(distance_5);

  return distance_5;
}

int sideSensorRight() {
  // Clears the trigger_6
  digitalWrite(trigger_6, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_6, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_6, LOW);
  
  // Reads the echo_1, returns the sound wave travel time in microseconds
  duration6 = pulseIn(echo_6, HIGH);
  
  // Calculating the distance
  distance_6= duration6*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.println(distance_6);

  return distance_6;
}

Servo myservo;
int servo_degree = 50; //Max degree 75, min degree 0

void ServoUp() {
  int val = servo_degree - 2;
  myservo.write(val);
  servo_degree = val;
}

void ServoDown() {
  int val = servo_degree + 2;
  myservo.write(val);
  servo_degree = val;
}
void setup()
{
  //start serial communication at Baud rate of 9600
  Serial.begin(9600);
  myservo.attach(Servo_Pin);
  myservo.write(50);
  pinMode(LA1_forwards, OUTPUT);//set relay as an output
  pinMode(LA1_backwards, OUTPUT);//set relay as an output
  pinMode(LA2_forwards, OUTPUT);//set relay as an output
  pinMode(LA2_backwards, OUTPUT);//set relay as an output
  pinMode(DC_haegri, OUTPUT);//set relay as an output
  pinMode(DC_vinstri, OUTPUT);//set relay as an output
  pinMode(trigger_1, OUTPUT);//setja trigger sem output
  pinMode(trigger_2, OUTPUT);//setja trigger sem output
  pinMode(trigger_3, OUTPUT);//setja trigger sem output
  pinMode(trigger_4, OUTPUT);//setja trigger sem output
  pinMode(trigger_5, OUTPUT);//setja trigger sem output
  pinMode(trigger_6, OUTPUT);//setja trigger sem output
  pinMode(echo_1, INPUT);//setja echo sem input
  pinMode(echo_2, INPUT);//setja echo sem input
  pinMode(echo_3, INPUT);//setja echo sem input
  pinMode(echo_4, INPUT);//setja echo sem input
  pinMode(echo_5, INPUT);//setja echo sem input
  pinMode(echo_6, INPUT);//setja echo sem input
  pinMode(feedback_1, INPUT);//feedback from actuator1
  pinMode(feedback_2, INPUT);//feedback from actuator2
  
  digitalWrite(LA1_forwards, HIGH);
  digitalWrite(LA1_backwards, HIGH);
  digitalWrite(LA2_forwards, HIGH);
  digitalWrite(LA2_backwards, HIGH);
  digitalWrite(DC_haegri, HIGH);
  digitalWrite(DC_vinstri, HIGH);
}

void base(){
  
//koma LA1 aftast
    digitalWrite(LA1_forwards, LOW);
    digitalWrite(LA1_backwards, HIGH);
//koma LA2 fremst
    digitalWrite(LA2_forwards, HIGH);
    digitalWrite(LA2_backwards, LOW);
// NO TURN
    digitalWrite(DC_haegri, HIGH);
    digitalWrite(DC_vinstri, HIGH);
// LEVEL FACE
    if (servo_degree >= 55){
        ServoUp();
      }
    if (servo_degree <= 50){
        ServoDown();
      }
}

  void backLA1(){
  
    digitalWrite(LA1_forwards, LOW);

    digitalWrite(LA1_backwards, HIGH);
  }


  void forwardLA1(){
    digitalWrite(LA1_forwards, HIGH);

    digitalWrite(LA1_backwards, LOW);

  }

  void stayLA1(){
    digitalWrite(LA2_forwards, HIGH);
    digitalWrite(LA2_backwards, HIGH);
    
  }

  void forwardLA2(){
    digitalWrite(LA2_forwards, HIGH);

    digitalWrite(LA2_backwards, LOW);

  }

  void backLA2(){
    digitalWrite(LA2_forwards, LOW);

    digitalWrite(LA2_backwards, HIGH);
    
  }

  void stayLA2(){
    digitalWrite(LA2_forwards, HIGH);
    digitalWrite(LA2_backwards, HIGH);
    
  }

  void DChaegri(){
      digitalWrite(DC_haegri, HIGH);
      digitalWrite(DC_vinstri, LOW);
    
  }

  void DCvinstri(){
      digitalWrite(DC_haegri, LOW);
      digitalWrite(DC_vinstri, HIGH);
    
  }

  void DCstay(){
      digitalWrite(DC_haegri, HIGH);
      digitalWrite(DC_vinstri, HIGH);
    
  }

  bool distanceToSmall() {
    return MIN_DISTANCE > distance_1;
  }


void execute()
{
  int no;
  int i = 0;
  //convert ASCII value from serial buffer into int
  no = value - '0';
  //Serial.println(no);
  /*
    """
    Direction control Index:

    '<' , '>' are the frame check bits for serial communication*/

  tala1 = 40; //feedback_1/12;
  tala2 = 70;//feedback_2/10;
  if(feedback_1 >= 930 && feedback_2 >= 800)
  {
    base();
  }
  //calculate distances
  if (bottomSensor() < MIN_DISTANCE)
  {
    digitalWrite(LA1_forwards, LOW);
    digitalWrite(LA1_backwards, HIGH);
  }
  else if(sideSensorLeft() < MIN_DISTANCE) {
    digitalWrite(LA1_forwards, LOW);
    digitalWrite(LA1_backwards, HIGH); 
  }
  else if(frontSensorLeft() < MIN_DISTANCE) {
    digitalWrite(LA1_forwards, LOW);
    digitalWrite(LA1_backwards, HIGH); 
  }
  
 /* else if(sideSensorRight() < MIN_DISTANCE) {
    digitalWrite(LA1_forwards, LOW);
    digitalWrite(LA1_backwards, HIGH); 
  }
  else if(frontSensorRight() < MIN_DISTANCE) {
    digitalWrite(LA1_forwards, LOW);
    digitalWrite(LA1_backwards, HIGH); 
  }
  else if(frontSensorCenter() < MIN_DISTANCE) {
    digitalWrite(LA1_forwards, LOW);
    digitalWrite(LA1_backwards, HIGH); 
  }*/
  else
  {  
    switch (value)
    {
      /*stay*/
      case 'a':
        digitalWrite(LA1_forwards, HIGH);
        digitalWrite(LA1_backwards, HIGH);
        digitalWrite(LA2_forwards, HIGH);
        digitalWrite(LA2_backwards, HIGH);
        digitalWrite(DC_haegri, HIGH);
        digitalWrite(DC_vinstri, HIGH);
        break;
      /*forward*/
       case 'b':
        forwardLA1();
        backLA2();
        DCstay();
        break;
      /*back*/
       case 'c':
        backLA1();
        stayLA2();
        DCstay();
        break;
      /*up*/ 
       case 'd':
        stayLA2();//var backLA2
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoUp();
        }
        stayLA1();
        DCstay();
        break;
      /*left-up*/
       case 'e':
        //snua DC motor left
        DCvinstri();
        backLA2();
        stayLA1();
        break;
      /*left*/ 
       case 'f':
        //snua DC motor left
        DCvinstri();
        stayLA1();
        stayLA2();
        break;
      /*left-down*/
       case 'g':
        //snua DC motor left
        DCvinstri();
        forwardLA2();//BREYTING FORWARD A AD VERA HER
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoDown();
        }
        stayLA1();
        break;
      /*down*/
       case 'h':
        stayLA2();//BREYTING FORWARD A AD VERA HER
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoDown();
        }
        stayLA1();
        DCstay();
        break;
      /*right-down*/
       case 'i':
        //snua DC motor right
        DChaegri();
        forwardLA2();
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoDown();
        }
        stayLA1();
        break;
      /*right*/
       case 'j':
        //snua DC motor right
        DChaegri();
        stayLA1();
        stayLA2();
        break;
      /*right-up*/
       case 'k':
        //snua DC motor right
        DChaegri();
        backLA2();
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoUp();
        }
        stayLA1();
        break;
      /*back-up*/
       case 'l':
        backLA1();
        backLA2();
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoUp();
        }
        DCstay();
        break;
      /*back-left-up*/
       case 'm':
        backLA1();
        backLA2();
        //snua DC motor left
        DCvinstri();
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoUp();
        }
        break;
      /*back-left*/
       case 'n':
        backLA1();
        //snua DC motor left
        DCvinstri();
        stayLA2();
        break;
      /*back-left-down*/
       case 'o':
        backLA1();
        forwardLA2();
        //snua DC motor left
        DCvinstri();
        break;
      /*back-down*/ 
       case 'p':
        backLA1();
        forwardLA2();
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoDown();
        }
        DCstay();
        break;
      /*back-right-down*/
       case 'q':
        backLA1();
        forwardLA2();
        //snua DC motor right
        DChaegri();
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoDown();
        }
        break;
      /*back-right*/ 
       case 'r':
        backLA1();
        //snua DC motor right
        DChaegri();
        stayLA2();
        break;
      /*back-right-up*/
       case 's':
        backLA1();
        backLA2();
        //snua DC motor right
        DChaegri();
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoUp();
        }
        break;
      /*forward-up*/
       case 't':
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoUp();
        }
        forwardLA1();
        backLA2();
        DCstay();
        break;
      /*forward-left-up*/
       case 'u':
        forwardLA1();
        backLA2();
        //snua DC motor left
        DCvinstri();
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoUp();
        }
        break;
      /*forward-left*/
       case 'v':
        forwardLA1();
        //snua DC motor left
        DCvinstri();
        stayLA2();
        break;
      /*forward-left-down*/
       case 'w':
        forwardLA1();
        forwardLA2();
        //snua DC motor left
        DCvinstri();
        break;
      /*forward-down*/
       case 'x':
        forwardLA1();
        forwardLA2();
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoDown();
        }
        DCstay();
        break;
      /*forward-right-down*/
       case 'y':
        forwardLA1();
        forwardLA2();
        //snua DC motor right
        DChaegri();
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoDown();
        }
        break;
      /*forward-right*/
       case 'z':
        forwardLA1();
        //snua DC motor right
        DChaegri();
        stayLA2();
        break;
      /*forward-right-up*/
       case 'A':
        forwardLA1();
        backLA2();
        //snua DC motor right
        DChaegri();
        if (servo_degree >= tala1 && servo_degree <= tala2)
        {
          ServoUp();
        }
        break;
      /*BASE*/
       case 'B':
        base();
        break;
      }
  }
}
 
void loop()
{
  if (Serial.available())
  {
    //Check for frame control bits
    char ch = Serial.read();
    if (ch == '<')
    {
      len = 0;
    }
    else if (ch == '>')
    {
      execute();
      //Serial.println(value);
      len = 1;
    }
    else if (len == 0)
      value = ch;
  }
}
