/*
 * Project argon
 * Description:
 * Author:
 * Date:
 */

#include "bbzparticle.h"
#include "Particle.h"

int pin = D7;

void bzz_print_swarm_id(){
    bbzvm_assert_lnum(1);
    bbzobj_t* int_val = bbzheap_obj_at(bbzvm_locals_at(1));

    Serial.printlnf("Hello from swarm id: %d", int_val->i.value);
    bbzvm_ret0();
}


void bbzvm_toggle_led(){
    bbzvm_assert_lnum(0);
    int new_value = !digitalRead(pin);
    Serial.printlnf("Toggled led: %d", new_value);
    digitalWrite(pin, new_value);

    bbzvm_ret0();
}

void bbz_delay(){
    delay((uint16_t)bbzheap_obj_at(bbzvm_locals_at(1))->i.value);
    bbzvm_ret0();
}

// setup() runs once, when the device is first turned on.
void setup() {

    Serial.printlnf("Start");
    pinMode(pin, OUTPUT);
    bbz_particle_init();

}

void bbz_setup() {
    bbzvm_function_register(BBZSTRING_ID(print_swarm_id), bzz_print_swarm_id);
    bbzvm_function_register(BBZSTRING_ID(delay), bbz_delay);
    bbzvm_function_register(BBZSTRING_ID(toggle_led), bbzvm_toggle_led);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

    bbz_particle_start(bbz_setup);
    Serial.printlnf("DEVICE CRASHED");

}