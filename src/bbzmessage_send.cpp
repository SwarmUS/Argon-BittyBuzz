#include "bbzmessage_send.h"
#include "Particle.h"

uint8_t bbzmessage_send(const message_t *){
    Serial.printlnf("Trying to send a message");
    return 1;
}