#include <CCS811.h>
#include <LiquidCrystal.h>

CCS811 sensor;
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

int tenRaisedTo[] = {1, 10, 100, 1000, 10000};

void printNumAlignRight(int n, int numDigits, int xRight, int y)
{
    for(int i = 0; i < numDigits; i++)
    {
        lcd.setCursor(xRight-i,y);
        lcd.write((n / tenRaisedTo[i]) % 10 + '0');
    }
}

void setup(void)
{
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Initializing");
    lcd.setCursor(0,1);
    lcd.print("CCS811 chip...");
    /*Wait for the chip to be initialized completely, and then exit*/
    while(sensor.begin() != 0){
        
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
    sensor.setMeasCycle(sensor.eCycle_250ms);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TVOC:      ppb");
    lcd.setCursor(0,1);
    lcd.print("CO2:       ppm");
}
void loop() {
  delay(1000);
    if(sensor.checkDataReady() == true){
        printNumAlignRight(sensor.getTVOCPPB(), 4, 9, 0);
        printNumAlignRight(sensor.getCO2PPM(), 4, 9, 1);
        
    } else {
        lcd.setCursor(6,0);
        lcd.print("NR");
    }
    /*!
     * @brief Set baseline
     * @param get from getBaseline.ino
     */
    sensor.writeBaseLine(0x847B);
    //delay cannot be less than measurement cycle
    //delay(1000);
}
