/* 2 MOISTURE SENSORS LOOPING ON AND OFF - sending value to serial monitor  

I Finally figured out what the digital pin is for - it's for controlling the sensor's state- this was obvious in 
hindhsight. Here the code uses the digital pin to control when and for how long the sensor
should be read from. IT prints the 12-bit values to the serial monitor.

I'm also seeing funkiness from the 2 sensors themsleves - sensor 1 hovers at 3000, while sensor 2 hoovers at 1550. 
The digital pin now my option to use these as states to track when the sensor has be turned on 
(I also now know what the led next to the power led is on the connector - it's not moisture levels) 

The next step is to understand the varying sensor readings and build on the system architecture and find a way to calibrate the 2 sensors

-- Taye. 

*/
#include <mbed.h>
#include <arm_book_lib.h>
#include <cstring>
#include <iostream>


// Sensor Pin Connection
AnalogIn moistureSensor(A1);   // Moisture sensor connected to A1 
DigitalOut sensorPower(D1);  // Digital Pin for Sensor 1 
AnalogIn moistureSensor2(A2); // Moisture Sensor 2 connected to A2 
DigitalOut sensorPower2(D2); // Digital Pin for Sensor 2  

// UART setup for Serial Communication
UnbufferedSerial pc(USBTX, USBRX, 115200);



// Serial Communication Function - The Function needed for the Nucleo to talk through the Serial Monitor 
void sendSerialMessage(const char* message){
    pc.write("\n", 1);  // Newline for better readability
    pc.write(message, strlen(message));  // Sends the message
    thread_sleep_for(2000); // Wait for 2 seconds before sending the next message
}

int main() {
    char buffer[50];
    pc.write("Moisture sensor reading started...\n", 34);

    while (1) { // While true - this will run for infinity 
        sensorPower = 1; // Signal sent to Digital Pin, Sensor can be read. 
        printf("Sensor One is ON\n");
        ThisThread::sleep_for(1000ms);

        float sensorValue = moistureSensor.read();  // Read analog value (0.0 - 1.0)
        int rawValue = sensorValue * 4095;  // Convert to raw 12-bit value

        sensorPower2 = 1;
        printf("Sensor Two is ON\n");
        ThisThread::sleep_for(1000ms);
        float sensorValue2 = moistureSensor2.read(); // Read Value of 2nd moisture Sensor 
        int rawValue2 = sensorValue2 * 4095; // Convert Raw to 12-bit value

        // Format and send the raw value
        int len = sprintf(buffer, "Sensor One (1) Value: %d\n", rawValue);
        pc.write(buffer, len);
        int len2 = sprintf(buffer, "Sensor Two (2) Value: %d\n", rawValue2);
        pc.write(buffer, len2);

        // Sending Signal to stop reading Moisture Sensors 
        sensorPower = 0;
        sensorPower2 = 0;  
        printf("Both Moisture Sensor are OFF. \n");
        ThisThread::sleep_for(5s);
    }
}