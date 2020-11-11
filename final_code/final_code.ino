/* Everyone can use this program freely.
 * To use the program correctly, check the readme.md file first.
 * 
 * After testing in the Serial Monitor, I made the scale to output the weight value on LCD screen.
 * Put no weight on the scale.
 * Replace the calibration factor value with the you've got in calibration step
 * Upload this file and you can start use your Weighing Scale...
 */

#include<HX711.h>

#include<LiquidCrystal.h> //Include LCD library

//pin assignment for LCD module
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;

//Creating LCD object named lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//pin assignment for HX711 ADC Amplifier module
#define Data 5
#define SCK 6

long calibration_factor = 42.5; //calibration factor to be adjusted later according to the get units result and is a parameter of set_scale() function

//Creating HX711 scale object
HX711 scale;

void setup() {
  lcd.begin(16, 2); // LCD set up (16 columns x 2 rows)

  scale.begin(Data, SCK); //Initialize the scale object with pin assignment

  //Initialize Calibration

  lcd.print("Calibrating...");
  scale.set_scale(calibration_factor);
  scale.tare(); //reset the scale to 0

  //Feedback to start weighing
  lcd.clear();
  lcd.print("Ready...");
}

void loop() {
  //Printing Result
  double weight = scale.get_units(20);  //get result weight

  if (weight >= 1000) // for kg
    printing(weight / 1000, 0);
  else if (weight > 5)  //for g
    printing(weight, 1);
  else            //around zero and minus value error catching
    printing(0, 2);

  //Put the HX711 in sleep mode for a while
  scale.power_down();
  delay(1500);
  scale.power_up();
}

void printing(double weight, int flag) {
  if (flag == 0) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Weighing Scale");
    lcd.setCursor(0, 1);
    lcd.print(weight);
    lcd.setCursor(6, 1);
    lcd.print("kg");
  }
  else if (flag == 1) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Weighing Scale");
    lcd.setCursor(0, 1);
    lcd.print(weight);
    lcd.setCursor(7, 1);
    lcd.print("g");
  }
  else {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Weighing Scale");
    lcd.setCursor(0, 1);
    lcd.print(0);
    lcd.setCursor(7, 1);
    lcd.print("g");
  }
}
