/* To use the program correctly, check the readme.md file first.
 * 
 * Do not put anything on the scale plate until you get a prompt. (Because the tare weight need to be calculate before using the scale)
 * Replace the calibration factor value with the one you've got from the calibration step.
 * Upload the file and open the Serial Monitor
 * Wait until it prompt to start weighing.
 * Then, you can test with various objects
 */

#include<HX711.h>

//pin assignment form HX711 ADC Amplifier module
#define Data 5
#define SCK 6

long calibration_factor = 41; //calibration factor to be adjusted later according to the get units result and is a parameter of set_scale() function
                              //The value is recieved from calibration step (replace with the value you've got)

//Creating HX711 scale object
HX711 scale;

void setup() {
  Serial.begin(9600); //baud rate
  Serial.println("Initializing Scale");

  scale.begin(Data, SCK); //Initialize the scale object with pin assignment

  //Initialize Calibration
  scale.set_scale(calibration_factor);
  scale.tare(); //reset the scale to 0
  
  //Feedback to start weighing
  Serial.println("Start Weighting");
}

void loop() {
  //Printing Result
  double weight = scale.get_units(20);  //get result weight

  Serial.print("Weight: ");

  //results more than 1000g will be shown as kg
  if (weight > 1000) {
    Serial.print(weight / 1000 , 2);
    Serial.println(" kg");
  }

  //Removing minus values
  else if (weight > 0) {
    Serial.print(weight , 2);
    Serial.println(" g");
  }
  else {
    Serial.print(0);
    Serial.println(" g");
  }

  //Put the HX711 in sleep mode for a while
  scale.power_down();
  delay(5000);
  scale.power_up();
}
