#include "GPS.h"

//----------------------------
//Global Variables
//----------------------------
const double EARTH_RADIUS = 6371000;
uint16_t Inv_read = 0;
uint16_t dist = 50;
uint8_t Initial_Valid = 0;

//GPS Message Example
//$GPRMC,194453.00,A,3017.75041,N,03144.32030,E,0.031,,220425,,,A*7D
//$GPRMC,,V,,,,,,,,,,N*53
//$GPRMC,182710.27,V,,,,,,,,,,N*75


//----------------------------
//Saved Regions
//----------------------------
S_Landmark landmarks[Landmarks_Number] = {
    
		{"Hall A", 30.06414306, 31.28019695},
    {"Hall C", 30.06364748, 31.28043102},
    {"Large Field", 30.06377145, 31.27950216},
    {"Credit building", 30.06341296, 31.278245681},
    {"Student Affairs", 30.06509733, 31.27863045},
    {"library", 30.06525677, 31.28019831},
    {"Loban WSHP", 30.06320738, 31.27940831},
		{"Mina's Home", 30.2504197, 31.4836571}
};



void GPS_Get_Current_location(S_Location* location)
{
	
	
	// Pointers for parsing latitude and longitude
	char lat_str[20], lon_str[20];
	char Message_Buffer[80];					//Buffer that holds GPS message
	
	
	//Get GPS message using UART 
	while(GPS_Get_message(Message_Buffer) != 1);	
	

	if(Message_Buffer[8] == 'V' || 	Message_Buffer[17] == 'V' )
	{	
		
		//Increment No. of invalid readings
		Inv_read++;
		
		
		//Comes from vaild mode
		if(Initial_Valid == 0)
		{
			if(Inv_read == 1)
			{
				
				//Write on LCD no of Invalids
				lcd_cmd(LCD_CLEAR_SCREEN);
				lcd_cmd(LCD_BEGIN_AT_FIRST_ROW);
				lcd_string("Invalid Reading");
		
				lcd_cmd(LCD_BEGIN_AT_SECOND_ROW);
				lcd_string("Invalids:");
				LCD_Print_int(Inv_read);
				
				
				
			}
			else if((Inv_read > 1))
			{
				//Up number on LCD
				lcd_cmd(LCD_BEGIN_AT_SECOND_ROW);
				for(uint8_t i = 0;  i < 9; i++)
				{
					lcd_cmd(LCD_MOVE_CURSOR_RIGHT);
				}
				LCD_Print_int(Inv_read);
				
			}
		}
		else
		{
			lcd_cmd(LCD_BEGIN_AT_SECOND_ROW);
			for(uint8_t j = 0; j < 16; j++)
			{
				lcd_cmd(LCD_MOVE_CURSOR_RIGHT);
			}
			lcd_data('*');
		}
		
	}
	else //(Message_Buffer[18] == 'A') Vaild reading
	{
		
		//Reset Number of Invaild readings
		Inv_read = 0;
		Initial_Valid = 1;
		
		//Find the latitude field after third comma
    char *lat_ptr = strstr(Message_Buffer, ",") + 1; 
    lat_ptr = strstr(lat_ptr, ",") + 1; 
    lat_ptr = strstr(lat_ptr, ",") + 1; 

		 //Extract latitude 
    strncpy(lat_str, lat_ptr, 9);
    lat_str[9] = '\0'; // Null-terminate the string
		
		
		 //Find the longitude field
    char *lon_ptr = strstr(lat_ptr, ",") + 1; 
    lon_ptr = strstr(lon_ptr, ",") + 1; 
		
		// Extract longitude
    strncpy(lon_str, lon_ptr, 9);
    lon_str[9] = '\0'; // Null-terminate the string

		
		////Convert the strings to float (((NMEA Format)))
    location->Longitude = atof(lon_str);
    location->Latitude = atof(lat_str);		
		
		//Compare Current location's longitude and Latitude with Landmarks
		GPS_Set_Landmark(location);

	}
	
}


