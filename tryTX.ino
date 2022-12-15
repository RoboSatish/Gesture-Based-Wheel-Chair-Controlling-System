#include <VirtualWire.h>
const int SensorPin = A2; // potentiometer pin
int SensorData;
char SensorCharMsg[5]; 
void setup() 
{
 pinMode(SensorPin,INPUT);
 Serial.begin(9600); 
 vw_setup(2000);     // Bits per sec
}
void loop() 
{
  
  SensorData = analogRead(SensorPin);
  // Convert integer data to Char array directly 
  itoa(SensorData,SensorCharMsg,10);
  // DEBUG
  Serial.print("Sensor Integer: ");
  Serial.print(SensorData);  // print the sensor data
  Serial.print(" Sensor CharMsg: ");
  Serial.print(SensorCharMsg);  //print the char array
  Serial.println(" ");
  delay(100);
  // END DEBUG
 vw_send((uint8_t *)SensorCharMsg, strlen(SensorCharMsg));  // send the message
 vw_wait_tx(); // Wait until the whole message is gone
 delay(200);  
} // END 
