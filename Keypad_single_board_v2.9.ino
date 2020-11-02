#include <Keypad.h>
char keymap [4] [4] = { { '1', '2', '3', 'A' }, { '4', '5', '6', 'B' }, { '7', '8', '9', 'C' }, { 'E', '0', 'F', 'D' } }; // define keypad array
const byte colPins [4] = {9, 8, 7, 6}, rowPins [4] = {5, 4, 3, 2};                                                        // define keypad pins
const byte number [16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};                                          // keypad map array
const byte INH = 10, FREQ = 11, CLR = 12, SER = 13, OE = 14, RCLK = 15, SRCLK = 16, SRCLR = 17, FREQOUT = 18;             // define control pins
byte digit [2] = {0, 1};
Keypad KPad (makeKeymap(keymap), rowPins, colPins, 4, 4);                                                                 // setup keypad

void setup() {
  pinMode(INH, OUTPUT);
  pinMode(CLR, INPUT_PULLUP);
  for (byte i = 18; i >= 13; i--) { pinMode(i, OUTPUT); }
  outputControl(HIGH, HIGH, LOW);}
  
void loop() {
  byte i = 0;
  if (digitalRead(CLR)) {                                                  // if CLR button NOT pressed
    do{ char key = KPad.getKey();
      if (key) {                                                           // has keypad been pressed?
        if (key >= 65) { key = key-55; }                                   // map ASCII codes to number array elements (A to 10....F to 15)
        else { key = key-48; }                                             // 48 to 0....57 to 9
        digit [i] = number [key];                                          // assign each digit
        i = i+1; }
        else{ digitalWrite(FREQOUT, pulseIn(FREQ, HIGH) > 25000 ? 1: 0); } // update frequency
      if (!digitalRead(CLR)) { i = 2; }                                    // escape loop if CLR pressed
    }while (i < 2);                                                        // wait for two key presses
    outputControl(LOW, LOW, HIGH);                                         // sets OE, INH and SRCLR
    digitalWrite(RCLK, LOW);
    shiftOut(SER, SRCLK, MSBFIRST, (digit [0]*16)+digit [1]);              // shift out binary number from the two digits
    digitalWrite(RCLK, HIGH); }
  else{ outputControl(HIGH, HIGH, LOW); }                                  // if CLR button IS pressed set OE, INH and SRCLR
} 
        
void outputControl(bool a, bool b, bool c) {
  digitalWrite(OE, a);                                                     // keypad 74HC595 output 
  digitalWrite(INH, b);                                                    // output signal to display
  digitalWrite(SRCLR, c); }                                                // keypad 74HC595 shift register
