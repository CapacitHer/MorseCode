/*
Lucky Cat
 /\_/\  
( ^_^ ) 
 > ~ <
*/

#include <LiquidCrystal.h>

const int buttonPin = 7;
const int ledPin = 13;
String morseCode = "";
String decodedMessage = "";
unsigned long pressStartTime = 0;
bool previousButtonState = LOW;
bool currentButtonState = LOW;
unsigned long lastPressTime = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

String morseToChar(String morse) {
  if (morse == "...---...") return "[ERASE]"; //erase last letter 
  if (morse == ".-.-.-") return "[NEW LINE]"; //new line 
  if (morse == "---...") return " "; //space 

  if (morse == ".-") return "A"; 
  if (morse == "-...") return "B"; 
  if (morse == "-.-.") return "C"; 
  if (morse == "-..") return "D"; 
  if (morse == ".") return "E"; 
  if (morse == "..-.") return "F"; 
  if (morse == "--.") return "G"; 
  if (morse == "....") return "H"; 
  if (morse == "..") return "I"; 
  if (morse == ".---") return "J"; 
  if (morse == "-.-") return "K"; 
  if (morse == ".-..") return "L"; 
  if (morse == "--") return "M"; 
  if (morse == "-.") return "N"; 
  if (morse == "---") return "O"; 
  if (morse == ".--.") return "P"; 
  if (morse == "--.-") return "Q"; 
  if (morse == ".-.") return "R"; 
  if (morse == "...") return "S"; 
  if (morse == "-") return "T"; 
  if (morse == "..-") return "U"; 
  if (morse == "...-") return "V"; 
  if (morse == ".--") return "W"; 
  if (morse == "-..-") return "X"; 
  if (morse == "-.--") return "Y"; 
  if (morse == "--..") return "Z"; 
  if (morse == "-----") return "0"; 
  if (morse == ".----") return "1"; 
  if (morse == "..---") return "2"; 
  if (morse == "...--") return "3"; 
  if (morse == "....-") return "4"; 
  if (morse == ".....") return "5"; 
  if (morse == "-....") return "6"; 
  if (morse == "--...") return "7"; 
  if (morse == "---..") return "8"; 
  if (morse == "----.") return "9"; 
  return "";
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  currentButtonState = !digitalRead(buttonPin);

  if (currentButtonState && !previousButtonState) {
    pressStartTime = millis();
    digitalWrite(ledPin, HIGH);
  }

  if (!currentButtonState && previousButtonState) {
    digitalWrite(ledPin, LOW);
    unsigned long pressDuration = millis() - pressStartTime;

    if (pressDuration < 300) {
      morseCode += ".";
    } else {
      morseCode += "-";
    }
    lastPressTime = millis();
    delay(300); // debounce delay
  }

  if (morseCode.length() > 0 && millis() - lastPressTime > 1000) { // time constraint to end character
    String decodedChar = morseToChar(morseCode);

    if (decodedChar == "[ERASE]") { // Erase the last letter
      if (decodedMessage.length() > 0) {
        decodedMessage.remove(decodedMessage.length() - 1);
      }
    } 
    else if (decodedChar == "[NEW LINE]") { // New line
      decodedMessage += "\n";
    } 
    else {
      decodedMessage += decodedChar;
    }

    morseCode = "";
    lcd.clear();
    lcd.print("Decoded Message:");
    lcd.setCursor(0, 1);
    lcd.print(decodedMessage);
  }

  previousButtonState = currentButtonState;
}
