#ifndef LANDMARKS_H
#define LANDMARKS_H

typedef struct {
    char name[30];
    float latitude;
    float longitude;
} Landmark;

// Global landmark database (7 faculty halls)
extern Landmark landmarks[7];

#endif