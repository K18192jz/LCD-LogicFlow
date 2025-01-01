#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Pin definitions for buttons
const int butokPin = 7;      
const int butDownPin = 8;
int butok, butdown;


// LCD setup
int lcdsize = 2;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize LCD with I2C address 0x27, 16 columns, 2 rows


void setup() {
  Serial.begin(9600);            // Start serial communication for debugging
  lcd.init();                    // Initialize the LCD
  lcd.backlight();               // Turn on the backlight of the LCD

  pinMode(butokPin, INPUT);      // Set button pin as input
  pinMode(butDownPin, INPUT);    // Set button pin as input
}


void loop() {
  // Read button states
  read();
  
  // Variable for animation control (do not remove)
  int repeat = 0;
}

// Function to read button states
void read() {
  butok = digitalRead(butokPin);     // Read OK button state
  butdown = digitalRead(butDownPin);  // Read Down button state
  delay(150);  // Short delay for debouncing
}

// Function to display and navigate through menu pages
String printpage(const String arr[], int sizeArr, String currentPage, String previousPage) {
  int i = 0; // Row of the LCD
  int j = 0; // Index for current menu option

  while (currentPage == page_name) {
    read();  // Read button states
    lcd.setCursor(13, i);   // Set cursor for "<<" indicator
    lcd.print(" <<");
    lcd.setCursor(0, i);     // Set cursor for ">>" indicator
    lcd.print(">> ");

    // Display menu items
    for (int d = 0; d < lcdsize; d++) {
      lcd.setCursor(2, d);  // Set cursor for each option
      if (j >= lcdsize) {
        lcd.print(arr[j + d - lcdsize + 1]);  // Display next options if j exceeds lcdsize
      } 
      else if (d >= sizeArr) {
        lcd.print("            ");  // Clear if there are fewer options than the lcdsize
      }
      else {
        lcd.print(arr[d]);  // Display option text
      }
    }

    j = j % sizeArr;  // Ensure j stays within array size
    if (sizeArr < lcdsize) { i = (i ) % sizeArr; }  // Ensure index stays within screen range
    else { i = (i ) % lcdsize; }  // Ensure index stays within LCD rows
    //////////// ADD YOUR BACKGROUND CODE HERE ///////////////
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    



    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    // Handle button navigation
    if (butdown == 1) {
      lcd.setCursor(13, i);
      lcd.print("   ");
      lcd.setCursor(0, i);
      lcd.print("   ");
      j = (j + 1) % sizeArr;  // Move to next option
      if (sizeArr < lcdsize) { i = (i + 1) % sizeArr; }
      else { i = (i + 1) % lcdsize; }
    }

    if (j > i) {
      i = lcdsize - 1;  // Ensure scrolling is within bounds
    }

    // Handle "OK" button press for selection
    if (butok == 1) {
      lcd.setCursor(17, i);  // Clear selected option
      lcd.print("   ");
      lcd.setCursor(0, i);
      lcd.print("   ");
      if (arr[j] == "    back    ") {
        page_name = previousPage;  // Go back to the previous page
      }
      else {
        page_name = arr[j];  // Navigate to the selected page
      }
      lcd.clear();  // Clear screen after selection
      break;
    }
  }

  return page_name;  // Return the current page name
}
