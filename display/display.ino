#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define MENU_LENGTH 6
#define MENU_ROW_HEIGHT 11
#define LCD_ROWS  4

#define BTN_UP  3
#define BTN_DOWN  4

// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 7 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(5, 7, 3);

int menuPos = 0;
int menuScreen = 0;
int markerPos = 0;
int menuStartAt = 0;

String menu[6] = {
  "First item",
  "Second item",
  "Third item",
  "Fourth item",
  "Fifth item",
  "Sixth item",
};

void setup() {
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);

  display.begin();
  display.setContrast(60);
  display.setTextSize(1);
  display.clearDisplay();
  display.display();

  showMenu();
}

bool isButtonDown(int pin) {
  if (digitalRead(pin) == LOW) {
    delay(30);

    if (digitalRead(pin) == LOW) {      
      return true;
    }

    return false;
  }

  return false;
}

void showMenu() {  
  for (int i = menuStartAt; i < (menuStartAt + LCD_ROWS); i++) {
    int markerY = (i - menuStartAt) * MENU_ROW_HEIGHT;
    
    if (i == menuPos) {
      display.setTextColor(WHITE, BLACK);
      display.fillRect(0, markerY, display.width(), MENU_ROW_HEIGHT, BLACK);
    } else {
      display.setTextColor(BLACK, WHITE);
      display.fillRect(0, markerY, display.width(), MENU_ROW_HEIGHT, WHITE);
    }

    if (i >= MENU_LENGTH) {
      continue;
    }

    display.setCursor(2, markerY + 2);
    display.print(menu[i]);
  }

  display.display();
}

void loop() {
  if (isButtonDown(BTN_DOWN) == true) {   
      if (menuPos < MENU_LENGTH - 1) {
        menuPos++;
  
        if (menuPos > 3) {
          menuStartAt++;
        }
        
        showMenu();
      }
      
      delay(100);   
  }

  if (isButtonDown(BTN_UP) == true) {    
      if (menuPos > 0) {
        menuPos--;
  
        if (menuStartAt > 0) {
          menuStartAt--;
        }
        
        showMenu();
      }
      
      delay(100);
    }
}

