#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Define pins for the up and down buttons
const int butOkPin = 7;      // Pin for OK button (select)
const int butDownPin = 8;    // Pin for Down button (navigate down)
int butok, butdown; // Variables to store the button states (1 or 0)

// Initial page name to start with
String page_name = "";

// Define the LCD size (number of rows visible at a time)
int lcdsize = 4;  // The LCD has 4 rows of text to display

// Initialize the I2C LCD (address 0x27, 20 columns, 4 rows)
LiquidCrystal_I2C lcd(0x27, 20, 4);  

// Define global string arrays for different pages
// Each array represents a page with its menu items
// The important part is that the items inside the menus (options) should not have the same name
String page1[]={""}

// Calculate the size of each page array (number of menu items) to handle navigation
const int page1_Size = sizeof(page1) / sizeof(page1[0]);

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the LCD
  lcd.init();                     
  lcd.backlight(); // Turn on the LCD backlight

  // Set button pins as input
  pinMode(butOkPin, INPUT);  // Set OK button pin as input
  pinMode(butDownPin, INPUT); // Set Down button pin as input
}

void loop() {
  // Update button states
  read();
  
  // Define repeat variable for animations (don't remove it)
  int repeat = 0;
  
  
}

// Reads the states of the up and down buttons
void read() {
  butok = digitalRead(butOkPin);     // Read the state of the "OK" button
  butdown = digitalRead(butDownPin); // Read the state of the "Down" button
  delay(100); // Simple debounce delay
}

// Function to render and navigate through a page
// arr: array of menu items for the page
// sizeArr: number of menu items in the array
// currentPage: current page name (to be displayed on LCD)
// previousPage: the page to return to when "back" is selected
String printpage(const String arr[], int sizeArr, String currentPage, String previousPage) {
  int i = 0; // LCD cursor row (0-3) 
  int j = 0; // Page index (0 to sizeArr-1)
  
  // Render the menu until we leave the current page
  while (currentPage == page_name) {
    read();  // Update button states

    // Highlight the currently selected item with ">>" at the start and "<<" at the end
    lcd.setCursor(17, i);
    lcd.print(" <<");
    lcd.setCursor(0, i);
    lcd.print(">> ");

    // Display the menu items on the LCD
    for (int d = 0; d < lcdsize; d++) {
      lcd.setCursor(2, d);  // Set the cursor to the 2nd column and row
      if (j >= lcdsize) {
        lcd.print(arr[j + d - lcdsize + 1]);  // Scroll through the menu if there are more items than the LCD can show
      } 
      else if (d >= sizeArr) {
        lcd.print("                ");  // Blank lines if there are fewer menu items than the LCD rows
      }
      else {
        lcd.print(arr[d]);  // Display the menu item
      }
    }
    
    // Circular navigation within the array
    j = j % sizeArr;
    if (sizeArr < lcdsize) { 
      i = i % sizeArr;  // Ensure cursor stays within bounds if there are fewer items than the LCD rows
    } else { 
      i = i % lcdsize;  // Ensure cursor stays within bounds if there are more items than the LCD rows
    }

    //////////// ADD YOUR BACKGROUND CODE HERE ///////////////
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    


    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////

    // Button handling for navigation
    if (butdown == 1) {  // If Down button is pressed, move to the next item
      lcd.setCursor(17, i);
      lcd.print("   ");
      lcd.setCursor(0, i);
      lcd.print("   ");
      j = (j + 1) % sizeArr;  // Move to the next item
      if (sizeArr < lcdsize) { 
        i = (i + 1) % sizeArr; 
      } else { 
        i = (i + 1) % lcdsize; 
      }
    }

    // Ensure the cursor stays within bounds
    if (j > i) {
      i = lcdsize - 1; // Move cursor to the last row if the index exceeds
    }

    if (butok == 1) {  // If OK button is pressed, select the current item
      lcd.setCursor(17, i);
      lcd.print("   ");
      lcd.setCursor(0, i);
      lcd.print("   ");
      
      // Handle the "back" option to navigate back to the previous page
      if (arr[j] == "      back      ") {
        page_name = previousPage;  // Go back to the previous page
      } else {
        page_name = arr[j];  // Set the selected item as the current page
      }
      lcd.clear();  // Clear the screen for the next page
      break;
    }
  }

  return page_name;  // Return the updated page name
}
