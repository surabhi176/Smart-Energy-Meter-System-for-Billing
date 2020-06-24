#include<LiquidCrystal.h>

 #include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);
int ledPin = 13; // choose the pin for the LED
int switchPin =7; // choose the input pin (for a pushbutton)
int val = 0; // variable for reading the pin status
int counter = 0;
int currentState = 0;
int previousState = 0;
int count=0;
float amount=0;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 60000;  //the value is a number of milliseconds
int icnt=0;
int fcnt;
int diff=0;
int temp=0;
int state=0;
int buttonPin=8;
void setup() {
pinMode(ledPin, OUTPUT); // declare LED as output
pinMode(switchPin, INPUT); // declare pushbutton as input
/*Serial.begin(9600);*/
lcd.begin(16,2);
lcd.clear();
startMillis = millis();//initial start time
mySerial.begin(9600);   // Setting the baud rate of GSM Module  
Serial.begin(9600);   //Initialise serial to communicate with GSM Modem
pinMode(buttonPin,INPUT);
}

void loop(){
val = digitalRead(switchPin); // read input value
if (val == HIGH) { // check if the input is HIGH (button released)
digitalWrite(ledPin, HIGH); // turn LED on
currentState = 1;
}
else {
digitalWrite(ledPin, LOW); // turn LED off
currentState = 0;
}
if(currentState != previousState){
if(currentState == 1){
counter = counter + 1;
Serial.println(diff);
/*if(counter==2)
{
  count=count+1;
  counter=0;
}*/
}
}
previousState = currentState;
delay(250);
currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
 if (currentMillis - startMillis>= period)  //test whether the period has elapsed
  {
fcnt=counter;
    diff=fcnt-icnt;
lcd.setCursor(0,0);// Sets the cursor to col 0 and row 0

temp=icnt;
icnt=fcnt;
startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state
getReading();
   sendTextMsg1();
   delay(10000);
int buttonVal=digitalRead(buttonPin);
  if (buttonVal==HIGH)
  {
    sendTextMsg();
    delay(500);
  }
   

  }
lcd.setCursor(0,0);// Sets the cursor to col 0 and row 0
lcd.print("U ");// Prints Sensor Val: to LCD
lcd.print(fcnt);
lcd.print(" ");
lcd.print(temp);
lcd.print(" ");
lcd.print(diff);


lcd.setCursor(0,1);// Sets the cursor to col 1 and row 0
lcd.print("Amount=Rs");// Prints Sensor Val: to LCD
lcd.print(amount);// Prints value on Potpin1 to LCD

}
 float getReading()
 { 



if(diff <= 2)
  amount = (diff * 3.25);
if(( diff > 2 ) && ( diff <= 6))
   amount = ( diff * 4.70 );
if(( diff> 6 ) && (diff<= 10))
   amount = (diff * 6.25);
 if(diff> 10)
  amount = (diff * 7.40);

return  amount;

 }

void sendTextMsg1()
{
  mySerial.print("AT+CMGF=1\r");
  delay(100);
  mySerial.println("AT+CMGS=\"+911023456789\"");
  delay(100);
  mySerial.println("Units consumed is ");
mySerial.println(diff);
mySerial.println("and the corresponding bill amount is Rs.");//the content of the message
mySerial.println(amount);
  delay(100);
  mySerial.print((char)26);
  delay(100);
  mySerial.println();
  delay(500);  
}
void sendTextMsg()
{
  mySerial.print("AT+CMGF=1\r");
  delay(100);
  mySerial.println("AT+CMGS=\"+911023456789\"");
  delay(100);
  mySerial.print("You have suucessfully paid the bill with no dues");
  delay(100);
  mySerial.print((char)26);
  delay(100);
  mySerial.println();  
}

