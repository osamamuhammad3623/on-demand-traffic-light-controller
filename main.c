#include "application.h"
#include "sys_tick.h"

int main(void){
    
    configure_vehicle_traffic_light();
    configure_pedestrian_traffic_light();
    configure_request_button(); /* for pedestrians to request green light to pass */
    //SysTick_init((ITERATIONS_PER_MILLISECOND)*(TRAFFIC_LIGHT_TIME_mSec), update_traffic_lights);
    SysTick_init(100, update_traffic_lights);
    SysTick_start();

    while(1);
}
