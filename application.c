#include<stdint.h>
#include "basic_gpio.h"
#include "application.h"
#include "common_macros.h"
#include "tm4c123gh6pm.h"

Traffic_Light_Color vehicle_traffic_light_color=YELLOW;
Traffic_Light_Color prev_vehicle_traffic_light_color=GREEN;

void configure_vehicle_traffic_light(){
    /* configuring Pins 0, 1 and 2 in PORT B */
    for (int i=0; i< 3; i++){
        GPIO_Configuration vehicle_traffic_leds={
            PORTB,
            i, /* pin number */
            LOGIC_LOW,
            Digital_Pin,
            GPIO,
            Output_Pin,
            Disable_internal_resistor
        };
        GPIO_init(&vehicle_traffic_leds);
    }
}

void configure_pedestrian_traffic_light(){
    /* configuring Pins 0, 1 and 2 in PORT D */
    for (int i=0; i< 3; i++){
        GPIO_Configuration pedestrian_traffic_leds={
            PORTD,
            i,
            LOGIC_LOW,
            Digital_Pin,
            GPIO,
            Output_Pin,
            Disable_internal_resistor
        };
        GPIO_init(&pedestrian_traffic_leds);
    }
}

void GPIOF_Handler(void){
    CLEAR_BIT(GPIO_PORTF_ICR_R, Pin_4); /* clear interrupt flag */
    if (vehicle_traffic_light_color == RED){
        return;
    }

    switch_traffic_light_state(VEHICLE_LIGHTS, YELLOW);
    switch_traffic_light_state(PEDESTRIAN_LIGHTS, YELLOW);
    vehicle_traffic_light_color = YELLOW;
    prev_vehicle_traffic_light_color = GREEN;
    
    NVIC_ST_CURRENT_R = 0;/* reset systick timer count */
}

void configure_request_button(){
    GPIO_Configuration push_btn={
        PORTF,
        Pin_4,
        LOGIC_LOW,
        Digital_Pin,
        GPIO,
        Input_Pin,
        Pull_up_resistor
    };

    GPIO_init(&push_btn);

    CLEAR_BIT(GPIO_PORTF_IS_R, Pin_4); /* pin is edge-sensitive */
    CLEAR_BIT(GPIO_PORTF_IBE_R,Pin_4); /* disable both edges detection */
    CLEAR_BIT(GPIO_PORTF_IEV_R, Pin_4); /* falling-edge detection */
    CLEAR_BIT(GPIO_PORTF_ICR_R, Pin_4); /* clear prior interrupts */
    SET_BIT(GPIO_PORTF_IM_R, Pin_4); /* enable arm interrupt (module int) */
    SET_BIT(NVIC_EN1_R, 14); /* allow NVIC to activate/process the interrupt coming from PORT F */
}

void switch_traffic_light_state(Traffic_Light_Type type, Traffic_Light_Color color){
    if (type == VEHICLE_LIGHTS){
        GPIO_PORTB_DATA_R &= ~(7);
        SET_BIT(GPIO_PORTB_DATA_R, color);

    }else if (type == PEDESTRIAN_LIGHTS){
        GPIO_PORTD_DATA_R &= ~(7);
        SET_BIT(GPIO_PORTD_DATA_R, color);
    }
}

void volatile update_traffic_lights(void){

    switch (vehicle_traffic_light_color)
    {
        /* if current color is red, switch to yellow */
    case RED:
        switch_traffic_light_state(VEHICLE_LIGHTS, YELLOW);
        switch_traffic_light_state(PEDESTRIAN_LIGHTS, YELLOW);
        vehicle_traffic_light_color = YELLOW;
        prev_vehicle_traffic_light_color = RED;
        break;
    
        /* if current color is green, switch to yellow */
    case GREEN:
        switch_traffic_light_state(VEHICLE_LIGHTS, YELLOW);
        switch_traffic_light_state(PEDESTRIAN_LIGHTS, YELLOW);
        vehicle_traffic_light_color = YELLOW;
        prev_vehicle_traffic_light_color = GREEN;
        break;

        /* if current color is yellow, then we see its previous color */
    case YELLOW:
        if (prev_vehicle_traffic_light_color == RED){
            switch_traffic_light_state(VEHICLE_LIGHTS, GREEN);
            switch_traffic_light_state(PEDESTRIAN_LIGHTS, RED);
            vehicle_traffic_light_color = GREEN;

        }else if (prev_vehicle_traffic_light_color == GREEN){
            switch_traffic_light_state(VEHICLE_LIGHTS, RED);
            switch_traffic_light_state(PEDESTRIAN_LIGHTS, GREEN);
            vehicle_traffic_light_color = RED;
        }
        prev_vehicle_traffic_light_color = YELLOW;
        break;
    }
}
