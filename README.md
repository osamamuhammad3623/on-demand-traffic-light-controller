# On-demand Traffic Light Controller

## Application description
- 2 traffic lights are connected to the microcontroller.
- One for vehicles (red, yellow & green), the other is for pedestrians (red & green).
- Pedestrians can use a push button to request green light to pass (in case the vehicles traffic light is yellow or green)
- If a pedestrian requests to pass, and the vehicles traffic light is red, nothing happens,  
otherwise, the vehicles traffic light immediately switches to yellow then red, and the pedestrians traffic light switches to green.

## Used components & tools
- TM4C123GH6PM (Tiva C) microcontroller, based on ARM architecture.
- 5 LEDs; (3 built-in LEDs for vehicles traffic light, 2 pedestrians traffic light LEDs)
- A push button (I used the built-in switch 1)
- IAR Embedded Workbench & Keil IDEs for debugging & simulation.

## With the help of Datasheet, I got my hands on:
- Ports & DIO
- SysTick timer
- NVIC
- Interrupts
- TM4C123 builtin LEDs & switches

## Project architecture
- The project follows the Layered Architecture model.
1. Main function has the superloop, and calls the application APIs.
2. Application APIs uses the modules drivers.
3. Modules drivers deal with the hardware directly.
