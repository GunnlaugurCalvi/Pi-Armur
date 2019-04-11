/*
         @authors:
Yash Chandak    Ankit Dhall
*/
//Define pin numbers

//LA's og skynjarar
const int LA1_forwards = 6;
const int LA1_backwards = 7;//assign relay INx pin to arduino pin
const int LA2_forwards = 4;
const int LA2_backwards = 5;
const int trigger_vinstri = 13;
const int echo_vinstri = 11;
const int echo_haegri = 12;
const int trigger_haegri = 10;
const int feedback_1 = A0; //potentiometer from LA1
const int feedback_2 = A1; //potentiometer from LA2

// defines variables
long duration;
long duration_2; // hægri tímataka
int distance_haegri;
int distance_vinstri;
char value;
int val[3];
int len;
int direc;


void setup()
{
  //start serial communication at Baud rate of 9600
  Serial.begin(9600);
pinMode(LA1_forwards, OUTPUT);//set relay as an output
pinMode(LA1_backwards, OUTPUT);//set relay as an output
pinMode(LA2_forwards, OUTPUT);//set relay as an output
pinMode(LA2_backwards, OUTPUT);//set relay as an output
pinMode(trigger_vinstri, OUTPUT);//setja trigger sem output
pinMode(trigger_haegri, OUTPUT);//setja trigger sem output
pinMode(echo_vinstri, INPUT);//setja echo sem input
pinMode(echo_haegri, INPUT);//setja echo sem input
pinMode(feedback_1, INPUT);//feedback from actuator1
pinMode(feedback_2, INPUT);//feedback from actuator2
}

void execute()
{
  int no;
  int i = 0;

  //convert ASCII value from serial buffer into int
  no = value - '0';
  //Serial.println(no);

  int a, b, c, d;

  /*
    """
    Direction control Index:

    '<' , '>' are the frame check bits for serial communication*/

  switch (no)
  {
    /*Something Weird */
    case 0:
      a = 0; b = 100; c = 100; d = 0;
      break;
      
    /*Back*/
    case 2:
      a = 0; b = 255; c = 0; d = 255;
      break;

    /*Left*/
    case 4:
      a = 255; b = 0; c = 0; d = 0;
      break;
      
    /*Still*/
    case 5:
      a = 0; b = 0; c = 0; d = 0;
      break;
      
    /*Right*/
    case 6:
      a = 0; b = 0; c = 255; d = 0;
      break;
      
    /*Forward*/
    case 8:
      a = 150; b = 0; c = 150; d = 0;
      break;
  }
 
  analogWrite(m1f, a);
  analogWrite(m1r, b);
  analogWrite(m2f, c);
  analogWrite(m2r, d);
  //delay(255);
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
