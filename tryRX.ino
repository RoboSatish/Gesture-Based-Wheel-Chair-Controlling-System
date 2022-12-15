#include <VirtualWire.h>
int SensorData; // Sensors
char SensorCharMsg[5]; // RF Transmission container
const int led1 = 2;
void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);

  // VirtualWire
  // Initialise the IO and ISR
  // Required for DR3100
  vw_set_ptt_inverted(true);
  // Bits per sec
  vw_setup(2000);
  // Start the receiver PLL running
  vw_rx_start();
} // END void setup

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  // Non-blocking
  if (vw_get_message(buf, &buflen))
  {
    int i;
    // Message with a good checksum received, dump it.
    for (i = 0; i < buflen; i++)
    {
      // Fill SensorCharMsg Char array with corresponding
      // chars from buffer.
      SensorCharMsg[i] = char(buf[i]);
    }
    // Null terminate the char array
    // This needs to be done otherwise problems will occur
    // when the incoming messages has less digits than the
    // one before.
    SensorCharMsg[buflen] = '\0';
    // Convert Sensor1CharMsg Char array to integer
    SensorData = atoi(SensorCharMsg);
    // DEBUG
    Serial.print("Sensor  ");
    Serial.println(SensorData);
    // END DEBUG
  }
  if (SensorData >= 1000)
  {
    digitalWrite(2, HIGH);
    delay(2000);
    
  }

  else
  {
    digitalWrite(2, LOW);
    delay(1000);
  }
}
