#include <SPI.h>
#include <MFRC522.h> //download the library file
 
#define SS_PIN 10 //Slave pin refer https://www.arduino.cc/en/reference/SPI will change according to the dev Board used
#define RST_PIN 9 //ANY ADC pin will work in UNO 9
MFRC522 mfrc(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();   //Intialize serial Peripheral interconnection
  mfrc.PCD_Init();   // Initiate MFRC522 prebuilt function in the library
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc.uid.size; i++)  //READING the uid of the card 
  {
     Serial.print(mfrc.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc.uid.uidByte[i], HEX);
     content.concat(String(mfrc.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if (content.substring(1) == "ADD THE UID OF THE CARD THAT HAS TO BE ALLOWED") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("AUTHORIZED");
    Serial.println();
    delay(2000);
  }
 
 else   {
    Serial.println(" ACCESS DENIED");
    delay(2500);
  }
} 

//for connection refer the MOSI , MISO, SDA,SCK of the arduino Boards 
//Its different for different boards.




