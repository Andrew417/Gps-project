#include "Speaker.h"



void Speaker_PlayTrack(uint8_t track_num)
{
    // Volume command (max = 30)
    uint8_t vol_cmd[10] = {0x7E,0xFF,0x06,0x06,0x00,0x00,30,0x00,0x00,0xEF};
    
    // Play command (specific track)
    uint8_t play_cmd[10] = {0x7E,0xFF,0x06,0x03,0x00,0x00,track_num,0x00,0x00,0xEF};
			
    // Send volume command
    for(int i=0; i<10; i++)
		{
				UART_Outint(vol_cmd[i]);
       // while(UART0->FR & (1<<5));  // Wait if TX buffer full
       // UART0->DR = vol_cmd[i];     // Send byte
    }
    
    // Send play command
    for(int i=0; i<10; i++)
		{
				UART_Outint(play_cmd[i]);
        //while(UART0->FR & (1<<5));
        //UART0->DR = play_cmd[i];
    }
}