#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include "basic_gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TRAFFIC_LIGHT_TIME_Sec              7

#define PEDESTRIANS_TRAFFIC_LIGHT_PORT      PORTD
#define PEDESTRIANS_RED_LIGHT_PIN           Pin_0
#define PEDESTRIANS_GREEN_LIGHT_PIN         Pin_2

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum{
    RED=0, YELLOW=1, GREEN=2, 
}Traffic_Light_Color;

typedef enum{
    VEHICLE_LIGHTS, PEDESTRIAN_LIGHTS
}Traffic_Light_Type;

/*******************************************************************************
 *                              Global variables                               *
 *******************************************************************************/
/* the current color of the vehicles traffic light */
extern Traffic_Light_Color vehicle_traffic_light_color;

/* the previous color of the vehicles traffic light, will be used to determine
      whether to go Red or Green */
extern Traffic_Light_Color prev_vehicle_traffic_light_color;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* A function to configure the builtin LEDs (representing the vehicles traffic light) */
void configure_vehicle_traffic_light(void);

/* A function to configure 2 pins in a configurable port as output pins */
void configure_pedestrian_traffic_light(void);

/* A function to configure user-switch 1 in port F, 
    enabling falling-edge interrupt detecting */
void configure_request_button(void);

/* A function to configure SysTick timer with interrupts */
void configure_application_timer(void);

void enable_application_timer(void);

/* A function to switch/change the traffic light state/color
    it takes 2 parameters:
        1. which traffic light (for vehicles or pedestrians),
        2. what color(state) to set */
void switch_traffic_light_state(Traffic_Light_Type type, Traffic_Light_Color color);

/* the function is volatile because it's the SysTick handler & makes changes to output pins  */
void volatile update_traffic_lights(void);

#endif /* _APPLICATION_H_ */