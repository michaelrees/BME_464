/*********************
// BME 464, Lab 1
// Michael Rees, Rhea Chitalia, Ananya Zutshi, Karthika Rhaa


This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
#include <Time.h>  

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

// input pins
int Input_Pin  = A0;    // select the input pin for the input signal
int High_Pin   = A1;   // input from positive comparator 
int Low_Pin    = A2;   // input from negative comparator

// Input and output variables
float Input; //variable input goes
float Output; // variable output goes
float Display;
char  Binary[] = {'+', '0', '0', '0', '.', '0', '0', '0', '0', '0', '0', '0'};   // lefternmost character should be + or - to give sign
int   count_RHS;
int   count_LHS;
//char   Binary_RHS[] = {'0', '0', '0', '0', '0', '0', '0'};
int   LHS;
int   RHS;
//ouput pins
int Output_Pin = 3;    // PWM enabled output pin

// comparator outputs
boolean Too_High = LOW;  // tells whether the signal is over the acceptable 5V
boolean Too_Low  = LOW;  // tells whether the signal is under the acceptable -5V


void setup() {

  // define pins as input
  pinMode(Input_Pin, INPUT); 
  pinMode(High_Pin, INPUT);
  pinMode(Low_Pin, INPUT);
  
  // define pins as output
  pinMode(Output_Pin, OUTPUT);
  
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  int time = millis();
  lcd.setCursor(0,0);
  lcd.print("Binary V_in is..");
  time = millis() - time;
  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(WHITE);
  delay(1000);
  lcd.clear();  
}

uint8_t i=0;

///****** NOTE - due to inverting amp in pre hardware, values above 2.5 are NEGATIVE, values below 2.5 are POSITIVE *********
   // actually we arent doing that anymore...
void loop() {
    char Binary[] = {'+', '0', '0', '0', '.', '0', '0', '0', '0', '0', '0', '0'};
    // read in the input pins
      Input = analogRead(Input_Pin) * 0.00488;
   
     // convert the input value to the non-shifted/scaled value

    
      Too_High = LOW;//digitalRead(High_Pin);
      Too_Low  = LOW;//digitalRead(Low_Pin);
    
     // Display = (Input * 0.00488); //converts input from arbitrary arduino scale to the actual value, AND multiplies by 2 and subtracts 2.5 to undo our scaling factor and shift.   
      Display = (Input - 2.5) *(-2);
      LHS = Display;
      RHS = (Display - LHS) * 100;
    
     // ouput to pulse wave modulated output pin
     // NOTE: analogRead values go from 0 to 1023, analogWrite values from 0 to 255
    Output = analogRead(Input_Pin) * 0.25;   // corrects for difference in analogRead/Write resolutions
    
    analogWrite(Output_Pin, Output); // set input value into pwm output pin 
    
    // Check input/output via serial monitor

     Serial.println(Output);
     
    // Convert base 10 display value to binary
    /*
     for (int i = 4; i >= 1; i--){
        Serial.println(count_LHS);
        count_LHS = LHS % 2;
        if (count_LHS = 1) {
          Binary_LHS[i] = '1';
        }
        
        LHS = LHS / 2;
       
        
     }
     count_LHS = 0;
     */
     // record if number is positive or negative
     if (LHS >= 0) {
       Binary[0] = '+';
     }
     else {
       Binary[0] = '-';
     }


     // put left hand side of number into binary
     if (abs(LHS % 2) == 1) {
       Binary[3] = '1';
     }
     LHS = LHS/ 2;
     
     if (abs(LHS % 2) == 1) {
       Binary[2] = '1';
     }
     LHS = LHS/ 2;
     
     if (abs(LHS % 2) == 1) {
       Binary[1] = '1';
     }
    
    // do the same thing for right hand side of input number
    
     if (abs(RHS % 2) == 1) {
       Binary[11] = '1';
     }
     RHS = RHS/ 2;
     
     if (abs(RHS % 2) == 1) {
       Binary[10] = '1';
     }
     RHS = RHS/ 2;    
    
     if (abs(RHS % 2) == 1) {
       Binary[9] = '1';
     }
     RHS = RHS/ 2;
     
     if (abs(RHS % 2) == 1) {
       Binary[8] = '1';
     }
     RHS = RHS/ 2;
     
     if (abs(RHS % 2) == 1) {
       Binary[7] = '1';
     }
     RHS = RHS/ 2;
     
     if (abs(RHS % 2) == 1) {
       Binary[6] = '1';
     }
     RHS = RHS/ 2;
     
     if (abs(RHS % 2) == 1) {
       Binary[5] = '1';
     }
     

      
    if (millis() % 1000 <=50) {
     lcd.setCursor(0,0);
     lcd.print(Display);  
      // Read in input pins     
      lcd.setCursor(0,1);
      lcd.print(Binary);
      lcd.setCursor(12,1);
      lcd.print("  ");
       // lcd.print(Binary_LHS);
       // lcd.print('.');
       // lcd.print(Binary_RHS);
      
      //lcd.setCursor(0,1);
      //lcd.print("Base_2 : ");
      //lcd.print(Binary);

     

    }
  
}
