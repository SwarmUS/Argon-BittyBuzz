#include "bbzoutmsg.h"

#ifndef BBZ_DISABLE_MESSAGES
/****************************************/
/****************************************/

void bbzoutmsg_queue_construct() {
    bbzringbuf_construct(&vm->outmsgs.queue, (uint8_t*)vm->outmsgs.buf, sizeof(bbzmsg_t), BBZOUTMSG_QUEUE_CAP+1);
}

/****************************************/
/****************************************/

void bbzoutmsg_queue_destruct() {
    bbzringbuf_clear(&vm->outmsgs.queue);
}

/****************************************/
/****************************************/

uint16_t bbzoutmsg_queue_size() {
    return bbzringbuf_size(&vm->outmsgs.queue);
}

/****************************************/
/****************************************/

static bbzmsg_t* outmsg_queue_append_template() {
    bbzmsg_t* m = ((bbzmsg_t*)bbzringbuf_at(&vm->outmsgs.queue, vm->outmsgs.queue.dataend + vm->outmsgs.queue.capacity));
    if (bbzringbuf_full(&vm->outmsgs.queue)) {
        // If full, replace the message with the lowest priority (the last of the queue) with the new one.
        *((bbzmsg_t*)bbzringbuf_rawat(&vm->outmsgs.queue, vm->outmsgs.queue.dataend - (uint8_t)1 + vm->outmsgs.queue.capacity)) = *m;
    }
    else {
        // If not full, push the message at the end of the queue.
        bbzringbuf_makeslot(&vm->outmsgs.queue);
    }
    return m;
}

/****************************************/
/****************************************/

#ifndef BBZ_DISABLE_NEIGHBORS
void bbzoutmsg_queue_append_broadcast(bbzheap_idx_t topic, bbzheap_idx_t value) {
    /* Make a new BROADCAST message */
    bbzmsg_t* m = outmsg_queue_append_template();
    m->bc.type = BBZMSG_BROADCAST;
    m->bc.rid = vm->robot;
    m->bc.topic = bbzheap_obj_at(topic)->s.value;
    m->bc.value = *bbzheap_obj_at(value);
    bbzmsg_sort_priority(&vm->outmsgs.queue);
}
#endif // !BBZ_DISABLE_NEIGHBORS

/****************************************/
/****************************************/

#if !defined(BBZ_DISABLE_SWARMS) && !defined(BBZ_DISABLE_SWARMLIST_BROADCASTS)
void bbzoutmsg_queue_append_swarm(bbzrobot_id_t robot,
                                  bbzswarmlist_t swarms,
                                  bbzlamport_t lamport) {
    /* Make a new swarm message */
    bbzmsg_t* m = outmsg_queue_append_template();
    m->sw.type = BBZMSG_SWARM;
    m->sw.rid = robot;
    m->sw.lamport = lamport;
    m->sw.swarms = swarms;
    bbzmsg_sort_priority(&vm->outmsgs.queue);
}
#endif // !BBZ_DISABLE_SWARMS && !BBZ_DISABLE_SWARMLIST_BROADCASTS

/****************************************/
/****************************************/

#ifndef BBZ_DISABLE_VSTIGS
void bbzoutmsg_queue_append_vstig(bbzmsg_payload_type_t type,
                                  bbzrobot_id_t rid,
                                  uint16_t key,
                                  bbzheap_idx_t value,
                                  uint8_t lamport) {
    /* Make a new VSTIG_PUT/VSTIG_QUERY message */
    bbzmsg_t* m = outmsg_queue_append_template();
    m->vs.type = type;
    m->vs.rid = rid;
    m->vs.lamport = lamport;
    m->vs.key = key;
    m->vs.data = *bbzheap_obj_at(value);
    bbzmsg_sort_priority(&vm->outmsgs.queue);
}
#endif // !BBZ_DISABLE_VSTIGS

/****************************************/
/****************************************/

void bbzoutmsg_queue_first(bbzmsg_payload_t* buf) {
    bbzmsg_t* msg = (bbzmsg_t*)bbzringbuf_at(&vm->outmsgs.queue, 0);
    bbzringbuf_clear(buf);
    bbzmsg_serialize_u8(buf, msg->type);
    bbzmsg_serialize_u16(buf, msg->base.rid);
    switch (msg->type) {
        case BBZMSG_BROADCAST:
#ifndef BBZ_DISABLE_NEIGHBORS
            if (bbztype_istable(msg->bc.value)) return;
            bbzmsg_serialize_u16(buf, msg->bc.topic);
            bbzmsg_serialize_obj(buf, &msg->bc.value);
            break;
#else // !BBZ_DISABLE_NEIGHBORS
            return;
#endif // !BBZ_DISABLE_NEIGHBORS
        case BBZMSG_VSTIG_PUT: // fallthrough
        case BBZMSG_VSTIG_QUERY:
#ifndef BBZ_DISABLE_VSTIGS
            if (bbztype_istable(msg->vs.data)) return;
            bbzmsg_serialize_u16(buf, msg->vs.key);
            bbzmsg_serialize_obj(buf, &msg->vs.data);
            bbzmsg_serialize_u8(buf, msg->vs.lamport);
            break;
#else // !BBZ_DISABLE_VSTIGS
            return;
#endif // !BBZ_DISABLE_VSTIGS
        case BBZMSG_SWARM:
#if !defined(BBZ_DISABLE_SWARMS) && !defined(BBZ_DISABLE_SWARMLIST_BROADCASTS)
            bbzmsg_serialize_u16(buf, msg->sw.lamport);
            bbzmsg_serialize_u8(buf, msg->sw.swarms);
            break;
#else // !BBZ_DISABLE_SWARMS && !BBZ_DISABLE_SWARMLIST_BROADCASTS
            return;
#endif // !BBZ_DISABLE_SWARMS && !BBZ_DISABLE_SWARMLIST_BROADCASTS
        default:
            break;
    }
}

/****************************************/
/****************************************/

void bbzoutmsg_queue_next() {
    bbzringbuf_pop(&vm->outmsgs.queue);
#ifdef BBZMSG_POP_NEEDS_SORT
    bbzmsg_sort_priority(&vm->outmsgs.queue);
#endif // !BBZMSG_POP_NEEDS_SORT
}

/****************************************/
/****************************************/
#endif // !BBZ_DISABLE_MESSAGES