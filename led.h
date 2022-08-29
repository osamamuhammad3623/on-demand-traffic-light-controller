#ifndef _BUILTIN_LED_H_
#define _BUILTIN_LED_H_


typedef enum {
    RED_LED=1, BLUE_LED=2, GREEN_LED=3, YELLOW_LED
}LED_Color;

/*
 * Description: Configure a specific internal LED
 *      1.make the pin an output pin
 *      2.no alternate function
 *      3.digital enable
 *      4.clear data register
 * */
void LED_Configure(LED_Color color);

/* A function to configure yellow color as it's not a builtin LED in Tiva C */
void LED_Configure_Yellow(void);

/*
 *Description: enable only a specific LED [other LEDs are disabled]
 * */
void LED_Enable(LED_Color color);

/*
 *Description: toggle the LED
 * */
void LED_Toggle(LED_Color color);

/*
 * Description: disable all LEDs
 * */
void LED_Disable(void);

#endif /* BUILTIN_LED_H_ */
