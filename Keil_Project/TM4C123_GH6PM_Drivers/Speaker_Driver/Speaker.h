#ifndef SPEAKER_H_
#define SPEAKER_H_

#include "stdlib.h"
#include "TM4C123_GH6PM_UART.h"


#define Hall_A									(1)
#define Hall_C									(2)
#define	Large_Field							(3)
#define Credit_building					(4)
#define Student_Affairs_Office	(5)
#define Library									(6)
#define Loban_WSHP							(7)
#define No_location							(8)

void Speaker_PlayTrack(uint8_t track_num);




#endif 