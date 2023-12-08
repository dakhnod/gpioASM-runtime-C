#include "gpioasm.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

gpioasm_engine_t engine;

void set_digital_output_pin(uint32_t index, bool state){
    printf("setting digital pin %d to state %d\n", index, state);
}

void set_analog_output_pin(uint32_t index, uint16_t duty_cycle){
    printf("setting analog pin %d to state %d\n", index, duty_cycle);
}

bool get_digital_input_pin(uint32_t index){
    // should read the actual input state here
    return false;
}

void start_timer(uint64_t timeout){
    printf("setting timer for %llums\n", timeout);
}

int main(){
    uint8_t test_microcode[] = {
        0, 128, 0, 1, 253, 32, 100, 1, 252, 32, 100, 176, 2, 9
    };
    gpioasm_engine_init_t init = {
        .pin_digital_output_handler = set_digital_output_pin,
        .pin_analog_output_handler = set_analog_output_pin,
        .pin_digital_input_provider = get_digital_input_pin,
        .timer_handler = start_timer
    };

    gpioasm_init(&engine, &init);

    gpioasm_push_packet(&engine, test_microcode, sizeof(test_microcode));

    gpioasm_start(&engine);

    // doing this because we have no real timer calling back...
    // if there was a timer, it would have to call gpioasm_handle_timer_timeout on timeout
    while(!gpioasm_read_has_reached_end(&engine)){
        gpioasm_handle_timer_timeout(&engine);
    }
}