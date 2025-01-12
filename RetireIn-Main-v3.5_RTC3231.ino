#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RTClib.h>

// >>>>>>>>>>> HardWare: Nano-mega328p-_#_-LCD-I2C-16x2-_#_-RTC-DS3231-_#_-2-pin-Button <<<<<<<<<<<<<<<<<
//             Copyright (C) 2025. Simon Clarke & SRC Repairs ltd. All Rights Reserved

 // This program is free and Open-Source software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
 // as published by the Free Software Foundation, either version 3 of the License, or any later version.
 // This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 // implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 // You should have received a copy of the GNU General Public License along with this program. 
 // If not, see <http://www.gnu.org/licenses/>.

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Button setup
const int buttonPin = 2; // Connect button to pin 2 and GND
int buttonState = 0; 
int lastButtonState = 0; 
bool showRemaining = false; // Toggles between time views

// Set the retirement date
const int retirement_year = 2026;
const int retirement_month = 1;
const int retirement_day = 23;
const int retirement_hour = 11;

void setup() {
    
    Serial.begin(9600);
   lcd.init();
   lcd.backlight();

    if (!rtc.begin()) {
        lcd.print("RTC NOT FOUND");
        while (1); 
    }

    if (rtc.lostPower()) {
        lcd.clear();
        lcd.print("Set RTC time!");
     // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //----------- Un-Comment this line to set RTC Time to Compile Time
   
    }
    pinMode(buttonPin, INPUT_PULLUP); 

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("RetireIn V3");
    lcd.setCursor(0, 3);
    lcd.print("  Version 3.5");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(" LOADING.");
    delay(400);
    lcd.clear();
    lcd.print(" LOADING..");
    delay(500);
    lcd.clear();
    lcd.print(" LOADING...");
    delay(500);
    lcd.clear();
    lcd.print(" LOADING....");
    delay(500);
    lcd.clear();
    lcd.print(" LOADING......");
    delay(500);
    lcd.clear();
    lcd.print(" LOADING........");
    delay(500);
}

void loop() {
    buttonState = digitalRead(buttonPin);

    if (buttonState == LOW && lastButtonState == HIGH) {
        showRemaining = !showRemaining; 
        delay(200); // Debouncing delay
    }
    lastButtonState = buttonState;

    DateTime now = rtc.now();

    if (showRemaining) {
       
        DateTime retirementDate(retirement_year, retirement_month, retirement_day, retirement_hour, 0, 0);
        TimeSpan remaining = retirementDate - now;

        if (remaining.totalseconds() <=0) { 
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("YOU'RE Retired!"); 
            lcd.setCursor(0, 1);
            lcd.print("--YOU'RE Retired!");
            lcd.setCursor(0, 2);
            lcd.print("---YOU'RE Retired!");
            lcd.setCursor(0, 3);
            lcd.print("-----YOU'RE Retired!");
        } else {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("   Retirement is in");
            lcd.setCursor(0, 3);
            lcd.print(remaining.days());
            lcd.print(" days ");
            lcd.print(remaining.hours());
            lcd.print(" hours");
            //delay(1200000); // --------Un-Comment to Stop Flickering when displaying mode: Remaining Time
        }
    } else {
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("UK Time Now");
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.print(now.hour() < 10 ? "0" : ""); 
        lcd.print(now.hour());
        lcd.print(":");
        lcd.print(now.minute() < 10 ? "0" : ""); 
        lcd.print(now.minute());
    
    }

    delay(500); // Adjust accordingly to prevent flickering
}
