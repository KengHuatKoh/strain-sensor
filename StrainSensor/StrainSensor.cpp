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
  _myBuffer = _linearMapA(_average, 0, 1023, 0, 5.0); 
  return _myBuffer;
}

int16_t StrainSensor::readAngle() {
  _myTurningpoint = 0.2 * (_myMax - _myMin) + _myMin;
  if (_myBuffer < _myTurningpoint) 
  return _linearMapB(_myBuffer, _myMin, _myTurningpoint, 110, 155);
  else 
  return _linearMapB(_myBuffer, _myTurningpoint, _myMax, 155, 180);
}

void StrainSensor::angle90Calib( ){
  _myMin = _myBuffer;
}

void StrainSensor::angle180Calib() {
  _myMax = _myBuffer;
}

float StrainSensor::_linearMapA(uint16_t x, uint16_t in_min, uint16_t in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int16_t StrainSensor::_linearMapB(float x, float in_min, float in_max, uint16_t out_min, uint16_t out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
