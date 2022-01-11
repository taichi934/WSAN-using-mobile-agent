#include <RH_RF95.h>
#include <SPI.h>
#include <String.h>

RH_RF95 rf95;
float frequency = 920.0;  // Change the frequency here.

void setup() {
  Serial.begin(9600);
  // Wait for serial port to be available
  while (!Serial)
    ;
  Serial.println("LoRa_Simple_Client");

  if (!rf95.init()) Serial.println("init failed");
  Serial.println("RH_RF95 initiated...\n\n");

  // Setup ISM frequency
  rf95.setFrequency(frequency);
  // Setup Power,dBm
  rf95.setTxPower(13);
  rf95.setSpreadingFactor(7);  // default:7
}

void loop() {
 
  if(Serial.available() > 0) {
    uint8_t data[RH_RF95_MAX_MESSAGE_LEN]; // RH_RF95_MAX_MESSAGE_LEN: 251
    // node id
    data[0] = 0;
    data[1] = 0;
    data[2] = 2;

    // motion number
    
    uint8_t motionNumber = Serial.read();
//     byte motionNumber = Serial.read();
//     motionNumber = motionNumber - 0x30;  // (0x30 =  0)
    data[3] = motionNumber;

    rf95.send(data, sizeof(data));
    
    Serial.print("Sending: ");
    for(int i = 0; i < 4; i++) {
      Serial.print(data[i]);
    }
    Serial.println("");

    delay(2000);
  }

  // recieve result packet
//  if(rf95.available()){
//    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
//    uint8_t len = sizeof(buf);
//    if (rf95.recv(buf, &len)){
//      Serial.println(buf[3]);
//    }
//  }
}
