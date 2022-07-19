#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

const int numReadings = 10; // The number of samples to average over

int readings[numReadings];      // an array of readings, of the desired dimension
int readIndex = 0;              // the index position in the array of readings, 0 initially
float totalSignal = 0;                  // the running total (summation), 0 initially
float averageSignal = 0;                // the average (total / numReadings), 0 initially
int i;

void setup(void)
{
  
  // Printing setup messages
  Serial.begin(115200);
  Serial.println("Hello!");
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  
}

void loop(void)
{
  int16_t adc0, adc1, adc2, adc3;
  float volts0, volts1, volts2, volts3;

  totalSignal = 0;
  
// Reading in the analog signals
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

// Converting the analog signals to voltage values
  volts0 = ads.computeVolts(adc0);
  volts1 = ads.computeVolts(adc1);
  volts2 = ads.computeVolts(adc2);
  volts3 = ads.computeVolts(adc3);

// Now to average these voltage values to smooth the signal received

  for(i=0; i<numReadings; i++){
    readings[i+1] = readings[i];
  }

  readings[0] = volts0;

  for(i=0; i<numReadings; i++){
    totalSignal = totalSignal + readings[i];
    Serial.print("Running total is: "), Serial.println(totalSignal);
  }
  
  // calculate the average:
  averageSignal = totalSignal / numReadings;
  
// Printing the values to the serial port (not smoothed/averaged)
  //Serial.println("-----------------------------------------------------------");
  //Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); 
  Serial.print("Volts0 value is: "), Serial.println(volts0);
  Serial.println("-----------------------------------------------------------");
  Serial.print("Averaged V0: "); Serial.println(averageSignal);
  delay(50);
}
