#include "gpioasm.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

gpioasm_engine_t engine;

void set_digital_output_pin(uint32_t index, uint8_t state){
    // state 0 = nff
    // state 1 = on
    // state 2 = high-impedance
    printf("setting digital pin %d to state %d\n", index, state);
}

void set_analog_output_pin(uint32_t index, uint16_t duty_cycle){
    printf("setting analog pin %d to state %d\n", index, duty_cycle);
}

bool get_digital_input_pin(uint32_t index){
    // should read the actual input state here
    return false;
}

void set_timer(void *engine_ptr, uint64_t timeout, bool start){
    if(start){
        printf("setting timer for %llums\n", timeout);
    }else{
        printf("stopping timer\n");
    }
}

int main(){
    uint8_t test_microcode[] = {
        0, 128, 0, 1, 253, 32, 100, 1, 252, 32, 100, 176, 2, 9
    };
    gpioasm_engine_init_t init = {
        .pin_digital_output_handler = set_digital_output_pin,
        .pin_analog_output_handler = set_analog_output_pin,
        .pin_digital_input_provider = get_digital_input_pin,
        .timer_handler = set_timer
    };

    gpioasm_init(&engine, &init);

    gpioasm_push_packet(&engine, test_microcode, sizeof(test_microcode));

    gpioasm_start(&engine);

    // doing this because we have no real timer calling back...
    // if there was a timer, it would have to call gpioasm_handle_timer_timeout on timeout
    while(gpioasm_is_running(&engine)){
        gpioasm_handle_timer_timeout(&engine);
    }
}