//compares current location longitude & latitude 
//Sets location datatype variable landmark element
void GPS_Set_Landmark(S_Location* location) 
{

		location->Longitude = floorf(location->Longitude/100) + fmodf(location->Longitude,100)/60;
		location->Latitude = floorf(location->Latitude/100) + fmodf(location->Latitude,100)/60; 
	
    float lat1 = location->Latitude * pi / 180.0;
    float lon1 = location->Longitude * pi / 180.0;
    float min_dist = MAX_DIST;
    int nearest_idx = 0;
	
    for (int i = 0; i < Landmarks_Number; i++) {
        // Convert landmark location to radians
        float lat2 = landmarks[i].Latitude * pi / 180.0;
        float lon2 = landmarks[i].Longitude * pi / 180.0;
        float dlat = lat2 - lat1;
        float dlon = lon2 - lon1;

        // Haversine formula
        float a = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
        float c = 2 * atan2(sqrt(a), sqrt(1-a));
        dist = EARTH_RADIUS * c;  


        if (dist < min_dist) {
            min_dist = dist;
            nearest_idx = i;
        }
	
    }
		strncpy(location->Region, landmarks[nearest_idx].name, sizeof(location->Region) - 1);
    location->Region[sizeof(location->Region) - 1] = '\0'; // Ensure null-termination
		location->Region_Index = nearest_idx;
		location->distance = (uint16_t)min_dist;

}

float CalculateDistance(S_Location* current, S_Landmark* landmark) {
    float lat1 = current->Latitude * pi / 180.0;
    float lon1 = current->Longitude * pi / 180.0;
    float lat2 = landmark->Latitude * pi / 180.0;
    float lon2 = landmark->Longitude * pi / 180.0;

    float dlat = lat2 - lat1;
    float dlon = lon2 - lon1;

    float a = sin(dlat/2) * sin(dlat/2) + 
              cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    return 6371000 * c; // Earth raduis in meters
}

// Find the nearest landmark
const char* FindNearestLandmark(S_Location* current) {
    float min_dist = MAX_DIST;
    int nearest_idx = 0;

    for (int i = 0; i < 5; i++) {
        float dist = CalculateDistance(current, &landmarks[i]);
        if (dist < min_dist) {
            min_dist = dist;
            nearest_idx = i;
        }
    }
    return landmarks[nearest_idx].name;
}

uint8_t GPS_Get_message(char *buffer)
{
		uint8_t cor_msg = 0;
		char character ;
		for (uint8_t i=0;i< Message_Size ; i++)
		{
			character =UART_InChar();
			if ((character !='*'))		//'*' is the terminatiing character of GPS message
			{
				if(i < 3) 
				{
					buffer[i]=character;
				}
				else if(((i == 3) && (character == 'R')) || (cor_msg == 1))
				{
					buffer[i]=character;
					cor_msg = 1;
				}
				else
				{
					return 0;
				}
				
			}
		 else
				 break;
		}
		
		return cor_msg;
}



void GPS_Display_region(S_Location* location)
{
	
	lcd_cmd(LCD_CLEAR_SCREEN);
	lcd_cmd(LCD_BEGIN_AT_FIRST_ROW);
	lcd_string("Current Location");
	lcd_cmd(LCD_BEGIN_AT_SECOND_ROW);
	lcd_string(location->Region);
	
}

void GPS_UpdateLED(uint16_t distance)
{
    if (distance < 30)
		{
				ClearBit(GPIO_PORTF_DATA_R, LED_RED);
				ClearBit(GPIO_PORTF_DATA_R, LED_GREEN);
				ClearBit(GPIO_PORTF_DATA_R, LED_BLUE);
			
        GPIO_PORTF_DATA_R |= (1 << 3);  // Green
    } 
		else if ((distance > 30) && (distance <= 50))
		{
				ClearBit(GPIO_PORTF_DATA_R, LED_RED);
				ClearBit(GPIO_PORTF_DATA_R, LED_GREEN);
				ClearBit(GPIO_PORTF_DATA_R, LED_BLUE);
			
        GPIO_PORTF_DATA_R = (1 << 3) | (1 << 1);  // Yellow (Green + Red)
    } 
		else
		{
				ClearBit(GPIO_PORTF_DATA_R, LED_RED);
				ClearBit(GPIO_PORTF_DATA_R, LED_GREEN);
				ClearBit(GPIO_PORTF_DATA_R, LED_BLUE);
        GPIO_PORTF_DATA_R = (1 << 1);  // Red
    }
 }
