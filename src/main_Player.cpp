// /***************************************************
// DFPlayer - A Mini MP3 Player For Arduino
//  <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>

//  ***************************************************
//  This example shows the basic function of library for DFPlayer.

//  Created 2016-12-07
//  By [Angelo qiao](Angelo.qiao@dfrobot.com)

//  GNU Lesser General Public License.
//  See <http://www.gnu.org/licenses/> for details.
//  All above must be included in any redistribution
//  ****************************************************/

// /***********Notice and Trouble shooting***************
//  1.Connection and Diagram can be found here
//  <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
//  2.This code is tested on Arduino Uno, Leonardo, Mega boards.
//  ****************************************************/

// #include <Arduino.h>
// #include <DFRobotDFPlayerMini.h>

// HardwareSerial mySerial(1);
// DFRobotDFPlayerMini myDFPlayer;
// void printDetail(uint8_t type, int value);

// struct Button {
//   const uint8_t PIN;
//   uint32_t numberKeyPresses;
//   bool pressed;
// };

// Button buttonUp = {15, 0, false};
// Button buttonDown = {4, 0, false};
// int volume = 0;

// void IRAM_ATTR isrUp() {
//   buttonUp.pressed = true;
// }
// void IRAM_ATTR isrDown() {
//   buttonDown.pressed = true;
// }

// void setup()
// {
//   mySerial.begin(9600, SERIAL_8N1, 16, 17);
//   Serial.begin(115200);

//   Serial.println();
//   Serial.println(F("DFRobot DFPlayer Mini Demo"));
//   Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

//   if (!myDFPlayer.begin(mySerial), false) {  //Use softwareSerial to communicate with mp3.
//     Serial.println(F("Unable to begin:"));
//     Serial.println(F("1.Please recheck the connection!"));
//     Serial.println(F("2.Please insert the SD card!"));
//     while(true);
//   }
//   Serial.println(F("DFPlayer Mini online."));

//   pinMode(buttonUp.PIN, INPUT_PULLUP);
//   attachInterrupt(buttonUp.PIN, isrUp, FALLING);
//   pinMode(buttonDown.PIN, INPUT_PULLUP);
//   attachInterrupt(buttonDown.PIN, isrDown, FALLING);
  
//   //----Read imformation----
//   Serial.println(myDFPlayer.readState()); //read mp3 state
//   Serial.println(myDFPlayer.readVolume()); //read current volume
//   Serial.println(myDFPlayer.readEQ()); //read EQ setting
//   Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
//   Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
//   Serial.println(myDFPlayer.readFileCountsInFolder(1)); //read fill counts in folder SD:/03
  
//   volume = 15;

//   myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
//   myDFPlayer.enableLoopAll();
//   myDFPlayer.play(1);  //Play the first mp3
// }

// void loop()
// {
//   static unsigned long timer = millis();
//   static unsigned long timer2 = millis();

//   if (buttonUp.pressed && millis() - timer2 > 250) {
//     buttonUp.pressed = false;
//     timer2 = millis(); // debounce
    
//     if(volume < 30)
//     {
//       volume++;
//       myDFPlayer.volume(volume);
//     }
//     Serial.printf("buttonUp Volume = %d\n", volume);
//   }

//   if (buttonDown.pressed && millis() - timer2 > 250) {
//     buttonDown.pressed = false;
//     timer2 = millis();

//     if(volume > 0)
//     {
//       volume--;
//       myDFPlayer.volume(volume);
//     }
//     Serial.printf("buttonDown Volume = %d\n", volume);
//   }

//   if (millis() - timer > 150000) {
//     timer = millis();
//     //myDFPlayer.next();  //Play next mp3 every 3 second.
//   }

//   if (myDFPlayer.available()) {
//     printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
//   }
// }

// void printDetail(uint8_t type, int value){
//   switch (type) {
//     case TimeOut:
//       Serial.println(F("Time Out!"));
//       break;
//     case WrongStack:
//       Serial.println(F("Stack Wrong!"));
//       break;
//     case DFPlayerCardInserted:
//       Serial.println(F("Card Inserted!"));
//       break;
//     case DFPlayerCardRemoved:
//       Serial.println(F("Card Removed!"));
//       break;
//     case DFPlayerCardOnline:
//       Serial.println(F("Card Online!"));
//       break;
//     case DFPlayerPlayFinished:
//       Serial.print(F("Number:"));
//       Serial.print(value);
//       Serial.println(F(" Play Finished!"));
//       break;
//     case DFPlayerError:
//       Serial.print(F("DFPlayerError:"));
//       switch (value) {
//         case Busy:
//           Serial.println(F("Card not found"));
//           break;
//         case Sleeping:
//           Serial.println(F("Sleeping"));
//           break;
//         case SerialWrongStack:
//           Serial.println(F("Get Wrong Stack"));
//           break;
//         case CheckSumNotMatch:
//           Serial.println(F("Check Sum Not Match"));
//           break;
//         case FileIndexOut:
//           Serial.println(F("File Index Out of Bound"));
//           break;
//         case FileMismatch:
//           Serial.println(F("Cannot Find File"));
//           break;
//         case Advertise:
//           Serial.println(F("In Advertise"));
//           break;
//         default:
//           break;
//       }
//       break;
//     default:
//       break;
//   }
// }