## Check out this examples

![EX:1](https://github.com/user-attachments/assets/ca7f616c-705e-4055-80c9-a1262699a55d)

![EX2](https://github.com/user-attachments/assets/faa08660-f00c-4ab6-aeee-a5d98c7ff17b)





This program offers a highly flexible menu navigation system in Arduino IDE for an LCD screen, compatible with LCD I2C 4x20 and 2x16 displays, as well as two buttons . It enables users to navigate effortlessly through multiple menus, select options, and adjust settings. The system is easily adaptable to various user interface requirements, making it suitable for both simple and complex menu structures.
# Features:
*The workflow is simple and intuitive, requiring only a few minutes to understand. It not only makes your code more organized and clear, and also speeds up the process if you need to recreate or modify the algorithm.

*Create custom menus with unlimited items, despite the LCD size, and navigate through them efficiently.

*Navigate inside the menus with a cursor, displayed as ">> item <<".

*Adjust anything to run in the background while navigating through menus, or design your own custom interface to your script. 

*Compatible with LCD I2C 20x4 and 16x2 displays, using two buttons ('Down' and 'OK'). You can also add additional buttons or features as needed.

*You only need the LiquidCrystal library to get started—no additional libraries are required. You can find examples in the examples path. These examples are designed to help you understand the basics and begin working directly without any extra setup.

# Wiring:
Buttons:   Pin7 : button ‘ok’ (optional pin)
                Pin8 : button ‘down’(optional pin)
                
Lcd:         SDA : A4
                SCL : A5




<img width="430" alt="animals" src="https://github.com/user-attachments/assets/1325e98d-0953-4359-b230-3a9698a59896" />


# How to use:
To use the algorithm, you need to be aware of a few things:

1*The printpage(); function allows you to display your flexible menu (I will explain it further later).

2*To display your custom menu, you need to define it like this:
```C++
String Menu_name=  "      Menu      ";

String Menu[] = {
"      item1      ",          
"      item2      ",          
"      item3      " }; 

const int Menu_Size = sizeof(Menu) / sizeof(Menu[0]);

page_name = printpage(Menu, Menu_Size, Menu_name, ""); 

```

3*You can add as many items as you want to display in the menu.

4*You cannot name two items the same, even in different menus. If you do so, additional code will be required to resolve the conflict:
```C++
String Menu[] = {"      item1      " ,"      item1      " };  -----X
```
5*You cannot name two menus or a menu and an item with the same name(unless you want to turn the item into a menu than you need to name it as the item). Look at the simple exemple to understand how to apply it

6*All strings should be 16 characters for the 20x4 LCD and 10 characters for the 16x2 LCD, including the menu name. Here's how it should be formatted:
For the 20x4 LCD:
```C++
String Menu_name = "      Menu      ";  // 16 characters in

String Menu[] = {"      item1      ", "      item2      "}; 
```
For the 16x2 LCD:
```C++
String Menu_name = "   Menu   ";  // 10 characters

String Menu[] = {"   item1   ", "   item2   "}; 
```
# The loops : 
To work with the algorithm, you need to understand that each menu is essentially a loop that the code will enter based on a variable called page_name.
The page_name variable allows you to navigate between menus and also enables you to create custom loops with your own rules. If you want to exit a menu loop, simply click on an item, and the menu will change to the selected item's menu. This is done by changing the page_name to something else (the item you picked). You can refer to examples for more details. If you wish to display things differently, you can create your own custom loop and implement any logic you want.
This flexibility allows you to adapt the flow to your specific needs, such as adding conditional behaviors or creating non-standard display patterns.
Important note: If you create an item inside a menu without setting a menu for it, the screen will freeze. This happens because the loop will break and enter the void loop, which has nothing to execute unless you change it.



# printpage() function:
*The function parameters : 
```C++
String printpage(const String arr[], int sizeArr, String currentPage, String previousPage);
```
Parameters arr[] : An array of strings representing the menu options displayed on the LCD. Each string must be exactly 16 characters(or 10) long to match the LCD’s format and ensure consistent behavior.

sizeArr : The number of options in the arr[]. It tells the function how many menu items to handle .

currentPage: The name of the current page (e.g.,Menu_name ), displayed as a header on the LCD.

previousPage: The name of the previous menu ```(e.g., "      Menu      ")```. Selecting  
```"      back      "``` will update page_name to this value, returning to the previous menu.

Exp: 
```C++
page_name = printpage(Menu, Menu_Size,"      Menu      " , "");
```

*The printpage() its a loop that the code will entre incase the page_name variable set to the menu name will allow you to make a flexible menu with limitless items inside 
You can add any custom code to run in the background while navigating through the menus.
I have set a designated place in the code for you to insert your background code.
Additionally, you can add more parameters to the function if needed, allowing you to customize the behavior further based on your specific requirements. This flexibility ensures that you can integrate your own logic and features seamlessly while maintaining the menu navigation system.


# Disclaimer:

This is a fully open-source code, and anyone is free to use, modify, or add anything they wish to it. If you base your project on this code, please make sure to credit me by mentioning my account. This ensures that the original work is recognized while allowing others to benefit from your adaptations and improvements.

I’m happy to help anyone using this code, Feel free to contact me if you need assistance👽✨. 

