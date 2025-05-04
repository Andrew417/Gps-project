#include "TM4C123_GH6PM_GPIO.h"
#include "TM4C123_GH6PM_UART.h"
#include "tm4c123gh6pm.h"
#include "string.h"
#include "stdint.h"
#include "math.h"

#define BUFFER_SIZE 256
#define GPS_BAUDRATE 9600  // Default NEO-6M baud rate

// GPS message identifiers
#define GGA_HEADER "$GPGGA"
#define RMC_HEADER "$GPRMC"

char gpsBuffer[BUFFER_SIZE] = {0};
volatile uint8_t bufferIndex = 0;
volatile uint8_t messageReady = 0;

typedef struct {
    float latitude;
    float longitude;
    uint8_t fix;
} GPS_Data;

GPS_Data currentGPS = {0.0, 0.0, 0};

void UART_Init(void) {
    // Enable clocks
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1; // UART1 for GPS
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // Port A for UART1
    
    // Wait for clocks to stabilize
    while((SYSCTL_PRUART_R & SYSCTL_PRUART_R1) == 0);
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0) == 0);

    // Disable UART during configuration
    UART1_CTL_R &= ~UART_CTL_UARTEN;
    
    // Configure baud rate (16MHz clock, 9600 baud)
    // IBRD = int(16,000,000 / (16 * 9600)) = 104
    // FBRD = round(0.1667 * 64) = 11
    UART1_IBRD_R = 104;
    UART1_FBRD_R = 11;
    
    // 8-bit word length, no parity, one stop bit, FIFOs enabled
    UART1_LCRH_R = UART_LCRH_WLEN_8 | UART_LCRH_FEN;
    
    // Enable UART, RX, and TX
    UART1_CTL_R |= UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE;
    
    // Configure GPIO pins
    GPIO_PORTA_AFSEL_R |= 0x03;       // Enable alternate function on PA0-1
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xFF) | 0x11; // UART1 on PA0-1
    GPIO_PORTA_DEN_R |= 0x03;         // Digital enable PA0-1
    GPIO_PORTA_AMSEL_R &= ~0x03;      // Disable analog on PA0-1
}

char UART_ReadChar(void) {
    while(UART1_FR_R & UART_FR_RXFE); // Wait until data is available
    return (char)(UART1_DR_R & 0xFF);
}

void UART_WriteChar(char c) {
    while(UART1_FR_R & UART_FR_TXFF); // Wait until TX FIFO has space
    UART1_DR_R = c;
}

void UART_WriteString(char *str) {
    while(*str) {
        UART_WriteChar(*str++);
    }
}

void parseGPSData(char *nmea) {
    char *token;
    char *rest = nmea;
    char nmeaType[7] = {0};
    
    // Get message type (first 6 characters)
    strncpy(nmeaType, nmea, 6);
    
    // Process GGA message (Global Positioning System Fix Data)
    if(strcmp(nmeaType, GGA_HEADER) == 0) {
        token = strtok_r(rest, ",", &rest); // $GPGGA
        token = strtok_r(NULL, ",", &rest); // UTC time
        token = strtok_r(NULL, ",", &rest); // Latitude
        
        if(token && strlen(token) > 0) {
            float lat = atof(token);
            token = strtok_r(NULL, ",", &rest); // N/S
            if(token[0] == 'S') lat = -lat;
            currentGPS.latitude = (int)(lat / 100) + fmod(lat, 100) / 60.0;
        }
        
        token = strtok_r(NULL, ",", &rest); // Longitude
        if(token && strlen(token) > 0) {
            float lon = atof(token);
            token = strtok_r(NULL, ",", &rest); // E/W
            if(token[0] == 'W') lon = -lon;
            currentGPS.longitude = (int)(lon / 100) + fmod(lon, 100) / 60.0;
        }
        
        token = strtok_r(NULL, ",", &rest); // Fix quality
        if(token) {
            currentGPS.fix = atoi(token);
        }
    }
    // Process RMC message (Recommended Minimum Navigation Information)
    else if(strcmp(nmeaType, RMC_HEADER) == 0) {
        token = strtok_r(rest, ",", &rest); // $GPRMC
        token = strtok_r(NULL, ",", &rest); // UTC time
        token = strtok_r(NULL, ",", &rest); // Status (A=active, V=void)
        
        if(token && token[0] == 'A') { // Only process if data is valid
            token = strtok_r(NULL, ",", &rest); // Latitude
            
            if(token && strlen(token) > 0) {
                float lat = atof(token);
                token = strtok_r(NULL, ",", &rest); // N/S
                if(token[0] == 'S') lat = -lat;
                currentGPS.latitude = (int)(lat / 100) + fmod(lat, 100) / 60.0;
            }
            
            token = strtok_r(NULL, ",", &rest); // Longitude
            if(token && strlen(token) > 0) {
                float lon = atof(token);
                token = strtok_r(NULL, ",", &rest); // E/W
                if(token[0] == 'W') lon = -lon;
                currentGPS.longitude = (int)(lon / 100) + fmod(lon, 100) / 60.0;
            }
            
            currentGPS.fix = 1; // RMC messages only come with valid data
        }
    }
}

void processGPSData(void) {
    char c;
    static uint8_t parsing = 0;
    
    while((UART1_FR_R & UART_FR_RXFE) == 0) { // While data is available
        c = UART_ReadChar();
        
        // Start of new message
        if(c == '$') {
            bufferIndex = 0;
            parsing = 1;
        }
        
        if(parsing) {
            // Store character if there's space
            if(bufferIndex < BUFFER_SIZE - 1) {
                gpsBuffer[bufferIndex++] = c;
            }
            
            // End of message
            if(c == '\n') {
                gpsBuffer[bufferIndex] = '\0'; // Null-terminate
                parseGPSData(gpsBuffer);
                parsing = 0;
                messageReady = 1;
            }
        }
    }
}

void printGPSData(void) {
    if(messageReady) {
        if(currentGPS.fix) {
            char buffer[50];
            sprintf(buffer, "Lat: %.6f, Lon: %.6f\r\n", 
                   currentGPS.latitude, currentGPS.longitude);
            UART_WriteString(buffer);
        } else {
            UART_WriteString("No GPS fix\r\n");
        }
        messageReady = 0;
    }
}

int main(void) {
    UART_Init();
    
    // Initialize debug UART (UART0 for output to PC)
    // ... (Add initialization for UART0 if you want to output to PC)
    
    UART_WriteString("GPS NEO-6M Parser Initialized\r\n");
    
    while(1) {
        processGPSData();
        printGPSData();
    }
}