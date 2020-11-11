/* Everyone can use this program freely.
 * To use the program correctly, check the readme.md file first.
 * 
 * Before Calibrating, you need a known-weight object (may be your phone or something)
 * You can put a plate or something (2 or 3 is better) on the load cells to put things on it while wehghing (ok with any weight)
 * Then upload this file and open the Serial Monitor.
 * Wait for the prompt to start calibrating
 * Pass numbers (like 20 or +32 or -16) from the Serial Monitor to adjust the weight value (In my case I used gram unit. This is your choice)
 * After Calibrating with some known-weight object (if you have only one, it's also ok), you will finally get the suitable calibration factor for your load cells
 * Mark that calibration factor value for later uses.(Important)
 * Done!!!
 */

#include<HX711.h>

//pin assignment form HX711 ADC Amplifier module
#define Data 5
#define SCK 6

long calibration_factor = 45; //calibration factor to be adjusted later according to the get units result and is a parameter of set_scale() function

//Creating HX711 scale object
HX711 scale;

void setup() {
  Serial.begin(9600); //baud rate
  Serial.println("Initializing Scale");

  scale.begin(Data, SCK); //Initialize the scale object with pin assignment

  //Calibration Steps
  scale.set_scale();
  scale.tare(); //reset the scale to 0

  Serial.print("Tare weight: ");
  Serial.println(scale.read_average(20)); //Describing the tare weight

  Serial.println("Put a known weight on the scale");
  delay(5000);  //Wait 5 seconds to put known weight

  Serial.print("Get Units: ");
  Serial.println(scale.get_units(10), 2); //average of 10 reading minus tare weight divided scale prameter (not set yet)
}

void loop() {
  scale.set_scale(calibration_factor); //Setting calibration factor

  //Printing Result
  Serial.print("Get Units (gram): ");
  scale.get_units(20) > 0 ? Serial.print(scale.get_units(20), 2) : Serial.print(0.0);
  Serial.print("\t\tCalibration Factor: ");
  Serial.println(calibration_factor);

  //HX711 sleep mode
  scale.power_down();
  delay(800);
  scale.power_up();

  //Adjusting Calibration Factor
  if (Serial.available()) {
    int adj = Serial.parseInt(); //Integer reading from Serial Monitor for calibration factor adjustment
    calibration_factor += adj;
  }
  delay(200);
}
