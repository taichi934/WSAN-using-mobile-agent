#include <RH_RF95.h>
#include <SPI.h>
#include <String.h>

float frequency = 920.0;  // Change the frequency here.

RH_RF95 rf95;

void setup() {
  Serial.begin(9600);

  if (!rf95.init()) {
    Serial.println(
        "LoRa module init failed, Please cehck hardware connection");
    while (1)
      ;
  }

  // Setup ISM frequency
  rf95.setFrequency(frequency);
  // Setup Power,dBm
  rf95.setTxPower(13);
  // Defaults BW Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  rf95.setSpreadingFactor(7); // default: 7

  Serial.print("Listening on frequency: ");
  Serial.print(frequency);
  Serial.print(" ");
}


void loop()
{
  if (rf95.available())
  {
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      if(buf[0] == 0 & buf[1] == 0 & buf[2] ==2) //Get sensor data from node id 001
      {
        // char nodeIdStr[50];
        // int nodeId;
        int motionNumber;
        for (int i = 0; i < 4; i++)
        {
          if(0 <= i && i <= 2) {
//            nodeIdStr[i] = buf[i];
//            if(i == 2)
//              nodeId =  atoi(nodeIdStr);
          } else {
            motionNumber = buf[i];
          }
        }
//        strncat(nodeIdStr, buf, 3);
//        nodeId = atoi(nodeIdStr);

        Serial.print("From node id = ");
//        Serial.print(nodeId);
        Serial.print(buf[0]);
        Serial.print(buf[1]);
        Serial.print(buf[2]);
        Serial.print(": ");
        Serial.print("Recieved motion number = ");
        Serial.println(motionNumber);


        // make result packet and send
//        uint8_t resultPacket[RH_RF95_MAX_MESSAGE_LEN];
//        int i = 0;
//        while(Serial.available() > 0){
//          resultPacket[i++] = Serial.read();
//        } 
//
//        rf95.send(resultPacket, sizeof(resultPacket));
        
      }
    }
    else
    {
        Serial.println("recv failed");
    }
  }
}
