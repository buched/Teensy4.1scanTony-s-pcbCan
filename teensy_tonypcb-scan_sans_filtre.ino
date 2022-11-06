#include <FlexCAN_T4.h>
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> K_Bus;    //Tractor / Control Bus
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> ISO_Bus;  //ISO Bus
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> V_Bus;    //Steering Valve Bus
CAN_message_t msg;

#define STEERSW_PIN 6 //PD6

void setup(void) {
  K_Bus.begin();
  K_Bus.setBaudRate(250000);
  ISO_Bus.begin();
  ISO_Bus.setBaudRate(250000);
  V_Bus.begin();
  V_Bus.setBaudRate(250000);
  Serial.print("3 bus ready");
  pinMode(STEERSW_PIN, INPUT_PULLUP); 
}

void loop() {
if(!digitalRead(STEERSW_PIN))                    // If pin 2 is low, read receive buffer
    {
      if ( K_Bus.read(msg) ) {
        Serial.print("Kbus;"); 
        Serial.print("MB;"); Serial.print(msg.mb);
        Serial.print("ID;0x"); Serial.print(msg.id, HEX);
        Serial.print(" DATA;");
        for ( uint8_t i = 0; i < 8; i++ ) {
          Serial.print(msg.buf[i]); Serial.print(";");
        }
        Serial.println("");
      }
      else if ( ISO_Bus.read(msg) ) {
        Serial.print("Isobus;"); 
        Serial.print("MB;"); Serial.print(msg.mb);
        Serial.print("ID;0x"); Serial.print(msg.id, HEX);
        Serial.print(" DATA;");
        for ( uint8_t i = 0; i < 8; i++ ) {
          Serial.print(msg.buf[i]); Serial.print(" ");
        }
        Serial.println("");
      }
      else if ( V_Bus.read(msg) ) {
        Serial.print("valvebus;"); 
        Serial.print("MB;"); Serial.print(msg.mb);
        Serial.print("ID;0x"); Serial.print(msg.id, HEX);
        Serial.print(" DATA;");
        for ( uint8_t i = 0; i < 8; i++ ) {
          Serial.print(msg.buf[i]); Serial.print(" ");
        }
      Serial.println("");
      }
    }
}
