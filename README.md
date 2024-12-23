# LCD LogicFlow: Flexible Menu Navigation
# Overview
This program provides a highly flexible menu navigation system for an LCD screen, designed to work with just two buttons. It allows users to easily navigate through multiple menus, select options, and adjust settings (like volume exemple). The system can be easily adapted to various user interface needs, making it suitable for simple or more complex menu structures.
# Features:
Multi-page Navigation: Navigate between menus such as Main Menu, Settings, and Volume.

Button Input: Use two buttons (OK and Down) for navigation.

Background Process: A background task runs while navigating through the menus.

Pin Setup:

Pin 7: OK button (used for selection).

Pin 8: Down button (used for scrolling through menu items).

# LCD Setup:
The system uses an I2C LCD with address 0x27 and dimensions of 20 columns and 4 rows.

# Code Flow
 1. Initialization
    
In the setup() function:

Serial communication is initialized.
The LCD is initialized, and the backlight is turned on.
Button pins are set as inputs.
2. Button Reading

The read() function checks the states of the OK and Down buttons.

3. Main Loop and Menu Navigation
   
The printpage() function is responsible for displaying menus and handling navigation:

arr: An array of menu items to display on the LCD.
sizeArr: The number of items in the menu array.
currentPage: The name of the current page (e.g., "Settings").
previousPage: The page to return to when the "back" option is selected.
4. Background Code

While navigating through the menu, you can add any background tasks that should run (e.g., checking volume level or updating settings).

5. Volume Control
   
In the Volume Menu, you can select a volume level from 0 to 6. Once selected, the system stores the volume level, and it can be used throughout the program.

7. Custom Actions on Start
   
When the "Start" menu item is selected, a simple cat face animation ("Meow!") is displayed, and the system returns to the Main Menu after a brief delay.

# How to Use
Understanding the printpage() Function
The printpage() function is a core part of this program. It is used to display menus on the LCD screen and handle user input for menu navigation. The function is called in a loop to display the pages and handle the user interaction. Here’s a breakdown of how it works:

Function Parameters:

arr: An array of strings representing the menu items to be displayed.
sizeArr: The number of items in the array (arr).
currentPage: A string representing the name of the current page.
previousPage: A string representing the name of the previous page.
Function Workflow:

Display the Menu: The printpage() function displays the current page’s menu items on the LCD screen.
Navigation: The user can navigate through the menu items using the Down button. The cursor moves up and down through the list of options.
Select an Option: The user can press the OK button to select an option.
Return to Previous Page: If the "back" option is selected, the user is returned to the previousPage.
Example Usage:
Main Menu:
Menu items: "Start", "Settings", "Exit"

"Settings" → navigates to the Settings page
"Start" → exits to a custom loop with a cat animation and then returns to the Main Menu
"Exit" → freezes the program
Settings Menu:
Menu items: "Volume", "Back"

"Volume" → navigates to the Volume page
"Back" → returns to the Main Menu
Volume Menu:
Menu items: "0", "1", "2", "3", "4", "5", "6", "Back"

# Select volume level → updates the volume and returns to the Settings menu(for the example)
"Back" → returns to the Settings menu
Volume Selection and Update
For the sake of this example, we included a function checkVolumeSelection() to check the selected volume option and update the Volume_value based on the page_name:


void checkVolumeSelection() {
  if (page_name == "        0       ") {
    Volume_value = 0;
    page_name = "      Volume    ";  // Go back to the volume page
  }

  else if (page_name == "        1       ") {
    Volume_value = 1;
    page_name = "      Volume    ";  // Go back to the volume page
  }
  // Repeat for other volume levels...
}
# Adding Global and Local Variables to printpage() for Custom Logic
You can define global or local variables in the printpage() function to implement custom behaviors. These variables allow for dynamic, flexible behavior in your menus.

# Example Use Cases:
Background Tasks: Add a variable to manage background code execution, like a backgroundMode variable for managing background tasks like volume monitoring or animations.
Global Variable Example:
cpp
Copy code
bool backgroundMode = true;  // Global variable to control background tasks
Inside the printpage() function, you can check and modify this variable to perform different actions depending on the state of the background:


if (backgroundMode) {
  // Run background code, such as monitoring volume or animations
}
Remember Settings:
You can use global variables to store settings (like the volume) and maintain them across different menus.


int Volume_value = 0;  // Global variable to store the volume level
Important Note on Page Flow and Action Timing
It does not matter how you scale the printpage() or the custom loop, because the program will always pick the correct page based on the print_page variable.

Key Consideration: If you want to perform an action immediately after selecting an option (before navigating to the selected page), you should add the action right after the printpage() function is executed. This is important when there are no lists or when you need to manage the page flow dynamically.



