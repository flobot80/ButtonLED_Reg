// This application uses button 1 and LED 1
// The operation is such that if you press the left button, as long as you keep the button pressed,
// the LED is on. As soon as you release the button, LED is off and stays off until the button is pressed again.
// This example use memory-mapped registers to communicate with GPIO peripherals.

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// According to the schematics on page 37 of the Launchpad user guide,
// left button (button 1) is connected to pin 1 (bit1)
#define LEFT_BUTTON BIT1

// According to the schematics on page 37 of the Launchpad user guide,
// left LED (LED 1) is connected to pin 0 (bit0)
#define LEFT_LED BIT0

// According to the schematics on page 37 of the Launchpad user guide,
// When a button is pressed, it is grounded (logic 0)
#define PRESSED 0

// This function initializes all the peripherals
void initialize();

int main(void)
{

    initialize();
    while (1) {
        // If the button is not pressed, keep the LED off
        if ((P1IN & LEFT_BUTTON) != PRESSED)
            P1OUT = P1OUT & ~LEFT_LED;

        // otherwise, turn the LED on
        else
            P1OUT = P1OUT |  LEFT_LED;
    }
}

void initialize()
{

    // step 1: Stop watchdog timer
    // We do this at the beginning of all our programs for now.Later we learn more about it.
    WDT_A_hold(WDT_A_BASE);

    // step 2: Initializing LED1
    // According to table 12.1 on page 678 of MSP432 User guide,
    // to create an output, all you need is to write a 1 to PxDIR for the specific bit you want
    // A common mistake is to write P1DIR = LEFT_LED instead of P1DIR |= LEFT_LED;
    P1DIR |= LEFT_LED;  // Same as P1DIR = P1DIR | LEFT_LED;


    // step 3: Initializing S1 (switch 1 or button 1)
    // According to the table on page 678 of MSP432 User guide,
    // to create an input with pull-up resistor, you need to do three things

    // step 3.1: write a 0 to PxDIR for the specific bit you want
    P1DIR &= ~LEFT_BUTTON;

    // step 3.2: write a 1 to PxREB for the specific bit you want
    P1REN |= LEFT_BUTTON;

    // step 3.3: write a 1 to PxOUT for the specific bit you want
    P1OUT |= LEFT_BUTTON;  // select pull-up
}
