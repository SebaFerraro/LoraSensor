#include <SPI.h>
#include <LoRa.h>

// WIFI_LoRa_32 ports
// GPIO5  -- SX1278's SCK
// GPIO19 -- SX1278's MISO
// GPIO27 -- SX1278's MOSI
// GPIO18 -- SX1278's CS
// GPIO14 -- SX1278's RESET
// GPIO26 -- SX1278's IRQ(Interrupt Request)

#define SS      5
#define RST     14
#define DI0     26

int counter = 0;
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xAB;     // address of this device
byte destination = 0xFF;      
String outgoing="";

void setup() {
  Serial.begin(115200);
  SPI.begin(18, 19, 23, 5);
  LoRa.setPins(SS, RST, DI0);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
   outgoing="0000000000000000";
  // send packet
  LoRa.beginPacket();
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(counter);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);          
  //LoRa.print("hello ");
  //LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
