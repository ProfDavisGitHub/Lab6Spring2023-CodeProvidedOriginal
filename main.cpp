// skeleton code for ECE 2036 thermostat lab
// code must be added by students
#include "mbed.h"
#include "TMP36.h"
#include "SDFileSystem.h"
#include "TextLCD.h"
#include "PinDetect.h"
#include "Speaker.h"
// must add your new class code to the project file Shiftbrite.h
#include "Shiftbrite.h"

// use class to setup temperature sensor pins
TMP36 myTMP36(p15);  //Analog in

// use class to setup microSD card filesystem
SDFileSystem sd(p5, p6, p7, p8, "sd");

// use class to setup the LCD
TextLCD myLCD(p22, p23, p24, p25, p26, p27); // rs, e, d4-d7

// use class to setup pushbuttons pins
PinDetect pb1(p28);
PinDetect pb2(p29);
PinDetect pb3(p30);

// use class to setup speaker pin
Speaker mySpeaker(p21); //PWM out

// use class to setup Shiftbrite pins
Shiftbrite myShiftbrite(p9, p10, p11, p12, p13);// ei li di n/c ci

// use class to setup Mbed's four on-board LEDs
DigitalOut myLED1(LED1);
DigitalOut myLED2(LED2);
DigitalOut myLED3(LED3);
DigitalOut myLED4(LED4);

// heat or code mode jumper - removed when pushbuttons added
DigitalIn jumper_wire(p14);

//also setting any unused analog input pins to digital outputs reduces A/D noise a bit
//see http://mbed.org/users/chris/notebook/Getting-best-ADC-performance/
DigitalOut P16(p16);
DigitalOut P17(p17);
DigitalOut P18(p18);
DigitalOut P19(p19);
DigitalOut P20(p20);




// Global variables used in callbacks and main program
// C variables in interrupt routines should use volatile keyword
int volatile heat_setting=78; // heat to temp
int volatile cool_setting=68; // cool to temp
bool volatile mode=false; // heat or cool mpde

// Callback routine is interrupt activated by a debounced pb1 hit
void pb1_hit_callback (void)
{
// ADD CODE HERE
}
// Callback routine is interrupt activated by a debounced pb2 hit
void pb2_hit_callback (void)
{
// ADD CODE HERE
}
// Callback routine is interrupt activated by a debounced pb3 hit
void pb3_hit_callback (void)
{
// ADD CODE HERE
}


int main()
{
    float Current_temp=0.0;

    // Use internal pullups for the three pushbuttons
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    // Delay for initial pullup to take effect
    wait(.01);
    // Setup Interrupt callback functions for a pb hit
    pb1.attach_deasserted(&pb1_hit_callback);
    pb2.attach_deasserted(&pb2_hit_callback);
    pb3.attach_deasserted(&pb2_hit_callback);
    // Start sampling pb inputs using interrupts
    pb1.setSampleFrequency();
    pb2.setSampleFrequency();
    pb2.setSampleFrequency();
    // pushbuttons now setup and running


    // start I/O examples - DELETE THIS IN YOUR CODE..BUT WILL USE THESE I/O IDEAS ELSEWHERE
    // since all this compiles - the needed *.h files for these are in the project
    //
    Current_temp = myTMP36;
    printf("Hello PC World\n\r"); // need terminal application running on PC to see this
    myLCD.printf("Hello LCD World"); // LCD
    mySpeaker.PlayNote(500.0, 1.0, 1.0); // Speaker buzz
    myShiftbrite.write( 0, 50 ,0); // Green RGB LED
    // SD card write file example - prints error message on PC when running until SD card hooked up
    FILE *fp = fopen("/sd/mydir/sdtest.txt", "w"); //open SD
    if(fp == NULL) {
        error("Could not open file for write\n");
    }
    fprintf(fp, "Hello SD Card World!"); // write SD
    fclose(fp); // close SD card
    //
    // end I/O examples




    // State machine code below will need changes
    while (1) {
        {
            enum Statetype { Heat_off = 0, Heat_on };
            Statetype state = Heat_off;
            while(1) {
                switch (state) {
                    case Heat_off:
                        myLED2 = 0;
                        state = Heat_on;
                        break;
                    case Heat_on:
                        myLED2 = 1;
                        state = Heat_off;
                        break;
                }
                wait(0.33);
            }
        }
    }
}