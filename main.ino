#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Lil guy you can move around
byte lilguy[8] = {
    0b01110,
    0b10001,
    0b10001,
    0b01110,
    0b00000,
    0b01110,
    0b11111,
    0b01010,
};

// Variables
// ===================================================================================================================================================================
int x; // the location of the lil guy                                                                                                                                |
const int on = 1023; // Analog input value                                                                                                                           |
const int lcl = 16; // The length of the LCD display, (Liquid Crystal Length)                                                                                        |
int letter; // For refresh, what column am I in?                                                                                                                     |
bool isPickedUp; // Decide whether or not the letter will follow lil guy.                                                                                            |
bool canPlace; // If there's a letter there, you can't place it                                                                                                      |
bool canPickUp; // Is there anything to pick up?                                                                                                                     |
int held; // What letter can be picked up?                                                                                                                           |
int letterLoc[5] = {2,3,4,5,6}; // Letter Locations. If forking, you need to change this to be the size of the text you added. (inc number by 2 to avoid weird bugs) |
// ===================================================================================================================================================================

// The actual program
void setup() {
  // Init stuff
  lcd.begin(lcl, 2); // LCD size or something I think
  Serial.begin(9600); // Using analog inputs for controls since digital pins were getting cluttered

  // Add lil guy to the spites list
  lcd.createChar(0, lilguy);

  // This has been: Init stuff
}

void loop() {
  // The ACTUAL program

  lcd.clear(); // Wipe the screen each frame so the lil guy doesn't multiply (One already almost destroyed the world)
  
  lcd.setCursor(15,0);
  lcd.print(held);
  // Get lil guy inputs
  int lilLeft = analogRead(A0);
  int lilRight = analogRead(A1);
  // Lil guy pick up letters
  int pickUp = analogRead(A2);

  // Anything to do with this list is super ugly so uhh
  if (x == letterLoc[0]) {
    canPickUp = true;
    held = 1;
  } else if (x == letterLoc[1]) {
    canPickUp = true;
    held = 2;
  } else if (x == letterLoc[2]) {
    canPickUp = true;
    held = 3;
  } else if (x == letterLoc[3]) {
    canPickUp = true;
    held = 4;
  } else if (x == letterLoc[4]) {
    canPickUp = true;
    held = 5;
  } else {
    canPickUp = false;
    held = 0;
  };


  // Show my name on screen line 1 OLD VERSION IGNORE
  // lcd.setCursor(0, 0);
  // lcd.print("Obscured for privacy");

  // Lil Guy controls (screen line 2)

  // Left
  if (lilLeft == on) {
    if (x>0) {
      x--;
    };
  };
  
  // Right
  if (lilRight == on) {
    if (x<15) {
      x++;
    };
  };
  
  // Letter Pick Up
  if (pickUp == on) {
    if (!isPickedUp && canPickUp) {
      isPickedUp = true;
    } else {
      isPickedUp = false;

    };
  };

  // Letter follow lil guy
  if (isPickedUp) {
    // This list was the worst idea ever I need to fix all this code later, maybe try using pthreads
    if (held == 1) {
      letterLoc[0] = x;
    } else if (held == 2) {
      letterLoc[1] = x;
    } else if (held == 3) {
      letterLoc[2] = x;
    } else if (held == 4) {
      letterLoc[3] = x;
    } else if (held == 5) {
      letterLoc[4] = x;
    }
  };

  // Display lil guy
  lcd.setCursor(x, 1); 
  lcd.write((uint8_t)0);
  // Letters (Lil Guy more important they get refreshed first L letters)


  // Super messy code just minimize and carry on with your day it's so bad (If you're changing the text you will have to deal with this though)
  for (letter<lcl; letter++;) {
    if (letter == letterLoc[0]) {
      lcd.setCursor(letter, 0);
      lcd.print("H");
    } else if (letter == letterLoc[1]) { // This code can induce vomiting, you have been warned
      lcd.setCursor(letter, 0);
      lcd.print("e");
    } else if (letter == letterLoc[2]) {
      lcd.setCursor(letter, 0);
      lcd.print("n");
    } else if (letter == letterLoc[3]) {
      lcd.setCursor(letter, 0);
      lcd.print("r");
    } else if (letter == letterLoc[4]) {
      lcd.setCursor(letter, 0);
      lcd.print("y");
    };
  };

  // delay(20); // Cap framerate so the text doesn't look weird (screen has problems refreshing too fast) PROGRAM TOO SLOW TO NEED THIS
};