#include <CCS811.h>
#include <LiquidCrystal.h>

#define UPDATE_INTERVAL 1000  // Cannot be greater than measurement cycle interval

CCS811 sensor;
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

unsigned long initTime, lastUpdatedTime, currentTime;

int32_t tenRaisedTo[] = {1, 10, 100, 1000, 10000, 100000, 1000000}; // for use in printNumAlignRight

void printNumAlignRight(unsigned long n, int numDigits, int xRight, int y) {  // Print a number on the LCD display aligning right with a certain number of digits, adding padding zeros to the left if necessary
    for(int i = 0; i < numDigits; i++) {  // Loop through each digit
        lcd.setCursor(xRight-i,y);                    // Set cursor to position of digit
        lcd.write((n / tenRaisedTo[i]) % 10 + '0');   // Write the current digit (adding '0' converts the value from range 0 to 9 to range '0' to '9')
    }
}

void setup(void) {
    // Display initialization message on LCD
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Initializing");
    lcd.setCursor(0,1);
    lcd.print("CCS811 chip...");

    // Wait for the chip to be initialized completely
    while(sensor.begin() != 0) {
        delay(1000);
    }

    /**
     * @brief Set measurement cycle
     * @param cycle:in typedef enum{
     *                  eClosed,      //Idle (Measurements are disabled in this mode)
     *                  eCycle_1s,    //Constant power mode, IAQ measurement every second
     *                  eCycle_10s,   //Pulse heating mode IAQ measurement every 10 seconds
     *                  eCycle_60s,   //Low power pulse heating mode IAQ measurement every 60 seconds
     *                  eCycle_250ms  //Constant power mode, sensor measurement every 250ms
     *                  }eCycle_t;
     */
    sensor.setMeasCycle(sensor.eCycle_1s);

    initTime = millis();
    lastUpdatedTime = 0;

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("V:");
    lcd.setCursor(9,0);
    lcd.print("C:");
    lcd.setCursor(0,1);
    lcd.print("Time:         s");
}
void loop() {
    currentTime = millis() - initTime;  // Get time (milliseconds) since initialization was completed
    if(currentTime - lastUpdatedTime >= UPDATE_INTERVAL) {  // Runs every UPDATE_INTERVAL milliseconds
        lastUpdatedTime += UPDATE_INTERVAL;

        if(sensor.checkDataReady() == true) {
            printNumAlignRight(sensor.getTVOCPPB(), 5, 6, 0);
            printNumAlignRight(sensor.getCO2PPM(), 5, 15, 0);
        } else {
            lcd.setCursor(2,0);
            lcd.print("error");
            lcd.setCursor(11,0);
            lcd.print("error");
        }

        printNumAlignRight(currentTime/1000, 7, 12, 1);
        
        /*!
         * @brief Set baseline
         * @param get from getBaseline.ino
         */
        sensor.writeBaseLine(0x847B);
    }
}
