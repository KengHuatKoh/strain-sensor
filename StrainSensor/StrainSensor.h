#ifndef StrainSensor_h
#define StrainSensor_h

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

class StrainSensor
{
	public:
    // Initialize a StrainSensor object, setting the input pin and moving average denominator n
    // maximum n=10
		StrainSensor(int pin, int numReadings);

    // Read the sensor: store current reading, calculate moving average
    // \return the voltage value 
    float readVoltage();

    // Read the estimated knee joint angle after calibration
    int16_t readAngle();

    // Set the current reading to become equivalent to sitting (90 deg knee joint)
    void angle90Calib();

    // Set the current reading to become equivalent to standing (0 deg knee joint)
    void angle0Calib();
    		
	private:
    float _linearMap(uint16_t x, uint16_t in_min, uint16_t in_max, float out_min, float out_max);
		int _pin;
		int _numReadings;
		const uint8_t _readingsSize = 10;
    uint16_t _readings[10];
		uint8_t _readIndex;
		uint16_t _total;
		uint16_t _average;
    uint16_t _min = 0;
    uint16_t _max = 1023;
};

#endif
