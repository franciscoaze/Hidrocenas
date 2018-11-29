uint8_t RED_LED = 6;
uint8_t GREEN_LED = 9;
uint8_t BLUE_LED = 10;

int brightness = 255;

int gBright = 0;
int rBright = 0;
int bBright = 0;

int fadeSpeed = 10;


void setup() {

//  ledcAttachPin(RED_LED, 1); // assign RGB led pins to channels
//  ledcAttachPin(GREEN_LED, 2);
//  ledcAttachPin(BLUE_LED, 3);
 

  TurnOn();
  delay(5000);
  TurnOff();
}

void TurnOn() { 
   for (int i = 0; i < 256; i++) {
       analogWrite(RED_LED, rBright);
       rBright +=1;
       delay(fadeSpeed);
   }
 
   for (int i = 0; i < 256; i++) {
       analogWrite(BLUE_LED, bBright);
       bBright += 1;
       delay(fadeSpeed);
   } 

   for (int i = 0; i < 256; i++) {
       analogWrite(GREEN_LED, gBright);
       gBright +=1;
       delay(fadeSpeed);
   } 
}

void TurnOff() {
   for (int i = 0; i < 256; i++) {
       analogWrite(GREEN_LED, brightness);
       analogWrite(RED_LED, brightness);
       analogWrite(BLUE_LED, brightness);
 
       brightness -= 1;
       delay(fadeSpeed);
   }
}


void loop() {
  // put your main code here, to run repeatedly:

}
