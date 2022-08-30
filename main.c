#include "application.h"

int main(void){
  
    configure_vehicle_traffic_light();
    configure_pedestrian_traffic_light();
    configure_request_button(); /* for pedestrians to request green light to pass */
    configure_application_timer();
    enable_application_timer();

    while(1);
}
