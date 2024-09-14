#include<Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial gsm (2,3);

float calibration_value = 21.34;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define trigPin 10
#define echoPin 9

long duration;
int distance ;
int buzzer=13;
Servo myservo;

int Distance()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
  
}

void setup()
{
 pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  delay(1000);
   Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("AGGRICULTURE");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM IS ON ");
    lcd.print("");
    delay(3000);
  lcd.clear();
  pinMode(trigPin , OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  myservo.attach(12);
  gsm.begin (9600);
  gsm.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println((char)26);
  delay(500);
  
}

void loop()
{int i ;
  
 
 for (i=0; i<=180; i++)
 {
  myservo.write(i);
    delay(20);
  Distance();
  {int value = analogRead(A0);
  Serial.println(value);
  if (value > 950) {
    digitalWrite(8, LOW);
{
  gsm.println("AT+CMGF=1");
  delay(500);
  gsm.println("AT+CMGS=\"+919599403563\"\r"); // replace your phone number
  delay(500);
  gsm.println ("WATER PUMP IS ON");
  delay(100);
  gsm.println((char)26);
  delay(500);
  Serial.println ("Done");
  gsm.println("AT+CMGF=1");
  delay(500);
}    
    
  } else {
    digitalWrite(8, HIGH);
    
  }
 
  if (value < 300) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : HIGH");
  } else if (value > 300 && value < 950) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : HIGH ");
  } else if (value > 950) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : LOW ");
  }
  }
{
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A1);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6;
 float ph_act = -5.70 * volt + calibration_value;
 lcd.setCursor(0, 0);
 lcd.print("pH:");
 lcd.setCursor(4, 0);
 lcd.print(ph_act);
 delay(100);
}  
 
  if (distance <= 5){
  digitalWrite(buzzer, HIGH);
{
  gsm.println("AT+CMGF=1");
  delay(500);
  gsm.println("AT+CMGS=\"+919599403563\"\r"); // replace your phone number
  delay(500);
  gsm.println ("enemy");
  delay(100);
  gsm.println((char)26);
  delay(500);
  Serial.println ("Done");
  gsm.println("AT+CMGF=1");
  delay(500);
}  
  
 delay(20);
}
else{
  digitalWrite(buzzer, LOW);
  }

  lcd.setCursor(11,0);  //Set cursor to first column of second row
  lcd.print("                "); //Print blanks to clear the row
  lcd.setCursor(11,0);   //Set Cursor again to first column of second row
  lcd.print(distance); //Print measured distance
  lcd.print("cm");  //Print your units.
  delay(20);
 }
 for(i=180; i>=0; i--)
 {
  myservo.write(i);
   delay(20);
   Distance();
   Distance();
   {int value = analogRead(A0);
  Serial.println(value);
  if (value > 950) {
    digitalWrite(8, LOW);

  gsm.println("AT+CMGF=1");
  delay(500);
  gsm.println("AT+CMGS=\"+919599403563\"\r"); // replace your phone number
  delay(500);
  gsm.println ("WATER PUMP IS ON");
  delay(100);
  gsm.println((char)26);
  delay(500);
  Serial.println ("Done");
  gsm.println("AT+CMGF=1");
  delay(500);
   
    
  } else {
    digitalWrite(8, HIGH);
    
  }
 
  if (value < 300) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : HIGH");
  } else if (value > 300 && value < 950) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : HIGH ");
  } else if (value > 950) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : LOW ");
  }
  }
{
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A1);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6;
 float ph_act = -5.70 * volt + calibration_value;
 lcd.setCursor(0, 0);
 lcd.print("pH:");
 lcd.setCursor(4, 0);
 lcd.print(ph_act);
 delay(100);
}  
  if (distance <= 5){
  digitalWrite(buzzer, HIGH);
  
  gsm.println("AT+CMGF=1");
  delay(500);
  gsm.println("AT+CMGS=\"+919599403563\"\r"); // replace your phone number
  delay(500);
  gsm.println ("enemy");
  delay(100);
  gsm.println((char)26);
  delay(500);
  Serial.println ("Done");
  gsm.println("AT+CMGF=1");
  delay(500);

 delay(20);
 
}
else{
  digitalWrite(buzzer, LOW);
  }

  
  lcd.setCursor(11,0);  //Set cursor to first column of second row
  lcd.print("                "); //Print blanks to clear the row
  lcd.setCursor(11,0);   //Set Cursor again to first column of second row
  lcd.print(distance); //Print measured distance
  lcd.print("cm");  //Print your units.
  delay(20);
  }  
  
 


}