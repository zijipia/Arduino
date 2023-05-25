#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27,16,2); //SCL A5 SDA A4
// pin 2 td1, pin 3 td2, pin 4 sw
long N = 0;
long time;
const float pi = 3.14;
const float R = 4;
void CHECK(){
if(digitalRead(3) == 0){
N++; }
else  {
N--;  }

}
void setup() {
lcd.init();
lcd.backlight();
pinMode(2, INPUT);
pinMode(3, INPUT);
pinMode(4, INPUT);
attachInterrupt(0,CHECK, FALLING);
}
void loop() {

if((millis()-time) > 100){
lcd.clear();
time = millis();  }  

if(digitalRead(4) == 0){
N = 0;
}

lcd.setCursor(0,0);
lcd.print("S = ");
lcd.print((2*pi*R*N)/20);
lcd.print(" CM");
}