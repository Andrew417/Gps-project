#ifndef DISTANCE_H
#define DISTANCE_H

#include "gps.h"
#include "landmark.h"

float CalculateDistance(GPS_Data current, Landmark landmark);
const char* FindNearestLandmark(GPS_Data current);

#endif  