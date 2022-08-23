#include "application.h"

int main(void){
    
    configure_vehicle_traffic_light();
    configure_pedestrian_traffic_light();
    configure_request_button(); /* for pedestrians to request green light to pass */

    while(1){
        
        /* enable red light for vehicles & green light for pedestrians, for 5 seconds */
        switch_traffic_light_state(VEHICLE_LIGHTS, RED);
        switch_traffic_light_state(PEDESTRIAN_LIGHTS, GREEN);
        busy_wait_ms(TRAFFIC_LIGHT_TIME_mSec);

        /* enable yellow light for both vehicles & pedestrians, for 5 seconds */
        switch_traffic_light_state(VEHICLE_LIGHTS, YELLOW);
        switch_traffic_light_state(PEDESTRIAN_LIGHTS, YELLOW);
        busy_wait_ms(TRAFFIC_LIGHT_TIME_mSec);

        /* enable green light for vehicles & red light for pedestrians, for 5 seconds */
        switch_traffic_light_state(VEHICLE_LIGHTS, GREEN);
        switch_traffic_light_state(PEDESTRIAN_LIGHTS, RED);
        busy_wait_ms(TRAFFIC_LIGHT_TIME_mSec);
    }
}