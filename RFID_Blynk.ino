
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <MFRC522.h>

char auth[] = "9ntV_TqtX5LaFwX7yfsQcL3sz_Mex4vV";
char ssid[] = "MBAHMUKIPER";
char pass[] = "ahhayas20";

#define SDA_PIN D2
#define RST_PIN D1

int virtual_State = 0;

MFRC522 mfrc522(SDA_PIN, RST_PIN); // Create MFRC522 instance.

WidgetLCD lcd(V1);

void setup() 
{
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  Blynk.begin(auth, ssid, pass);
  mfrc522.PCD_Init(); // Init MFRC522 card
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
       
void loop()   
{
  Blynk.run();
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();  
    
  if(content.substring(1) == "B9 9F AE B3") // UID kartu nya silahkan cocokan dengan kartu masing"
          {
            lcd.clear();
            lcd.print(0, 0, "Valid card");                                              // Print if card is TRUE
            lcd.print(0, 1, "Access Granted");
            delay(1000);      
          } 
         else if(content.substring(1) == "8F AA 2B 20") // UID kartu nya silahkan cocokan dengan kartu masing"
          {
            lcd.clear();
            lcd.print(0, 0, "Valid card");                                              // Print if card is TRUE
            lcd.print(0, 1, "Access Granted");
            delay(1000);      
          }
                          
          else
          {                  
            lcd.clear();
            lcd.print(0, 0, "Invalid card");                                   // Print if card is FALSE
            lcd.print(0, 1, "Access Denied");
          }                           
          
}   
