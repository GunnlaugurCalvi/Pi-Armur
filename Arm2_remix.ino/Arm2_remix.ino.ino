/*
         @authors:
Yash Chandak    Ankit Dhall
*/
//Define pin numbers

//LA's og skynjarar
const int LA1_forwards = 7;
const int LA1_backwards = 6;//assign relay INx pin to arduino pin
const int LA2_forwards = 4;
const int LA2_backwards = 5;
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

void movement() {
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
  Serial.print("Distance_1: ");
  Serial.println(distance_1);
  
//**********************************************

  // Clears the trigger_2
  digitalWrite(trigger_2, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_2, LOW);
  
  // Reads the echo_2, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echo_2, HIGH);
  
  // Calculating the distance
  distance_2= duration2*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance_2: ");
  Serial.println(distance_2);
  
//**********************************************

  // Clears the trigger_3
  digitalWrite(trigger_3, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_3, LOW);
  
  // Reads the echo_3, returns the sound wave travel time in microseconds
  duration3 = pulseIn(echo_3, HIGH);
  
  // Calculating the distance
  distance_3= duration3*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance_3: ");
  Serial.println(distance_3);
  
//**********************************************

  // Clears the trigger_4
  digitalWrite(trigger_4, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_4, LOW);
  
  // Reads the echo_4, returns the sound wave travel time in microseconds
  duration4 = pulseIn(echo_4, HIGH);
  
  // Calculating the distance
  distance_4= duration4*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance_4: ");
  Serial.println(distance_4);
  
//**********************************************

  // Clears the trigger_5
  digitalWrite(trigger_5, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_5, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_5, LOW);
  
  // Reads the echo_5, returns the sound wave travel time in microseconds
  duration5 = pulseIn(echo_5, HIGH);
  
  // Calculating the distance
  distance_5= duration5*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance_5: ");
  Serial.println(distance_5);

//**********************************************

  // Clears the trigger_6
  digitalWrite(trigger_6, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_6, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_6, LOW);
  
  // Reads the echo_6, returns the sound wave travel time in microseconds
  duration6 = pulseIn(echo_6, HIGH);
  
  // Calculating the distance
  distance_6= duration6*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance_6: ");
  Serial.println(distance_6);
}

void setup()
{
  //start serial communication at Baud rate of 9600
  Serial.begin(9600);
pinMode(LA1_forwards, OUTPUT);//set relay as an output
pinMode(LA1_backwards, OUTPUT);//set relay as an output
pinMode(LA2_forwards, OUTPUT);//set relay as an output
pinMode(LA2_backwards, OUTPUT);//set relay as an output
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
}

void base(){
//koma LA1 aftast
  digitalWrite(LA1_forwards, LOW);
  
  digitalWrite(LA1_backwards, HIGH);
//koma LA2 fremst
  digitalWrite(LA2_forwards, HIGH);
  
  digitalWrite(LA2_backwards, LOW);
//timi til ad koma ser i base sidan
}

void backLA1(){
  
    digitalWrite(LA1_forwards, LOW);

    digitalWrite(LA1_backwards, HIGH);
  }


  void forwardLA1(){
    digitalWrite(LA1_forwards, HIGH);

    digitalWrite(LA1_backwards, LOW);

  }

  void forwardLA2(){
    digitalWrite(LA2_forwards, HIGH);

    digitalWrite(LA2_backwards, LOW);

  }

  void backLA2(){
    digitalWrite(LA2_forwards, LOW);

    digitalWrite(LA2_backwards, HIGH);
    
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

  switch (no)
  {
    /*Something Weird */
    case 0:
    digitalWrite(LA1_forwards, HIGH);
    digitalWrite(LA1_backwards, HIGH);
    digitalWrite(LA2_forwards, HIGH);
    digitalWrite(LA2_backwards, HIGH);
      break;
      
    /*stay*/
    case 1:
      digitalWrite(LA1_forwards, HIGH);
    digitalWrite(LA1_backwards, HIGH);
    digitalWrite(LA2_forwards, HIGH);
    digitalWrite(LA2_backwards, HIGH);
      break;
    /*forward*/
     case 2:
      forwardLA1();
      break;
    /*back*/
     case 3:
      backLA1();
      break;
    /*up*/ 
     case 4:
      backLA2();
      break;
    /*left-up*/
     case 5:
      //snua DC motor left
      backLA2();
      break;
    /*left*/ 
     case 6:
      //snua DC motor left
      break;
    /*left-down*/
     case 7:
      //snua DC motor left
      forwardLA2();
      break;
    /*down*/
     case 8:
      forwardLA2();
      break;
    /*right-down*/
     case 9:
      //snua DC motor right
      forwardLA2();
      break;
    /*right*/
     case 10:
      //snua DC motor right
      break;
    /*right-up*/
     case 11:
      //snua DC motor right
      backLA2();
      break;
    /*back-up*/
     case 12:
      backLA1();
      backLA2();
      break;
    /*back-left-up*/
     case 13:
      backLA1();
      backLA2();
      //snua DC motor left
      break;
    /*back-left*/
     case 14:
      backLA1();
      //snua DC motor left
      break;
    /*back-left-down*/
     case 15:
      backLA1();
      forwardLA2();
      //snua DC motor left
      break;
    /*back-down*/ 
     case 16:
      backLA1();
      forwardLA2();
      break;
    /*back-right-down*/
     case 17:
      backLA1();
      forwardLA2();
      //snua DC motor right
      break;
    /*back-right*/ 
     case 18:
      backLA1();
      //snua DC motor right
      break;
    /*back-right-up*/
     case 19:
      backLA1();
      backLA2();
      //snua DC motor right
      break;
    /*forward-up*/
     case 20:
      forwardLA1();
      backLA2();
      break;
    /*forward-left-up*/
     case 21:
      forwardLA1();
      backLA2();
      //snua DC motor left
      break;
    /*forward-left*/
     case 22:
      forwardLA1();
      //snua DC motor left
      break;
    /*forward-left-down*/
     case 23:
      forwardLA1();
      forwardLA2();
      //snua DC motor left
      break;
    /*forward-down*/
     case 24:
      forwardLA1();
      forwardLA2();
      break;
    /*forward-right-down*/
     case 25:
      forwardLA1();
      forwardLA2();
      //snua DC motor right
      break;
    /*forward-right*/
     case 26:
      forwardLA1();
      //snua DC motor right
      break;
    /*forward-right-up*/
     case 27:
      forwardLA1();
      backLA2();
      //snua DC motor right
      break;
    /*BASE*/
     case 28:
     // base();
      //delay(5000);
      digitalWrite(LA1_forwards, LOW);
      digitalWrite(LA1_backwards, HIGH);
      digitalWrite(LA2_forwards, HIGH);
      digitalWrite(LA2_backwards, LOW);
      break;

    
  }
 
 /* analogWrite(LA1_forwards, a);
  analogWrite(LA1_backwards, b);
  analogWrite(LA2_forwards, c);
  analogWrite(LA2_backwards, d);
  //delay(255);*/
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
