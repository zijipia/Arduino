#define GREEN_PIN 9
#define RED_PIN 10
#define BLUE_PIN 11
#define LED_PIN 8
int DELAY_TIME = 5;
 
void setup() {
	pinMode(RED_PIN, OUTPUT);
	pinMode(GREEN_PIN, OUTPUT);
	pinMode(BLUE_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), DELAYY, FALLING);
}
 
void loop(){
	showSpectrum();
}

void DELAYY() {
  DELAY_TIME = DELAY_TIME < 50 ? (DELAY_TIME + 5) :  0 ;
  digitalWrite(LED_PIN, HIGH);
  delay(2000);
  digitalWrite(LED_PIN, LOW);
}

void showSpectrum()
{
	for (int i = 0; i < 768; i++)
	{
		showRGB(i);  // Call RGBspectrum() with our new x
		delay(DELAY_TIME);   // Delay
	}
}

void showRGB(int color)
{
	int redPWM;
	int greenPWM;
	int bluePWM;
 
	if (color <= 255)          // phân vùng 1
	{
		redPWM = 255 - color;    // red đi từ sáng về tắt
		greenPWM = color;        // green đi từ tắt thành sáng
		bluePWM = 0;             // blue luôn tắt
	}
	else if (color <= 511)     // phân vùng 2
	{
		redPWM = 0;                     // đỏ luôn tắt
		greenPWM = 255 - (color - 256); // green đi từ sáng về tắt
		bluePWM = (color - 256);        // blue đi từ tắt thành sáng
	}
	else // color >= 512       // phân vùng 3
	{
		redPWM = (color - 512);         // red tắt rồi lại sáng
		greenPWM = 0;                   // green luôn tắt nhé
		bluePWM = 255 - (color - 512);  // blue sáng rồi lại tắt
	}
	analogWrite(RED_PIN, redPWM);
	analogWrite(BLUE_PIN, bluePWM);
	analogWrite(GREEN_PIN, greenPWM);
}