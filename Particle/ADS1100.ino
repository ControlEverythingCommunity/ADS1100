// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADS1100
// This code is designed to work with the ADS1100_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1100_I2CADC#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// ADS1100 I2C address is 0x48(72)
#define Addr 0x48

float raw_adc = 0.0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "ADS1100");
  Particle.variable("raw_adc", raw_adc);

  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Continuous conversion mode, 8 SPS, 1PGA
  Wire.write(0x8C);
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
  raw_adc = (data[0] * 256.0) + data[1];
  if (raw_adc > 32767)
  {
    raw_adc -= 65536;
  }
  
  // Output data to dashboard
  Particle.publish("Digital value of analog input :", String(raw_adc));
  delay(500);
}
