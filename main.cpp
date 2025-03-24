/* Hi - For this code, I wanted to finally get the Serial Commiunication working - and I did!
A mix of making sure <cstring> is defined and creating the Serial Communication Function. With the Serial Monitor working
I can now confidently see activity from the Nucleo and can now begin testing and creating test codes for the component and 
Moisture Sensor Sub-System.

The sensor check is on a continous loop and the threshold are set low enough for easy triggering and alert to the Serial Monitor

The next step is to get functional Moisture Sensor reading, build are realistic function of operation and build the moisture sensor sub-system. 

for whatever reason - strlen is stil marked as red and undeclared, even with <cstring> and the code still builds and functions as expected. I don't know why, maybe IDE?- Taye*/

#include <mbed.h>
#include <arm_book_lib.h>
#include <cstring>// This is needed for Serial Communication to work pc.write(message) and strlen - Taye :)
#include <iostream>

// Sensors Pin Connections 
AnalogIn moistureSensor1(PA_0);   // Moisture sensor for Plant A
DigitalIn moistureSensor1_D(D1);   // Moisture sensor for Plant A (Not needed for this test code)

// UART setup for Serial Communication 
UnbufferedSerial pc(USBTX, USBRX, 115200);

// Serial Communication Function - The Function needed for the Nucleo to talk through the Serial Monitor 
void sendSerialMessage(const char* message) {
    pc.write("\n", 1);  // Newline for better readability
    pc.write(message, strlen(message));  // Sends the message
    thread_sleep_for(2000); // Wait for 2 seconds before sending the next message
}

// Thresholds for Moisture Levels 
#define MOISTURE_THRESHOLD_1 0.5  

// Function Prototypes
void checkMoistureSensors();

//Main Loop
int main() {
        // Start reading moisture on a continuous loop - this is not at all what final function will be - but for test purposes, I want to see continuous readings 
    while (true) {
    void checkMoistureSensors();
        thread_sleep_for(1000);  // Delay of 1 second between checks
        float moistureValue = moistureSensor1.read();  // Read raw value (0.0 to 1.0)
        char buffer[50];  // Create a buffer to hold the value
        sprintf(buffer, "Moisture Value: %.2f", moistureValue);
        sendSerialMessage(buffer);  // Send the value 
    
        if (moistureValue < MOISTURE_THRESHOLD_1) {
            sendSerialMessage("Plant A Needs Water");
    }
}

}