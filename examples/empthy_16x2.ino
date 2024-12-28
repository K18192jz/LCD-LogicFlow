#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int butUpPin = 7;      
const int butDownPin = 2;
int butup, butdown;
String ppp = "page1";

int lcdsize = 2;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 20 chars and 4 line display

// Define the global string array as page1
String page1[] = {
  "    frezz   ",
  "    frezz   ",
  "    cat     ",
  "    frezz   ",
  "    frezz   ",
  "    frezz   "
  
};

const int page1Size = sizeof(page1) / sizeof(page1[0]);

void setup() {
  lcd.init();                     
  lcd.backlight();

  pinMode(butUpPin, INPUT);
  pinMode(butDownPin, INPUT);
}
int repeat=0;
void loop() {
  read();
  ppp = printpage(page1, page1Size, "page1");  // Use page1 as the global array
  while (ppp=="      cool      "){
    if(repeat == 0){
    lcd.setCursor(0, 0);
    lcd.print("       /\\_/\\  ");  
    delay(1000); 
    lcd.setCursor(0, 1);
    lcd.print("      ( o.o )   ");
    delay(1000); 
    lcd.setCursor(0, 2);
    lcd.print("       > ^ <    ");
    delay(1000); 
    lcd.setCursor(0, 3);
    lcd.print("       Meow!    ");
    repeat++;
    }
    read();
    if (butup==1){
      ppp= "      cat       ";
      break;
    }
  }
}

void read() {
  // Update button states
  butup = digitalRead(butUpPin);     
  butdown = digitalRead(butDownPin);  
  delay(200);
}

String printpage(const String arr[], int sizeArr, String pp) {
  int i = 0; // LCD cursor row (0-3)
  int j = 0; // Page index (0 to size)

  while (pp == ppp) {
    read();
    lcd.setCursor(13, i);
    lcd.print(" <<");
    lcd.setCursor(0, i);
    lcd.print(">> ");

    for (int d = 0; d < lcdsize; d++) {
      lcd.setCursor(2, d);
      if (j >= lcdsize) {
        lcd.print(arr[j + d - lcdsize + 1]);
      } 
      else if (d >=sizeArr){
        lcd.print("            ");
        
      }
      else {
        lcd.print(arr[d]);
      }
    }

    j = j % sizeArr;
    if(sizeArr < lcdsize){i = (i ) % sizeArr;}
    else {i = (i ) % lcdsize;}
    ///////////////////////////////////////////////////////
    /////////////////////RF////////////////////////////////
    ///////////////////////////////////////////////////////
    if (butdown == 1) {
      lcd.setCursor(13, i);
      lcd.print("   ");
      lcd.setCursor(0, i);
      lcd.print("   ");
      j = (j + 1) % sizeArr;
      if(sizeArr < lcdsize){i = (i + 1) % sizeArr;}
      else {i = (i + 1) % lcdsize;}
    }
    if (j > i) {
      i = lcdsize - 1;
    }
    if (butup == 1) {
      lcd.setCursor(17, i);
      lcd.print("   ");
      lcd.setCursor(0, i);
      lcd.print("   ");
      if (arr[j]=="    back    "){
        ppp = "page1";
      }
      else{
      ppp = arr[j];}
      lcd.clear();
      break;
    }
  }

  return ppp;
}
