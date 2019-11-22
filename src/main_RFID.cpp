// /*
//  * --------------------------------------------------------------------------------------------------------------------
//  * Example sketch/program showing how to read new NUID from a PICC to serial.
//  * --------------------------------------------------------------------------------------------------------------------
//  * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
//  * 
//  * Example sketch/program showing how to the read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
//  * Reader on the Arduino SPI interface.
//  * 
//  * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
//  * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
//  * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
//  * will show the type, and the NUID if a new card has been detected. Note: you may see "Timeout in communication" messages
//  * when removing the PICC from reading distance too early.
//  * 
//  * @license Released into the public domain.
//  * 
//  * Typical pin layout used:
//  * -----------------------------------------------------------------------------------------
//  *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
//  *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
//  * Signal      Pin          Pin           Pin       Pin        Pin              Pin
//  * -----------------------------------------------------------------------------------------
//  * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
//  * SPI SS      SDA(SS)      10            53        D10        10               10
//  * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
//  * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
//  * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
//  */

// #include <SPI.h>
// #include <MFRC522.h>

// #define SS_PIN 21
// #define RST_PIN 22

// int counter = 0;

// void printDec(byte *buffer, byte bufferSize);
// void printHex(byte *buffer, byte bufferSize);

// MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

// MFRC522::MIFARE_Key key; 

// // Init array that will store new NUID 
// byte nuidPICC[4];

// typedef struct {
//     int cardID;
//     byte nuid[4];
// } rfidCard;

// void printCard(rfidCard* card);
// int getCardId(byte *nuid);

// rfidCard cards[30];

// void setup() { 
//   Serial.begin(115200);
//   SPI.begin(); // Init SPI bus
//   rfid.PCD_Init(); // Init MFRC522 

//   // Cards
//   cards[0] = (rfidCard) {0, {43, 92, 132, 89} };
// cards[1] = (rfidCard) {1, {138, 71, 133, 89} };
// cards[2] = (rfidCard) {2, {200, 26, 133, 89} };
// cards[3] = (rfidCard) {3, {128, 214, 132, 89} };
// cards[4] = (rfidCard) {4, {31, 135, 132, 89} };
// cards[5] = (rfidCard) {5, {121, 204, 132, 89} };
// cards[6] = (rfidCard) {6, {189, 198, 132, 89} };
// cards[7] = (rfidCard) {7, {131, 167, 132, 89} };
// cards[8] = (rfidCard) {8, {140, 149, 132, 89} };
// cards[9] = (rfidCard) {9, {60, 112, 132, 89} };
// // Sticker
// cards[10] = (rfidCard) {10, {218, 28, 252, 31} };
// cards[11] = (rfidCard) {11, {218, 31, 217, 31} };
// cards[12] = (rfidCard) {12, {218, 34, 233, 31} };
// cards[13] = (rfidCard) {13, {218, 38, 34, 31} };
// cards[14] = (rfidCard) {14, {218, 41, 126, 31} };
// cards[15] = (rfidCard) {15, {218, 45, 0, 31} };
// cards[16] = (rfidCard) {16, {218, 48, 160, 31} };
// cards[17] = (rfidCard) {17, {218, 49, 235, 31} };
// cards[18] = (rfidCard) {18, {218, 46, 59, 31} };
// cards[19] = (rfidCard) {19, {218, 42, 172, 31} };

//   for (byte i = 0; i < 6; i++) {
//     key.keyByte[i] = 0xFF;
//   }

//   Serial.println(F("This code scan the MIFARE Classsic NUID."));
//   Serial.print(F("Using the following key:"));
//   printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
// }
 
// void loop() {

//   // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
//   if ( ! rfid.PICC_IsNewCardPresent())
//     return;

//   // Verify if the NUID has been readed
//   if ( ! rfid.PICC_ReadCardSerial())
//     return;

//   Serial.print(F("PICC type: "));
//   MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
//   Serial.println(rfid.PICC_GetTypeName(piccType));

//   // Check is the PICC of Classic MIFARE type
//   if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
//     piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
//     piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
//     Serial.println(F("Your tag is not of type MIFARE Classic."));
//     return;
//   }

//   if (rfid.uid.uidByte[0] != nuidPICC[0] || 
//     rfid.uid.uidByte[1] != nuidPICC[1] || 
//     rfid.uid.uidByte[2] != nuidPICC[2] || 
//     rfid.uid.uidByte[3] != nuidPICC[3] ) {
//     Serial.println(F("A new card has been detected."));

//     // Store NUID into nuidPICC array
//     for (byte i = 0; i < 4; i++) {
//       nuidPICC[i] = rfid.uid.uidByte[i];
//     }
    
//     Serial.println(F("The NUID tag is:"));
//     Serial.print(F("In hex: "));
//     printHex(rfid.uid.uidByte, rfid.uid.size);
//     Serial.println();
//     Serial.print(F("In dec: "));
//     printDec(rfid.uid.uidByte, rfid.uid.size);
//     Serial.println();

