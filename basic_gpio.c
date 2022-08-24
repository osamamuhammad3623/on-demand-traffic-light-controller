#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "basic_gpio.h"
#include "common_macros.h"


void GPIO_init(const GPIO_Configuration * config){
    SET_BIT(SYSCTL_RCGC2_R, config->port); /* enable clock for the port */
    if (config->port == PORTA){
        /* Configurate direction */
        if (config->dir == Output_Pin){
            SET_BIT(GPIO_PORTA_DIR_R, config->pin);
        }else{
            CLEAR_BIT(GPIO_PORTA_DIR_R, config->pin);
        }

        /* Configurate function type */
        if (config->type == GPIO){
            CLEAR_BIT(GPIO_PORTA_AFSEL_R, config->pin);
        }else {
            SET_BIT(GPIO_PORTA_AFSEL_R, config->pin);
        }

        /* Configurate internal resistor */
        if (config->internalR != Disable_internal_resistor){

            GPIO_PORTA_LOCK_R = 0x4C4F434B; /* unlock commit R. */
            SET_BIT(GPIO_PORTA_CR_R,config->pin) ; /* enable commit R. to control PUR/PDR R. */

            if (config->internalR == Pull_up_resistor){ 
                SET_BIT(GPIO_PORTA_PUR_R, config->pin); /* enable PUR for the pin */
            }else{
                SET_BIT(GPIO_PORTA_PDR_R, config->pin); /* enable PDR for the pin */
            }
        }

        /* Configurate Digital IO */
        if (config->isDigital == Digital_Pin){
            SET_BIT(GPIO_PORTA_DEN_R, config->pin);
        }else{
            CLEAR_BIT(GPIO_PORTA_DEN_R, config->pin);
        }
    }

    else if (config->port == PORTB){
        /* Configurate direction */
        if (config->dir == Output_Pin){
            SET_BIT(GPIO_PORTB_DIR_R, config->pin);

        }else{
            CLEAR_BIT(GPIO_PORTB_DIR_R, config->pin);
        }

        /* Configurate function type */
        if (config->type == GPIO){
            CLEAR_BIT(GPIO_PORTB_AFSEL_R, config->pin);
        }else {
            SET_BIT(GPIO_PORTB_AFSEL_R, config->pin);
        }

        /* Configurate internal resistor */
        if (config->internalR != Disable_internal_resistor){

            GPIO_PORTB_LOCK_R = 0x4C4F434B; /* unlock commit R. */
            SET_BIT(GPIO_PORTB_CR_R,config->pin) ; /* enable commit R. to control PUR/PDR R. */
            
            if (config->internalR == Pull_up_resistor){ 
                SET_BIT(GPIO_PORTB_PUR_R, config->pin); /* enable PUR for the pin */
            }else{
                SET_BIT(GPIO_PORTB_PDR_R, config->pin); /* enable PDR for the pin */
            }
        }

        /* Configurate Digital IO */
        if (config->isDigital == Digital_Pin){
            SET_BIT(GPIO_PORTB_DEN_R, config->pin);
        }else{
            CLEAR_BIT(GPIO_PORTB_DEN_R, config->pin);
        }
    }

    else if (config->port == PORTC){
        /* Configurate direction */
        if (config->dir == Output_Pin){
            SET_BIT(GPIO_PORTC_DIR_R, config->pin);
        }else{
            CLEAR_BIT(GPIO_PORTC_DIR_R, config->pin);
        }

        /* Configurate function type */
        if (config->type == GPIO){
            CLEAR_BIT(GPIO_PORTC_AFSEL_R, config->pin);
        }else {
            SET_BIT(GPIO_PORTC_AFSEL_R, config->pin);
        }

        /* Configurate internal resistor */
        if (config->internalR != Disable_internal_resistor){

            GPIO_PORTC_LOCK_R = 0x4C4F434B; /* unlock commit R. */
            SET_BIT(GPIO_PORTC_CR_R,config->pin) ; /* enable commit R. to control PUR/PDR R. */
            
            if (config->internalR == Pull_up_resistor){ 
                SET_BIT(GPIO_PORTC_PUR_R, config->pin); /* enable PUR for the pin */
            }else{
                SET_BIT(GPIO_PORTC_PDR_R, config->pin); /* enable PDR for the pin */
            }
        }

        /* Configurate Digital IO */
        if (config->isDigital == Digital_Pin){
            SET_BIT(GPIO_PORTC_DEN_R, config->pin);
        }else{
            CLEAR_BIT(GPIO_PORTC_DEN_R, config->pin);
        }
    }

    else if (config->port == PORTD){
        /* Configurate direction */
        if (config->dir == Output_Pin){
            SET_BIT(GPIO_PORTD_DIR_R, config->pin);
        }else{
            CLEAR_BIT(GPIO_PORTD_DIR_R, config->pin);
        }

        /* Configurate function type */
        if (config->type == GPIO){
            CLEAR_BIT(GPIO_PORTD_AFSEL_R, config->pin);
        }else {
            SET_BIT(GPIO_PORTD_AFSEL_R, config->pin);
        }

        /* Configurate internal resistor */
        if (config->internalR != Disable_internal_resistor){

            GPIO_PORTD_LOCK_R = 0x4C4F434B; /* unlock commit R. */
            SET_BIT(GPIO_PORTD_CR_R,config->pin) ; /* enable commit R. to control PUR/PDR R. */
            
            if (config->internalR == Pull_up_resistor){ 
                SET_BIT(GPIO_PORTD_PUR_R, config->pin); /* enable PUR for the pin */
            }else{
                SET_BIT(GPIO_PORTD_PDR_R, config->pin); /* enable PDR for the pin */
            }
        }

        /* Configurate Digital IO */
        if (config->isDigital == Digital_Pin){
            SET_BIT(GPIO_PORTD_DEN_R, config->pin);
        }else{
            CLEAR_BIT(GPIO_PORTD_DEN_R, config->pin);
        }
    }

    else if (config->port == PORTE){
        /* Configurate direction */
        if (config->dir == Output_Pin){
            SET_BIT(GPIO_PORTE_DIR_R, config->pin);
        }else{
            CLEAR_BIT(GPIO_PORTE_DIR_R, config->pin);
        }

        /* Configurate function type */
        if (config->type == GPIO){
            CLEAR_BIT(GPIO_PORTE_AFSEL_R, config->pin);
        }else {
            SET_BIT(GPIO_PORTE_AFSEL_R, config->pin);
        }

        /* Configurate internal resistor */
        if (config->internalR != Disable_internal_resistor){

            GPIO_PORTE_LOCK_R = 0x4C4F434B; /* unlock commit R. */
            SET_BIT(GPIO_PORTE_CR_R,config->pin) ; /* enable commit R. to control PUR/PDR R. */
            
            if (config->internalR == Pull_up_resistor){ 
                SET_BIT(GPIO_PORTE_PUR_R, config->pin); /* enable PUR for the pin */
            }else{
                SET_BIT(GPIO_PORTE_PDR_R, config->pin); /* enable PDR for the pin */
            }
        }

        /* Configurate Digital IO */
        if (config->isDigital == Digital_Pin){
            SET_BIT(GPIO_PORTE_DEN_R, config->pin);
        }else{
            CLEAR_BIT(GPIO_PORTE_DEN_R, config->pin);
        }
    }

    else if (config->port == PORTF){
        /* Configurate direction */
        if (config->dir == Output_Pin){
            SET_BIT(GPIO_PORTF_DIR_R, config->pin);
        }else{
            CLEAR_BIT(GPIO_PORTF_DIR_R, config->pin);
        }

        /* Configurate function type */
        if (config->type == GPIO){
            CLEAR_BIT(GPIO_PORTF_AFSEL_R, config->pin);
        }else {
            SET_BIT(GPIO_PORTF_AFSEL_R, config->pin);
        }

        /* Configurate internal resistor */
        if (config->internalR != Disable_internal_resistor){

            GPIO_PORTF_LOCK_R = 0x4C4F434B; /* unlock commit R. */
            SET_BIT(GPIO_PORTF_CR_R,config->pin) ; /* enable commit R. to control PUR/PDR R. */
            
            if (config->internalR == Pull_up_resistor){ 
                SET_BIT(GPIO_PORTF_PUR_R, config->pin); /* enable PUR for the pin */
            }else{
                SET_BIT(GPIO_PORTF_PDR_R, config->pin); /* enable PDR for the pin */
            }
        }

        /* Configurate Digital IO */
        if (config->isDigital == Digital_Pin){
            SET_BIT(GPIO_PORTF_DEN_R, config->pin);
        }else{
            CLEAR_BIT(GPIO_PORTF_DEN_R, config->pin);
        }
    }

    /* Configure data */
    if (config->dir == Output_Pin){
        GPIO_writePin(config->port, config->pin, config->data);
    }

}