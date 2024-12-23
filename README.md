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

5. Volume Control(example)
   
In the Volume Menu, you can select a volume level from 0 to 6. Once selected, the system stores the volume level, and it can be used throughout the program.

6. Custom Actions on Start
   
When the "Start" menu item is selected, a simple cat face animation ("Meow!") is displayed, and the system returns to the Main Menu after a brief delay.

# How to Use 

the printpage() Function:

The printpage() function is a vital component of the program, designed to display menus on an LCD screen and manage user interactions. It operates within a loop, which continuously handles menu navigation and exits (breaks) when the page_name variable is updated. This allows smooth transitions between menus or custom loops. Here's how to use it effectively:

1. The printpage() Function
Core Functionality
The printpage() function:

Displays the menu options on the LCD, highlighting the current selection with a cursor (e.g., >> and <<).
Handles user input for navigation using buttons (e.g., Down for moving the cursor and OK for selecting an option).
Monitors the page_name variable and exits the loop when page_name changes, allowing the program to transition to a different menu or custom loop.
Adding Background Code
Inside the printpage() loop, you can execute background tasks while the menu is displayed. For example, on a "Volume" page, you might use a Serial.print function to continuously show the current volume level. Look for the section marked with a comment in the function and add your code there.

Parameters
arr[]:
An array of strings representing the menu options displayed on the LCD. Each string must be exactly 16 characters long to match the LCD’s format and ensure consistent behavior.
Example:

cpp
Copy code
const char* mainMenu[] = {"      Start     ", 
                          "      Settings  ", 
                          "      Exit      "};
sizeArr:
The number of options in the arr[]. It tells the function how many menu items to handle.
Example: If there are 3 items in arr[], sizeArr = 3.

currentPage:
The name of the current page (e.g., " Settings "), displayed as a header on the LCD.

previousPage:
The name of the previous menu (e.g., " Main Menu "). Selecting "Back" will update page_name to this value, returning to the previous menu.

2. The page_name Variable
The page_name variable is critical for navigating between menus and custom loops. It determines which menu or loop the program should execute.

Key Rules for Using page_name
Exact Matching is Crucial:
The value of page_name must match the option string in the arr[] array exactly (including spaces) for the program to navigate correctly. For example:

If the menu option is " Settings ", you must set page_name = " Settings " to enter that menu.
Incorrectly formatted names (e.g., "Settings") will cause errors or undefined behavior.
16-Character Convention:
To maintain compatibility with the LCD display and avoid issues, always use 16-character strings for page_name and menu options.
Examples:

" Volume "
" Settings "
" Main Menu "
Workflow: From Menu to Menu or Custom Loops
Entering a Menu:

The program remains in a specific menu loop while page_name matches the menu’s name.
When a user selects an option, the program updates page_name to the selected option’s name, triggering an exit from the current menu and transitioning to the new one.
Transitioning to a Custom Loop:

For custom functionality (e.g., volume adjustment), the program changes page_name to the custom loop’s name (e.g., " Volume ").
Inside the custom loop, you can handle unique tasks before returning to a menu.
Returning to the Parent Menu:

After completing a custom loop or selecting "Back," the program updates page_name to the parent menu’s name (e.g., " Settings ") and re-enters that menu.
Example Scenario
Main Menu
Options: " Start ", " Settings ", " Exit "
Selecting " Settings " sets page_name = " Settings " and transitions to the Settings menu.
Settings Menu
Options: " Volume ", " Back "
Selecting " Volume " sets page_name = " Volume " and transitions to the Volume custom loop.
Selecting " Back " sets page_name = " Main Menu " and returns to the Main Menu.
Volume Custom Loop
Adjusts the volume based on user input.
Selecting "Back" sets page_name = " Settings " and transitions back to the Settings menu.
Why This Structure Works
Clear Navigation:
Using page_name ensures that the program knows exactly which menu or loop to execute at all times.

Consistency:
The 16-character string requirement prevents mismatches and keeps the LCD display aligned.

Flexibility:
You can add custom loops or new menus by simply updating the page_name logic and ensuring the names match the 16-character convention.

By adhering to these guidelines, you can efficiently use the printpage() function to create a robust, dynamic, and user-friendly menu system.
