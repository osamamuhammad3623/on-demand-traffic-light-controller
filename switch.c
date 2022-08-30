#include <stdint.h>
#include "switch.h"
#include "common_macros.h"
#include "tm4c123gh6pm.h"

void Switch_Configure(Switch_Pin sw){
	SYSCTL_RCGC2_R |= (1 << 5); /* enable clock for port F */
	CLEAR_BIT(GPIO_PORTF_DIR_R, sw);
	CLEAR_BIT(GPIO_PORTF_AFSEL_R, sw);
	GPIO_PORTF_LOCK_R = 0x4C4F434B; /* unlock commit reg. */
	SET_BIT(GPIO_PORTF_CR_R, sw); /* enable commit reg. to control PUR reg. */
	SET_BIT(GPIO_PORTF_PUR_R, sw);
	SET_BIT(GPIO_PORTF_DEN_R, sw);
}

uint8_t Switch_isPressed(Switch_Pin sw){
    if (BIT_IS_CLEAR(GPIO_PORTF_DATA_R,sw))
        return 1;

    return 0;
}
