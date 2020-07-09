#include "bbzmessage_crc.h"
#include "util/crc16.h"  

uint16_t bbzmessage_crc(const message_t *msg) {
    const char *rawmsg = (const char*)msg;
    uint16_t crc = crc16(rawmsg, sizeof(message_t)-sizeof(msg->crc));
    return crc;
}
