#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Pin definitions for buttons
const int butokPin = 7;      
const int butDownPin = 8;
int butok, butdown;
String page_name = "    Main    ";  // Initialize the page to "Main"

// LCD setup
int lcdsize = 2;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize LCD with I2C address 0x27, 16 columns, 2 rows

// Menu options
String Main_Menu[] = {
  "    Start   ",          // Option 1: Start
  "   Settings ",          // Option 2: Settings
  "   Exit     "           // Option 3: Exit (not implemented in code)
};

String Settings[] = {
  "   Volume   ",          // Option 1: Volume settings
  "    back    "           // Option 2: Go back to the main menu
};

String Volume[] = {
  "      0     ",          // Option 1: Volume level 0
  "      1     ",          // Option 2: Volume level 1
  "      2     ",          // Option 3: Volume level 2
  "      3     ",          // Option 4: Volume level 3
  "      4     ",          // Option 5: Volume level 4
  "      5     ",          // Option 6: Volume level 5
  "      6     ",          // Option 7: Volume level 6
  "    back    "           // Option 8: Go back to settings menu
};

// Calculate the size of each menu
const int Main_Menu_Size = sizeof(Main_Menu) / sizeof(Main_Menu[0]);
const int Settings_Size = sizeof(Settings) / sizeof(Settings[0]);
const int Volume_Size = sizeof(Volume) / sizeof(Volume[0]);

void setup() {
  Serial.begin(9600);            // Start serial communication for debugging
  lcd.init();                    // Initialize the LCD
  lcd.backlight();               // Turn on the backlight of the LCD

  pinMode(butokPin, INPUT);      // Set button pin as input
  pinMode(butDownPin, INPUT);    // Set button pin as input
}

int Volume_value = 0;  // Variable to store selected volume level (0 to 6)

void loop() {
  // Read button states
  read();
  
  // Variable for animation control (do not remove)
  int repeat = 0;

  // Handle page navigation and rendering
  // The pages will render in sequence; the important part is ensuring options do not repeat
  page_name = printpage(Main_Menu, Main_Menu_Size, "    Main    ", "");  // Render main menu
  page_name = printpage(Settings, Settings_Size, "   Settings ", "    Main    ");  // Render settings menu with back option
  page_name = printpage(Volume, Volume_Size, "   Volume   ", "   Settings ");  // Render volume menu with back option

  // Function to handle volume selection
  checkVolumeSelection();

  // Animation when the "Start" option is selected
  while (page_name ==  "    Start   ") {
    if (repeat == 0) {
      // Display animation on LCD
      Serial.println(Volume_value);  // Output the current volume value to the serial monitor
      lcd.setCursor(0, 0);   // Set cursor to row 0, column 0
      lcd.print("   ><(((('> ");  // Display animation (simple cat face)
      delay(1000); 
      lcd.setCursor(0, 1);   // Set cursor to row 1, column 0
      lcd.print("   <'))))>< ");
      repeat=1;  // Ensure animation is not repeated
    }
    read();  // Read button states
    if (butok == 1 || butdown == 1) {  // If OK or Down button is pressed, exit animation
      delay(100);  // Short delay before going back to main menu
      page_name = "    Main    ";  // Go back to the main menu
      lcd.clear();  // Clear the LCD screen
      break;
    }
  }
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

// Function to handle volume selection and update volume value
void checkVolumeSelection() {
  // Check if a volume option is selected
  if (page_name == "      0     ") {
    Volume_value = 0;
    page_name = "   Volume   ";  // Return to volume page
  }
  else if (page_name == "      1     ") {
    Volume_value = 1;
    page_name = "   Volume   ";  // Return to volume page
  }
  else if (page_name == "      2     ") {
    Volume_value = 2;
    page_name = "   Volume   ";  // Return to volume page
  }
  else if (page_name == "      3     ") {
    Volume_value = 3;
    page_name = "   Volume   ";  // Return to volume page
  }
  else if (page_name == "      4     ") {
    Volume_value = 4;
    page_name = "   Volume   ";  // Return to volume page
  }
  else if (page_name == "      5     ") {
    Volume_value = 5;
    page_name = "   Volume   ";  // Return to volume page
  }
  else if (page_name == "      6     ") {
    Volume_value = 6;
    page_name = "   Volume   ";  // Return to volume page
  }
}
