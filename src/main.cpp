#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    //init lcd
int buttonR = 6, buttonL = 7;         // button input
int readingR, readingL;               // the current reading from the input pin
int count = 0;

long time = 0;
long debounce = 200;


         //init parameters
int clk, mem, temp, load, cont;
int curr;
String temps, clks, mems, loads, conts;

int changeScreen(int stage);
void serialParse(int check);
void lcdPrint(int num);
void serialToString(int param, String out);


void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(buttonR, INPUT), pinMode(buttonL, INPUT);         //init button pins
  count = 0;
}

void loop()
{
  readingR = digitalRead(buttonR);
  readingL = digitalRead(buttonL);

  while (Serial.available()) {
    curr = Serial.parseInt();
    if (curr>0)
      clk = curr;
    
    curr = Serial.parseInt();
    if (curr>0)
      mem = curr;
      
    curr = Serial.parseInt();
    if (curr>0)
      temp = curr;
      
    curr = Serial.parseInt();
    if (curr>0)
      load = curr;
      
    curr = Serial.parseInt();
    if (curr>0)
      cont = curr;

    Serial.println(clk);
    
  }

    serialToString(clk, clks);
    serialToString(mem, mems);
    serialToString(temp, temps);
    serialToString(load, loads);
    serialToString(cont, conts);
    
    count = changeScreen(count);                    //updates count and prints correct stage
  
}

int changeScreen(int stage){                        //keeps track of current stage, + or - when button is pressed
  int check = 0;              //flag if button is pressed, only print to lcd when pressed
  if (readingR == LOW && millis() - time > debounce) {        //screen fwd when right button pressed
    stage++;
    if (stage == 5)
      stage = 0;
    time = millis();    
    check = 1;
  }

  if (readingL == LOW && millis() - time > debounce) {      //screen back when left button pressed
    stage--;
    if (stage == -1)
      stage = 4;
    time = millis();    
    check = 1;
  }
  if (check == 1)
    lcdPrint(stage);
  check = 0;
  return stage;
}

void lcdPrint(int num){                 //prints correct stage to LCD
  lcd.clear();
  switch(num){
    case 0: 

      lcd.print("GPU CLOCK "), lcd.print(clk), lcd.print("M");
      break;
    case 1:

      lcd.print("GPU MEMO "), lcd.print(mem), lcd.print("M");
      break;
    case 2:

      lcd.print("GPU TEMP "), lcd.print(temp), lcd.print("C");
      break;
    case 3:

      lcd.print("GPU LOAD "), lcd.print(load), lcd.print("%");
      break;
    case 4:

      lcd.print("GPU FANS "), lcd.print(cont), lcd.print("%");
      break;
    }
}

void serialToString(int param, String out){
  if (param>0)
    out = String(param);
}

void serialParse(int check){
  int check_temp;
  check_temp = Serial.parseInt();
  if (check_temp > 0)
    check = check_temp;
}
