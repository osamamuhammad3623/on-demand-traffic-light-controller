# On-demand Traffic Light Controller

## Application description
- 2 traffic lights are connected to the microcontroller.
- One for vehicles, the othe is for pedestrians.
- Pedestrians can use a push button to request green light to pass (in case the vehicles' traffic light is yellow or green)
- If a pedestrian requests to pass, and the vehicles' traffic light is red, nothing happens,  
otherwise, the vehicles' traffic light switches to red, the pedestrians' traffic light switches to green.

## Used components
- TM4C123GH6PM (Tiva C) microcontroller, based on ARM architecture.
- 6 LEDs; 3 for each traffic light
- A push button