#include "mbed.h"
#include "PinDetect.h"
// must import Cookbook PinDetct library into project
// URL: http://mbed.org/users/AjK/libraries/PinDetect/lkyxpw

DigitalOut myled(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

PinDetect pb(p8);
// SPST Pushbutton debounced count demo using interrupts and callback
// no external PullUp resistor needed
// Pushbutton from P8 to GND.
// A pb hit generates an interrupt and activates the callback function
// after the switch is debounced

// Global count variable
int volatile count=0;

// Callback routine is interrupt activated by a debounced pb hit
void pb_hit_callback (void) {
    count++;
    myled4 = count & 0x01;
    myled3 = (count & 0x02)>>1;
    myled2 = (count & 0x04)>>2;
}
int main() {

    // Use internal pullup for pushbutton
    pb.mode(PullUp);
    // Delay for initial pullup to take effect
    wait(.01);
    // Setup Interrupt callback function for a pb hit
    pb.attach_deasserted(&pb_hit_callback);
    // Start sampling pb input using interrupts
    pb.setSampleFrequency();

    //Blink myled in main routine forever while responding to pb changes
    // via interrupts that activate the callback counter function
    while (1) {
        myled = !myled;
        wait(.5);
    }

}