/*
 * --------------------------------------------------------------------------------------------------------------------
 * ESP32-Tonie - For Samuel
 * --------------------------------------------------------------------------------------------------------------------
 * 
 * Author: Lukas Kaiser (lukas@lukas-kaiser.at)
 * 2019-11
 * 
 */

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 121 // 1st byte for count of cards + room for 30 cards (* 4 bytes for id)
#define MODE_CONFIG 0
#define MODE_PLAYBACK 1
#define MODE_HIBERNATION 255

boolean inMenu = false;
byte modeSelect = -1;
uint8_t tagCount = 0;

void setup()
{
    Serial.begin(115200); // start serial connection to pc for configuration
    while (!EEPROM.begin(EEPROM_SIZE)); // init EEPROM

    Serial.println();
    Serial.println("     Welcome to");
    Serial.println("    ___________ ____ ________        __              _          ");
    Serial.println("   / ____/ ___// __ \\__  /__ \\      / /_____  ____  (_)__  _____");
    Serial.println("  / __/  \\__ \\/ /_/ //_ <__/ /_____/ __/ __ \\/ __ \\/ / _ \\/ ___/");
    Serial.println(" / /___ ___/ / ____/__/ / __/_____/ /_/ /_/ / / / / /  __(__  ) ");
    Serial.println("/_____//____/_/   /____/____/     \\__/\\____/_/ /_/_/\\___/____/  ");
    Serial.println();

    // load data from eprom
    tagCount = EEPROM.read(0);
    Serial.print("tagCount = ");
    Serial.println(tagCount);
}


void loop()
{
    // we are allways in the menue unless in config
    if(!inMenu)
    {
        inMenu = true;
        // show menu
        Serial.println();
        Serial.println("Menu:");
        Serial.println("[c] config");
        Serial.println("[r] reset");
    }

    if (Serial.available() > 0)
    {
        byte incomingByte = 0;
        incomingByte = Serial.read();
        Serial.println();

        switch (incomingByte)
        {
        case 'c':
            Serial.println("Configuration was selected");
            inMenu = false;
            break;
        case 'r':
            Serial.println("Reset to factory settings");
            for (int i = 0 ; i < EEPROM_SIZE ; i++)
            {
                EEPROM.write(i, 0);
            }
            EEPROM.commit();
            inMenu = false;
            break;
        
        default:
            Serial.print("Unknown command \"");
            Serial.print(char(incomingByte));
            Serial.println("\"");
            inMenu = false;
            break;
        }
    }
}