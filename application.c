#include<stdint.h>
#include "basic_gpio.h"
#include "application.h"
#include "led.h"
#include "sys_tick.h"
#include "common_macros.h"
#include "switch.h"
#include "tm4c123gh6pm.h"

Traffic_Light_Color vehicle_traffic_light_color=YELLOW;
Traffic_Light_Color prev_vehicle_traffic_light_color=GREEN;

void configure_vehicle_traffic_light(){
    // using the builtin LEDs
    LED_Configure(RED_LED);
    LED_Configure(GREEN_LED);
    LED_Configure(YELLOW_LED);
}

void configure_pedestrian_traffic_light(){
    /* configuring the 2 pins */
    GPIO_Configuration pedestrian_traffic_leds={
        PEDESTRIANS_TRAFFIC_LIGHT_PORT,
        PEDESTRIANS_RED_LIGHT_PIN,
        LOGIC_LOW,
        Digital_Pin,
        GPIO,
        Output_Pin,
        Pull_up_resistor
    };

    GPIO_init(&pedestrian_traffic_leds);
    
    pedestrian_traffic_leds.pin = PEDESTRIANS_GREEN_LIGHT_PIN;
    GPIO_init(&pedestrian_traffic_leds);
}

void GPIOF_Handler(void){
    SET_BIT(GPIO_PORTF_ICR_R, Pin_4); /* clear interrupt flag */
    if (vehicle_traffic_light_color == RED){
        return;
    }

    switch_traffic_light_state(VEHICLE_LIGHTS, YELLOW);
    vehicle_traffic_light_color = YELLOW;
    prev_vehicle_traffic_light_color = GREEN;
    
    NVIC_ST_CURRENT_R = 0;/* reset systick timer count */
}

void configure_request_button(){

    Switch_Configure(SW1);
    /* configure the switch interrupt */
    CLEAR_BIT(GPIO_PORTF_IS_R, Pin_4); /* pin is edge-sensitive */
    CLEAR_BIT(GPIO_PORTF_IBE_R,Pin_4); /* disable both edges detection */
    CLEAR_BIT(GPIO_PORTF_IEV_R, Pin_4); /* falling-edge detection */
    CLEAR_BIT(GPIO_PORTF_ICR_R, Pin_4); /* clear prior interrupts */
    SET_BIT(GPIO_PORTF_IM_R, Pin_4); /* enable arm interrupt (module int) */
    SET_BIT(NVIC_EN0_R, 30); /* allow NVIC to activate/process the interrupt coming from PORT F */
}

void configure_application_timer(void){
    /* configure the systick timer to interrupt every second */
    SysTick_init(16e6, update_traffic_lights);
}

void enable_application_timer(void){
    SysTick_start();
    update_traffic_lights();
}

void switch_traffic_light_state(Traffic_Light_Type type, Traffic_Light_Color color){
    // using the builtin LEDs for vehicles traffic light
    if (type == VEHICLE_LIGHTS){
        LED_Disable();
        switch (color)
        {
        case RED:
            LED_Enable(RED_LED);
            break;

        case YELLOW:
            LED_Enable(YELLOW_LED);
            break;

        case GREEN:
            LED_Enable(GREEN_LED);
            break;
        }

    }else if (type == PEDESTRIAN_LIGHTS){

        GPIO_writePin(PEDESTRIANS_TRAFFIC_LIGHT_PORT, PEDESTRIANS_RED_LIGHT_PIN, LOGIC_LOW);
        GPIO_writePin(PEDESTRIANS_TRAFFIC_LIGHT_PORT, PEDESTRIANS_GREEN_LIGHT_PIN, LOGIC_LOW);
        switch (color)
        {
        case RED:
            GPIO_writePin(PEDESTRIANS_TRAFFIC_LIGHT_PORT, PEDESTRIANS_RED_LIGHT_PIN, LOGIC_HIGH);
            break;

        case GREEN:
            GPIO_writePin(PEDESTRIANS_TRAFFIC_LIGHT_PORT, PEDESTRIANS_GREEN_LIGHT_PIN, LOGIC_HIGH);
            break;
        }
    }
}

void volatile update_traffic_lights(void){
    static uint8_t systick_int_cnt= (TRAFFIC_LIGHT_TIME_Sec)-1;

    /* check if the configured traffic light time has elapsed */
    systick_int_cnt++;
    if (systick_int_cnt != TRAFFIC_LIGHT_TIME_Sec){
        return;
    }
    systick_int_cnt=0;


    switch (vehicle_traffic_light_color)
    {
        /* if current color is red, switch to yellow */
    case RED:
        switch_traffic_light_state(VEHICLE_LIGHTS, YELLOW);
        switch_traffic_light_state(PEDESTRIAN_LIGHTS, RED);
        vehicle_traffic_light_color = YELLOW;
        prev_vehicle_traffic_light_color = RED;
        break;
    
        /* if current color is green, switch to yellow */
    case GREEN:
        switch_traffic_light_state(VEHICLE_LIGHTS, YELLOW);
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
