#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include "basic_gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ITERATIONS_PER_MILLISECOND          762
#define TRAFFIC_LIGHT_TIME_mSec             5000

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
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* A function to configure the pins 0:2 in port B as output pins */
/* 
pin 0: Red light, 
pin 1: Yellow light, 
pin 2: Green light */
void configure_vehicle_traffic_light();

/* A function to configure the pins 0:2 in port D as output pins */
/* 
pin 0: Red light, 
pin 1: Yellow light, 
pin 2: Green light */
void configure_pedestrian_traffic_light();

/* A function to configure user-switch 1 in port F, 
    enabling falling-edge interrupt detecting */
void configure_request_button();

/* A function to switch/change the traffic light state/color
    it takes 2 parameters:
        1. which traffic light (for vehicles or pedestrians),
        2. what color(state) to set */
void switch_traffic_light_state(Traffic_Light_Type type, Traffic_Light_Color color);

/* the function is volatile because it's the SysTick handler & makes changes to output pins  */
void volatile update_traffic_lights(void);

#endif /* _APPLICATION_H_ */