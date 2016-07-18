// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADS1100
// This code is designed to work with the ADS1100_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1100_I2CADC#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class ADS1100
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, ADS1100 I2C address is 0x48(72)
		I2CDevice device = Bus.getDevice(0x48);

		// Select configuration register
		// Continuous conversion mode, 8 SPS, 1 PGA
		device.write((byte)0x0C);
		Thread.sleep(500);

		// Read 2 bytes of data
		// raw_adc msb, raw_adc lsb
		byte[] data = new byte[2];
		device.read(data, 0, 2);

		// Convert the data
		int raw_adc = (data[0] * 256) + (data[1] & 0xFF);
		
		// Output data to screen
		System.out.printf("Digital Value of Analog Input : %d %n", raw_adc);
	}
}
