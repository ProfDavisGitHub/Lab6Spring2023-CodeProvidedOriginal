#include "mbed.h"
#include "PinDetect.h"
// must import Cookbook PinDetct library into project
// URL: http://mbed.org/users/AjK/libraries/PinDetect/lkyxpw

DigitalOut myled(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

PinDetect pb1(p8);
PinDetect pb2(p7);
// SPST Pushbutton debounced count demo using interrupts and callback
// no external PullUp resistor needed
// Pushbutton from P8 to GND.
// Second Pushbutton from P7 to GND.
// A pb hit generates an interrupt and activates the callback function
// after the switch is debounced

// Global count variable
int volatile count=0;

// Callback routine is interrupt activated by a debounced pb1 hit
void pb1_hit_callback (void) {
    count++;
    myled4 = count & 0x01;
    myled3 = (count & 0x02)>>1;
    myled2 = (count & 0x04)>>2;
}
// Callback routine is interrupt activated by a debounced pb2 hit
void pb2_hit_callback (void) {
    count--;
    myled4 = count & 0x01;
    myled3 = (count & 0x02)>>1;
    myled2 = (count & 0x04)>>2;
}
int main() {

    // Use internal pullups for pushbutton
    pb1.mode(PullUp);    
    pb2.mode(PullUp);
    // Delay for initial pullup to take effect
    wait(.01);
    // Setup Interrupt callback functions for a pb hit
    pb1.attach_deasserted(&pb1_hit_callback);
    pb2.attach_deasserted(&pb2_hit_callback);
    // Start sampling pb inputs using interrupts
    pb1.setSampleFrequency();
    pb2.setSampleFrequency();
    //Blink myled in main routine forever while responding to pb changes
    // via interrupts that activate the callback counter function
    while (1) {
        myled = !myled;
        wait(.5);
    }

}