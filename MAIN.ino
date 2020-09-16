#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>


LiquidCrystal_PCF8574 lcd(0x27);

unsigned long pretime;
unsigned long currtime;
unsigned long timePeriod;
boolean flag = true;
const int IRsensor = 4;

void setup(){
  Serial.begin(9600);
  pinMode(IRsensor, INPUT);
  pretime = micros();
  lcd.begin(16,2);//tft.init(INITR_GREENTAB);             
  lcd.print("Simple harmonic motion");
  lcd.setCursor(0,1);
  lcd.print("Physics");
  
}
void loop(){
  int IR = digitalRead(4);
  lcd.setBacklight(255);
  if (IR==0) // ถ้าเจอลูกตุ้ม
  {
    if (flag == true) //ถ้าสัญลักษณ์ไม่ซ้ำ
    {
    lcd.clear();

    currtime = micros();
    timePeriod = currtime-pretime;
    pretime = currtime;
    flag = !flag;

   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   double convert  = timePeriod/1000;

   lcd.setCursor(0,0);
   double T = convert/1000;
   const double pie = 3.141;
   const double g = 9.81;
   double L = ((pow(T,2)*g)/(4*(pow(pie,2))))*100;


   lcd.print("T = ");
   lcd.print(T);
   lcd.print(" s");
   lcd.setCursor(0,1);
   lcd.print("l = ");
   lcd.print(L);
   lcd.print(" m");
  //////////////////////////////////////////////////////////////////////////////////// T = XX ms /////////////////////////////
  
   
    //Serial.println(timePeriod/1000);
    Serial.println(L);
    delay(100);
    
    }
    else{ //ถ้าซ้ำ
      flag = !flag;
      delay(100);
    }
  }
}
