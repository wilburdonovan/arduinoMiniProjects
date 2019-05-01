#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Fonts/FreeSans12pt7b.h> 
#include <Fonts/FreeSans24pt7b.h> 

#include <Adafruit_SSD1306.h>

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#define SSD1306_LCDHEIGHT 64
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int potPin1= A0; //Assigning potPen to A0
int potPin2= A1;
int readVal1; // declaring readvalue variable
int readVal2;

// Define constants used to calibrate the potentiometer to the Launch knob in the vehicle
const int oneLaunchValue = 1;          // Sensor Value for 1st Launch
const int twoLaunchValue = 93;           // Sensor Value for 2nd Launch
const int threeLaunchValue = 186;          // Sensor Value for 3rd Launch
const int fourLanuchValue = 279;           // Sensor Value for 4th Launch
const int fiveLaunchValue = 372;          // Sensor Value for 5th Launch
const int sixLanuchValue = 465;           // Sensor Value for 6th Launch
const int sevenLaunchValue = 558;          // Sensor Value for 7th Launch
const int eightLanuchValue = 651;           // Sensor Value for 8th Launch
const int nineLaunchValue = 744;          // Sensor Value for 9th Launch
const int tenLanuchValue = 837;           // Sensor Value for 10th Launch
const int elevenLaunchValue = 930;          // Sensor Value for 11th Launch
const int twelveLanuchValue = 1022;           // Sensor Value for 12th Launch
const int rangeband = 20;           // Band either side of selected gear position must be less than half the variance of each sequential shift value

// Constants for gear shift
// Define constants used to calibrate the potentiometer to the gear shifter in the vehicle
const int parkValue = 18;          // Sensor Value for Park Position
const int revValue = 218;           // Sensor Value for Reverse Gear
const int neuValue = 426;           // Sensor Value for Neutral Gear
const int oneValue = 630;           // Sensor Value for 1st Gear
const int twoValue = 825;           // Sensor Value for 2nd Gear
const int threeValue = 1005;         // Sensor Value for 3rd Gear

// Assign variables for gear indicator determination calculations
int LaunchVal = 0;              // value read from the pot as a 0 to 1023 integer
int GearVal = 0;              // value read from pot 0-1023 integer
String outValue = "X";        // Assign output variable for launch control to be stored and printed
String outValueGear = "X";    // Outvalue for gear shift

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
  Serial.begin(9600); //Starting serial port

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();

 
}

void loop() {
  // put your main code here, to run repeatedly:
  LaunchVal = analogRead(potPin1); //read input from potentiometer 1 (launch)
  GearVal = analogRead(potPin2); // read input from potentiometer 2 (gear control)


  // LAUNCH VALUE CODE
  if (LaunchVal > (oneLaunchValue-rangeband) && LaunchVal < (oneLaunchValue+rangeband)) {
  outValue = ("1");
  } else if (LaunchVal > (twoLaunchValue-rangeband) && LaunchVal < (twoLaunchValue+rangeband)) {
  outValue = ("2");
  } else if (LaunchVal > (threeLaunchValue-rangeband) && LaunchVal < (threeLaunchValue+rangeband)) {
  outValue = ("3");
  } else if (LaunchVal > (fourLanuchValue-rangeband) && LaunchVal < (fourLanuchValue+rangeband)) {
  outValue = ("4");
  } else if  (LaunchVal > (fiveLaunchValue-rangeband) && LaunchVal < (fiveLaunchValue+rangeband)) {
  outValue = ("5");
  } else if  (LaunchVal > (sixLanuchValue-rangeband) && LaunchVal < (sixLanuchValue+rangeband)) {
  outValue = ("6");    
  } else if (LaunchVal > (sevenLaunchValue-rangeband) && LaunchVal < (sevenLaunchValue+rangeband)) {
  outValue = ("7");
  } else if  (LaunchVal > (eightLanuchValue-rangeband) && LaunchVal < (eightLanuchValue+rangeband)) {
  outValue = ("8");
   } else if  (LaunchVal > (nineLaunchValue-rangeband) && LaunchVal < (nineLaunchValue+rangeband)) {
  outValue = ("9");
  } else if  (LaunchVal > (tenLanuchValue-rangeband) && LaunchVal < (tenLanuchValue+rangeband)) {
  outValue = ("10");    
  } else if (LaunchVal > (elevenLaunchValue-rangeband) && LaunchVal < (elevenLaunchValue+rangeband)) {
  outValue = ("11");
  } else if  (LaunchVal > (twelveLanuchValue-rangeband) && LaunchVal < (twelveLanuchValue+rangeband)) {
  outValue = ("12");
  } else {
  outValue = (" ");
  }

  //GEAR VALUE CODE
  if (GearVal > (parkValue-rangeband) && GearVal < (parkValue+rangeband)) {
  outValueGear = ("P");
  } else if (GearVal > (revValue-rangeband) && GearVal < (revValue+rangeband)) {
  outValueGear = ("R");
  } else if (GearVal > (neuValue-rangeband) && GearVal < (neuValue+rangeband)) {
  outValueGear = ("N");
  } else if (GearVal > (oneValue-rangeband) && GearVal < (oneValue+rangeband)) {
  outValueGear = ("1");
  } else if  (GearVal > (twoValue-rangeband) && GearVal < (twoValue+rangeband)) {
  outValueGear = ("2");
  } else if  (GearVal > (threeValue-rangeband) && GearVal < (threeValue+rangeband)) {
  outValueGear = ("3");    
  } else {
  outValueGear = (" ");
  }

  // print the results to the serial monitor:
  Serial.print("Launch in = " );
  Serial.print(LaunchVal);
  Serial.print("\t Launch Control Value = ");
  Serial.println(outValue);
  Serial.print("Gear in = " );
  Serial.print(GearVal);
  Serial.print("\t Gear = ");
  Serial.println(outValueGear);



// output launch value to display
  display.clearDisplay();
  display.setFont(&FreeSans24pt7b);
  display.setTextColor(WHITE);
  display.setCursor(8,32);
  display.print(outValueGear);

// Draw a vertical dividing line between gear display and volts display
  display.drawLine(50, 0, 50, display.height(), WHITE);
  display.drawLine(51, 0, 51, display.height(), WHITE);

// Output gear to display
  display.setFont(&FreeSans12pt7b);
  display.setCursor(64,24);
  display.print(outValue);
  
  display.display(); 
  
  delay(2);    //wait 2 milliseconds before the next loop for the analog-to-digital converter to settle after the last reading:

}
