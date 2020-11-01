#include <LiquidCrystal_I2C.h>                                          // also includes Wire.h library so no need to include separately
LiquidCrystal_I2C lcd(0x27, 20, 4);                                     // set up display called 'lcd' at address 0x27 (change to suit)
const byte AloA = 2, AloB = 3, AloC = 4, AhiA = 5, AhiB = 6, AhiC = 7;  // assign pins for low/high address CD4051's select pins (A,B,C)
const byte DatA = 8, DatB = 9, DatC = 10;                               // assign pins for data CD4051 select pins (A,B,C)
const byte InA = 11, InB = 12, InC = 13;                                // assign pins for input CD4051 select pins (A,B,C)
const byte InCOM = 14, DatCOM = 15, AhiCOM = 16, AloCOM = 17;           // assign CD4051 COM I/O controls
const byte OE = A6, FREQ = A7;                                          // assign control pins (A4 and A5 are used for I2C)
byte bits[8];                                                           // array for binary representation

void setup() {
  for(byte i = 13; i >= 2; i--){ pinMode(i, OUTPUT); }                  // set output pins, others are input by default
  lcd.init();
  lcd.backlight();
  displaytext(3,1,(F("LAoE interface")));                               // flash screen at startup
  displaytext(2,2,(F("Love electronics")));
  delay(2500);
  lcd.clear();
  displaytext(0, 0, "Addr:");                                           // fixed screen text
  displaytext(0, 2, "Data:");
  displaytext(12, 2, "Input:"); }

void loop () {
  displaytext(16, 0, (analogRead(FREQ) > 500 ? "10Hz": "20Hz"));        // display current frequency
  displaydata(6, 0, 0, 1, AhiA, AhiB, AhiC, AhiCOM);                    // display address high byte in hex and binary
  displaydata(9, 0, 9, 1, AloA, AloB, AloC, AloCOM);                    // display address low byte in hex and binary
  displaydata(6, 2, 0, 3, DatA, DatB, DatC, DatCOM);                    // display data byte in hex and binary
  if (analogRead(OE) > 500) {
    displaytext(18, 2, "--");
    displaytext(12, 3, "(High Z)"); }
  else{ displaydata(18, 2, 12, 3, InA, InB, InC, InCOM); } }            // display input byte in hex and binary

void displaytext(byte col, byte row, String text) {
  lcd.setCursor(col, row); lcd.print(text); }

void displaydata(byte a, byte b, byte c, byte d, byte A, byte B, byte C, byte COMpin) {
  for (byte channel = 0; channel < 8; channel++) {
    digitalWrite(A,(1&channel));
    digitalWrite(B,(2&channel));
    digitalWrite(C,(4&channel));
    delay(2);
    bits[channel]=digitalRead(COMpin); }                                //digital read of 'analog' pins (CD4051 COM I/O pins)
  byte lsb = (bits[3]*8)+(bits[2]*4)+(bits[1]*2)+bits[0];
  byte msb = (bits[7]*8)+(bits[6]*4)+(bits[5]*2)+bits[4];
  lcd.setCursor(a, b); lcd.print(msb, HEX); lcd.print(lsb, HEX);
  lcd.setCursor(c, d);
  for (byte i = 8; i >= 1; i--) { lcd.print(bits[i-1]); } }
