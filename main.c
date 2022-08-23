#include<stdint.h>

#define ITERATIONS_PER_MILLISECOND      762

void busy_wait_ms(uint64_t m_sec){
    unsigned long long delay = ITERATIONS_PER_MILLISECOND*m_sec;
    while(delay--);
}

int main(void){
    /* configure the vahicle traffic light LEDs */
    /* configure the pedestrian traffic light LEDs */
    /* configure the push button (for pedestrians to request grren light to pass) */

    /*
    while 1
        enable red light for vehicles & green light for pedestrians, for 5 seconds
        enable yellow light for both vehicles & pedestrians, for 5 seconds
        enable green light for vehicles & red light for pedestrians, for 5 seconds 
    */
}