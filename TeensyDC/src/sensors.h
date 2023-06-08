#define __SENSORS_H__
#ifdef __SENSORS_H__

void sensorSetup(int lineCount, void (*kick)());
void readPhotoTransistor();

#endif // __MOTORS_H__