//     int result = getCardId(nuidPICC);
//     if(result == -1)
//     {
//         cards[counter] = (rfidCard) {counter,{nuidPICC[0], nuidPICC[1], nuidPICC[2], nuidPICC[3]}};
//         Serial.print("\n");
//         Serial.print("!! -> New Card in Dec: ");
//         printCard(&cards[counter]);
//         Serial.print("\n\n");
//         counter++;

//         Serial.println();
//         Serial.println(F("//----------------------------------//"));
//         Serial.println(F("//         THE CURRENT DECK         //"));
//         Serial.println(F("//----------------------------------//"));
//         for(int id =  0; id < counter; id++)
//         {
//             Serial.print(F("//  "));
//             printCard(&cards[id]);
//             Serial.println("  //");
//         }
//         Serial.println(F("//----------------------------------//"));
//         Serial.println();

//         Serial.println();
//         Serial.println(F("//----------------------------------//"));
//         Serial.println(F("//               CODE               //"));
//         Serial.println(F("//----------------------------------//"));
//         for(int id =  0; id < counter; id++)
//         {
//             //cards[x] = (rfidCard) {x, {y, z, r} };
//             Serial.print("cards[");
//             Serial.print(id);
//             Serial.print("] = (rfidCard) {");
//             Serial.print(cards[id].cardID);
//             Serial.print(", {");
//             Serial.print(cards[id].nuid[0]);
//             Serial.print(", ");
//             Serial.print(cards[id].nuid[1]);
//             Serial.print(", ");
//             Serial.print(cards[id].nuid[2]);
//             Serial.print(", ");
//             Serial.print(cards[id].nuid[3]);
//             Serial.print("} };");
//             Serial.println();
//         }
//         Serial.println(F("//----------------------------------//"));
//         Serial.println();

//     } else {
//         Serial.print("\n");
//         Serial.print("!! -> Card already in Deck with ID #");
//         Serial.println(result);
//         Serial.print("\n\n");

//         Serial.println(F("//----------------------------------//"));
//         Serial.println(F("//         THE CURRENT DECK         //"));
//         Serial.println(F("//----------------------------------//"));
//         for(int id =  0; id < counter; id++)
//         {
//             Serial.print(id==result ? "//                                  //\n": "");
//             Serial.print(F("//"));
//             Serial.print(id==result ? "->": "  ");
//             printCard(&cards[id]);
//             Serial.print(id==result ? "<-": "  ");
//             Serial.println("//");
//             Serial.print(id==result ? "//                                  //\n": "");
//         }
//         Serial.println(F("//----------------------------------//"));
//         Serial.println();
//     }

//     Serial.println();
//   }
//   else Serial.println(F("Card read previously."));





//   // Halt PICC
//   rfid.PICC_HaltA();

//   // Stop encryption on PCD
//   rfid.PCD_StopCrypto1();
// }


// /**
//  * Helper routine to dump a byte array as hex values to Serial. 
//  */
// void printHex(byte *buffer, byte bufferSize) {
//   for (byte i = 0; i < bufferSize; i++) {
//     Serial.print(buffer[i] < 0x10 ? " 0" : " ");
//     Serial.print(buffer[i], HEX);
//   }
// }

// /**
//  * Helper routine to dump a byte array as dec values to Serial.
//  */
// void printDec(byte *buffer, byte bufferSize) {
//   for (byte i = 0; i < bufferSize; i++) {
//     Serial.print(buffer[i] < 0x10 ? " 0" : " ");
//     Serial.print(buffer[i], DEC);
//   }
// }


// void printCard(rfidCard *card)
// {
//     Serial.print("[");
//     Serial.print(card->cardID < 10 ? "0" : "");
//     Serial.print(card->cardID);
//     Serial.print("]");
//     Serial.print(" 0x");
//     Serial.print(card->nuid[0] < 0x10 ? "0" : "");
//     Serial.print(card->nuid[0], HEX);
//     Serial.print(" | 0x");
//     Serial.print(card->nuid[1] < 0x10 ? "0" : "");
//     Serial.print(card->nuid[1], HEX);
//     Serial.print(" | 0x");
//     Serial.print(card->nuid[2] < 0x10 ? "0" : "");
//     Serial.print(card->nuid[2], HEX);
//     Serial.print(" | 0x");
//     Serial.print(card->nuid[3] < 0x10 ? "0" : "");
//     Serial.print(card->nuid[3], HEX);
// }


// int getCardId(byte *nuid)
// {
//     for(int id =  0; id < counter; id++)
//     {
//         if(cards[id].nuid[0] == nuid[0] && cards[id].nuid[1] == nuid[1] && cards[id].nuid[2] == nuid[2] && cards[id].nuid[3] == nuid[3])
//             return id;
//     }
//     return -1;
// }