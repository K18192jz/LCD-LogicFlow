#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Define pins for the up and down buttons
const int butOkPin = 7;      // Pin for OK button (select)
const int butDownPin = 8;    // Pin for Down button (navigate down)
int butok, butdown; // Variables to store the button states (1 or 0)

// Initial page name to start with
String page_name = "      Main      "; 

// Define the LCD size (number of rows visible at a time)
int lcdsize = 4;  // The LCD has 4 rows of text to display

// Initialize the I2C LCD (address 0x27, 20 columns, 4 rows)
LiquidCrystal_I2C lcd(0x27, 20, 4);  

// Define global string arrays for different pages
// Each array represents a page with its menu items
// The important part is that the items inside the menus (options) should not have the same name

String Main_Menu[] = {
  "      Start     ",          // Option 1: Start
  "      Settings  ",          // Option 2: Settings
  "      Exit      "           // Option 3: Exit (this is not used in code, will freeze if selected)
};

String Settings[] = {
  "      Volume    ",          // Option 1: Volume (navigate to volume settings)
  "      back      "           // Option 2: Go back to the main menu
};

String Volume[] = {
  "        0       ",          // Option 1: Volume level 0
  "        1       ",          // Option 2: Volume level 1
  "        2       ",          // Option 3: Volume level 2
  "        3       ",          // Option 4: Volume level 3
  "        4       ",          // Option 5: Volume level 4
  "        5       ",          // Option 6: Volume level 5
  "        6       ",          // Option 7: Volume level 6
  "      back      "           // Option 8: Go back to settings menu
};

// Calculate the size of each page array (number of menu items) to handle navigation
const int Main_Menu_Size = sizeof(Main_Menu) / sizeof(Main_Menu[0]);
const int Settings_Size = sizeof(Settings) / sizeof(Settings[0]);
const int Volume_Size = sizeof(Volume) / sizeof(Volume[0]);

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

int Volume_value = 0;  // Store the selected volume level (from 0 to 6)

void loop() {
  // Update button states
  read();
  
  // Define repeat variable for animations (don't remove it)
  int repeat = 0;

  // Handle navigation and rendering of pages
  // The pages will be rendered in sequence; however, it doesn't matter the order,
  // The important part is that the items inside the menus (options) should not have the same name
  page_name = printpage(Main_Menu, Main_Menu_Size, "      Main      ", ""); // Main menu doesn't need a "back" option
  page_name = printpage(Settings, Settings_Size, "      Settings  " , "      Main      "); // Settings menu, with back to "Main Menu"
  page_name = printpage(Volume, Volume_Size, "      Volume    " , "      Settings  "); // Volume menu, with back to "Settings"
  
  // Function to check volume selection (updates the volume value) 
  checkVolumeSelection();

  // Animation when the "      Start     " item is selected
  while (page_name == "      Start     ") {
    if (repeat == 0) {
      // Print animation on the LCD
      Serial.println(Volume_value);  // Output the current volume to the serial monitor
      lcd.setCursor(0, 0);   // Set cursor to the top row, column 0
      lcd.print("       /\\_/\\  ");  // Display a simple cat face animation
      delay(1000); 
      lcd.setCursor(0, 1);
      lcd.print("      ( o.o )   ");
      delay(1000); 
      lcd.setCursor(0, 2);
      lcd.print("       > ^ <    ");
      delay(1000); 
      lcd.setCursor(0, 3);
      lcd.print("       Meow!    ");
      delay(1000); 
      repeat++;  // Avoid repeating animation
    }
    read();  // Update button states
    if (butok == 1 || butdown == 1) {  // If OK or Down button is pressed, exit the animation
      delay(100);  // Small delay before going back to Main Menu
      page_name = "      Main      ";  // Go back to the main menu
      break;
    }
  }
}

// Reads the states of the up and down buttons
void read() {
  butok = digitalRead(butOkPin);     // Read the state of the "OK" button
  butdown = digitalRead(butDownPin); // Read the state of the "Down" button
  lcd.clear();  // Clear the screen
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
    Serial.println(Volume_value);  // Output the current volume to the serial monitor while display lcd
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

// Function to check the volume selection and update the Volume_value
void checkVolumeSelection() {
  // Check if the current page is showing a volume level (0, 1, 2, ..., 6)
  if (page_name == "        0       ") {
    Volume_value = 0;
    page_name = "      Volume    ";  // Navigate to the volume page
  }
  else if (page_name == "        1       ") {
    Volume_value = 1;
    page_name = "      Volume    ";  // Navigate to the volume page
  }
  else if (page_name == "        2       ") {
    Volume_value = 2;
    page_name = "      Volume    ";  // Navigate to the volume page
  }
  else if (page_name == "        3       ") {
    Volume_value = 3;
    page_name = "      Volume    ";  // Navigate to the volume page
  }
  else if (page_name == "        4       ") {
    Volume_value = 4;
    page_name = "      Volume    ";  // Navigate to the volume page
  }
  else if (page_name == "        5       ") {
    Volume_value = 5;
    page_name = "      Volume    ";  // Navigate to the volume page
  }
  else if (page_name == "        6       ") {
    Volume_value = 6;
    page_name = "      Volume    ";  // Navigate to the volume page
  }
}
