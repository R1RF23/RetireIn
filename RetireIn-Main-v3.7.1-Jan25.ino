#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RTClib.h>

// * Copyright (C) 2025. Simon Clarke & SRC Repairs ltd. All Rights Reserved
 
 //* This program is free and Open-Source software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
 //as published by the Free Software Foundation, either version 3 of the License, or any later version.
 
 //* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 //implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 //* You should have received a copy of the GNU General Public License along with this program. 
 //If not, see <http://www.gnu.org/licenses/>.

// >>>>>>-----HW SETUP
RTC_DS1307 rtc;                       // Pins: V+<->5V, GND<->GND, SCK<->A5, SDA<->A4
LiquidCrystal_I2C lcd(0x27, 16, 2);   // Pins: V+<->5V, GND<->GND, SCK<->A5, SDA<->A4

const int buttonPin = 2;             // 2pin Button--- 1P<->D2, 1P<->GND
int buttonState;
int lastButtonState = HIGH; 
bool showRemaining = false;
int scrollPosition = 0;
bool hasScrolled = false;
const char* scrollingMessage = "SCROLLING MSG"; //V3 IS BETTER THAN THE LAST 2 VERSIONS BUT STILL NOT EVEN NEAR AS GOOD AS IT COULD BE IF I HAD THE TIME TO SPARE.
unsigned long previousMillis = 0;
const long interval = 5000; //ScrollSpeed

// Set RetireDate
const int retirement_year = 2026;
const int retirement_month = 1;
const int retirement_day = 23;
const int retirement_hour = 11;


void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();

    if (!rtc.begin()) {
        lcd.setCursor(0, 0);
        lcd.print("RTC NOT FOUND!!");
        lcd.setCursor(0, 1);
        lcd.print("CHECK RTC WIRING");
        while (1); 
    }

    if (!rtc.isrunning()) {
        lcd.clear();
        lcd.print("Set RTC time!");
        //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //----------- Un-Comment this line to set RTC Time to Compile Time
    }
    pinMode(buttonPin, INPUT_PULLUP); 

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  RetireIN  V3");
    lcd.setCursor(0, 1);
    lcd.print("  Version 3.7.1");
    delay(4000);
    lcd.clear();
    lcd.print(" LOADING.");
    delay(600);
    lcd.clear();
    lcd.print(" LOADING..");
    delay(500);
    lcd.clear();
    lcd.print(" LOADING...");
    delay(400);
    lcd.clear();
    lcd.print(" LOADING....");
    delay(300);
    lcd.clear();
    lcd.print(" LOADING......");
    delay(200);
    lcd.clear();
    lcd.print(" LOADING........");
    delay(100);
    lcd.clear();
    
            if (!hasScrolled) {
            lcd.setCursor(0, 1);
            for (int i = 0; i < 16; i++) {
                if (scrollPosition + i < strlen(scrollingMessage)) {
                    lcd.write(scrollingMessage[scrollPosition + i]);
                delay(100);
                } else {
                    lcd.write(' '); // FILL IF PRINT IS -< 16CHARS
                }
            }

            scrollPosition++;
            if (scrollPosition >= strlen(scrollingMessage)) {
                hasScrolled = true; //ScrollFLAGG
        }
delay(4000); //scrolling speed(*note: Value isTOTAL)
     }
}

void loop() {
    unsigned long currentMillis = millis();
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

        if (remaining.totalseconds() <= 0) { 
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("YO              ");
            lcd.setCursor(0, 1);
            lcd.print("              d!");
            delay(500);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("YOU'R           ");
            lcd.setCursor(0, 1);
            lcd.print("            red!");
    delay(400);
    lcd.clear();
    lcd.setCursor(0, 0);
            lcd.print("YOU'RE          ");
            lcd.setCursor(0, 1);
            lcd.print("          tired!");
    delay(300);
    lcd.clear();
    lcd.setCursor(0, 0);
            lcd.print("YOU'RE Re       ");
            lcd.setCursor(0, 1);
            lcd.print("        Retired!");
    delay(300);
    lcd.clear();
    lcd.setCursor(0, 0);
            lcd.print("YOU'RE Reti     ");
            lcd.setCursor(0, 1);
            lcd.print("    'RE Retired!");
    delay(200);
    lcd.clear();
    lcd.setCursor(0, 0);
            lcd.print("YOU'RE Retire   ");
            lcd.setCursor(0, 1);
            lcd.print("   U'RE Retired!"); 
    delay(200);
    lcd.clear();
    lcd.setCursor(0, 0);
            lcd.print(" YOU'RE Retired!");
            lcd.setCursor(0, 1);
            lcd.print(" YOU'RE Retired!");  
            delay(500);
        } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Retirement is in");
            lcd.setCursor(0, 1);
            lcd.print(remaining.days());
            lcd.print(" days ");
            lcd.print(remaining.hours());
            lcd.print(" hrs");
        }
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("UK Time Now");
        lcd.setCursor(0, 1);
        lcd.print(now.hour() < 10 ? "0" : ""); 
        lcd.print(now.hour());
        lcd.print(":");
        lcd.print(now.minute() < 10 ? "0" : ""); 
        lcd.print(now.minute());
    }

    delay(300); //scroll speed
}
