// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADS1100
// This code is designed to work with the ADS1100_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1100_I2CADC#tabs-0-product_tabset-2

#include <Wire.h>

// ADS1100 I2C address is 0x48(72)
#define Addr 0x48

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Continuous conversion mode, 8 SPS, 1PGA
  Wire.write(0x0C);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[2];

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data
  float raw_adc = (data[0] * 256.0) + data[1];
  if (raw_adc > 32767)
  {
    raw_adc -= 65536;
  }

  // Output data to serial monitor
  Serial.print("Digital value of analog input : ");
  Serial.println(raw_adc);
  delay(500);
}
