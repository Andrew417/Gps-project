#include "distance.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Haversine formula (returns distance in meters)
float CalculateDistance(GPS_Data current, Landmark landmark) {
    float lat1 = current.latitude * M_PI / 180.0;
    float lon1 = current.longitude * M_PI / 180.0;
    float lat2 = landmark.latitude * M_PI / 180.0;
    float lon2 = landmark.longitude * M_PI / 180.0;

    float dlat = lat2 - lat1;
    float dlon = lon2 - lon1;

    float a = sin(dlat/2) * sin(dlat/2) + 
              cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    return 6371000 * c; // Earth raduis in meters
}

// Find the nearest landmark
const char* FindNearestLandmark(GPS_Data current) {
    float min_dist = INFINITY;
    int nearest_idx = 0;

    for (int i = 0; i < 5; i++) {
        float dist = CalculateDistance(current, landmarks[i]);
        if (dist < min_dist) {
            min_dist = dist;
            nearest_idx = i;
        }
    }
    return landmarks[nearest_idx].name;
}