/*
 * Project argon
 * Description:
 * Author:
 * Date:
 */

#include "bbzparticle.h"
#include "Particle.h"

void bzz_print_number(){
    bbzvm_assert_lnum(1);
    bbzobj_t* int_val = bbzheap_obj_at(bbzvm_locals_at(1));

    Serial.printlnf("Hello world! %d", int_val->i.value);
    bbzvm_ret0();
}

void bbz_delay(){
    delay((uint16_t)bbzheap_obj_at(bbzvm_locals_at(1))->i.value);
    Serial.printlnf("delay called");
    bbzvm_ret0();
}

// setup() runs once, when the device is first turned on.
void setup() {

    Serial.printlnf("Start");

    bbz_particle_init();

}

void bbz_setup() {
    bbzvm_function_register(BBZSTRING_ID(printnumber), bzz_print_number);
    bbzvm_function_register(BBZSTRING_ID(delay), bbz_delay);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

    bbz_particle_start(bbz_setup);
    Serial.printlnf("DEVICE CRASHED");

}