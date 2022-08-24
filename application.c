#include<stdint.h>
#include "basic_gpio.h"
#include "application.h"
#include "common_macros.h"
#include "tm4c123gh6pm.h"


void busy_wait_ms(uint64_t m_sec){
    unsigned long long delay = ITERATIONS_PER_MILLISECOND*m_sec;
    while(delay--);
}

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

void GPIOE_Handler(void){
    CLEAR_BIT(GPIO_PORTE_ICR_R, REQUEST_BUTTON_PIN); /* clear interrupt flag */
    /* if the vehicles' traffic light is not red, switch it to red */
    if (BIT_IS_CLEAR(GPIO_PORTB_DATA_R, 0)){
        switch_traffic_light_state(VEHICLE_LIGHTS, RED);
        switch_traffic_light_state(PEDESTRIAN_LIGHTS, GREEN);
    }
}

void configure_request_button(){
    GPIO_Configuration push_btn={
        PORTF,
        REQUEST_BUTTON_PIN,
        LOGIC_LOW,
        Digital_Pin,
        GPIO,
        Input_Pin,
        Pull_up_resistor
    };

    GPIO_init(&push_btn);

    CLEAR_BIT(GPIO_PORTF_IS_R, REQUEST_BUTTON_PIN); /* pin is edge-sensitive */
    CLEAR_BIT(GPIO_PORTF_IBE_R,REQUEST_BUTTON_PIN); /* disable both edges detection */
    CLEAR_BIT(GPIO_PORTF_IEV_R, REQUEST_BUTTON_PIN); /* falling-edge detection */
    CLEAR_BIT(GPIO_PORTF_ICR_R, REQUEST_BUTTON_PIN); /* clear prior interrupts */
    SET_BIT(GPIO_PORTF_IM_R, REQUEST_BUTTON_PIN); /* enable arm interrupt (module int) */
    SET_BIT(NVIC_EN1_R, 14); /* allow NVIC to activate the interrupt coming from PORT F */
}

void switch_traffic_light_state(Traffic_Light_Type type, Traffic_Light_Color color){
    /* clear pins 0:2, then set the target pin */
    if (type == VEHICLE_LIGHTS){
        GPIO_PORTB_DATA_R &= ~(7);
        switch (color)
        {
        case RED:
            SET_BIT(GPIO_PORTB_DATA_R, RED);
            break;
        case YELLOW:
            SET_BIT(GPIO_PORTB_DATA_R, YELLOW);
            break;
        case GREEN:
            SET_BIT(GPIO_PORTB_DATA_R, GREEN);
            break;
        }

    }else if (type == PEDESTRIAN_LIGHTS){
        GPIO_PORTD_DATA_R &= ~(7);
        switch (color)
        {
        case RED:
            SET_BIT(GPIO_PORTD_DATA_R, RED);
            break;
        case YELLOW:
            SET_BIT(GPIO_PORTD_DATA_R, YELLOW);
            break;
        case GREEN:
            SET_BIT(GPIO_PORTD_DATA_R, GREEN);
            break;
        }
    }
}