#include <SPI.h>
#include <LoRa.h>

// WIFI_LoRa_32 ports
// GPIO5  -- SX1278's SCK
// GPIO19 -- SX1278's MISO
// GPIO27 -- SX1278's MOSI
// GPIO18 -- SX1278's CS
// GPIO14 -- SX1278's RESET
// GPIO26 -- SX1278's IRQ(Interrupt Request)
#define LED_BUILTIN 2
#define SS      5
#define RST     14
#define DI0     26
int recipient; 
byte sender;
byte incomingMsgId;
byte incomingLength;

String incoming ;

void setup() {
  Serial.begin(115200);
  SPI.begin(18, 19, 23, 5);
  LoRa.setPins(SS, RST, DI0);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
   recipient = LoRa.read();          // recipient address
   sender = LoRa.read();            // sender address
   incomingMsgId = LoRa.read();     // incoming msg ID
   incomingLength = LoRa.read();    // incoming msg length
   incoming = "";
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
     }

    // print RSSI of packet
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
  
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
   
   
  }
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
  
