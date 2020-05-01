#include "StrainSensor.h"

StrainSensor::StrainSensor(int pin, int numReadings) {
	_pin = pin;
  if (numReadings >= _readingsSize) _numReadings = _readingsSize;
  else _numReadings = numReadings;
  for (int thisReading = 0; thisReading < _readingsSize; thisReading++) _readings[thisReading] = 0;
}

float StrainSensor::readVoltage() {
  _total = _total - _readings[_readIndex];
  _readings[_readIndex] = analogRead(_pin);
  _total = _total + _readings[_readIndex];
  _average = _total / (_numReadings * 1.0);
  _readIndex = _readIndex + 1;
  if (_readIndex >= _numReadings) _readIndex = 0;
  return _linearMap(_average, 0, 1023, 0, 5.0); 
}

int16_t StrainSensor::readAngle() {
  return (_average - _min) * (0 - 90) / (_max - _min) + 90;
}

void StrainSensor::angle90Calib( ){
  _min = _average;
}

void StrainSensor::angle0Calib() {
  _max = _average;
}

float StrainSensor::_linearMap(uint16_t x, uint16_t in_min, uint16_t in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
