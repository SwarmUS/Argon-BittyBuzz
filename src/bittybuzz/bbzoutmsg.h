/**
 * @file bbzoutmsg.h
 * @brief Definition of the message queues structure for outgoing messages.
 */

#ifndef BBZOUTMSG_H
#define BBZOUTMSG_H

#include "bbzinclude.h"
#include "bbzmsg.h"
#include "bbzringbuf.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Type for the output message structure.
 * @note You should not create an instance of this structure manually ;
 * we assume there is only a single instance: vm->outmsgs.
 */
typedef struct PACKED bbzoutmsg_queue_t {
#ifndef BBZ_DISABLE_MESSAGES
    bbzringbuf_t queue; /**< @brief Message queue. */
    bbzmsg_t buf[BBZOUTMSG_QUEUE_CAP+2]; /**< @brief Output message buffer */
#endif // !BBZ_DISABLE_MESSAGES
} bbzoutmsg_queue_t;

#ifndef BBZ_DISABLE_MESSAGES
/**
 * @brief Constructs the VM's outgoing message queue.
 */
void bbzoutmsg_queue_construct();

/**
 * @brief Destructs the VM's outgoing message queue.
 */
void bbzoutmsg_queue_destruct();

/**
 * @brief Returns how many messages are in the queue.
 * @return The count of messages in the queue
 */
uint16_t bbzoutmsg_queue_size();

#ifndef BBZ_DISABLE_NEIGHBORS
/**
 * @brief Appends a new #BBZMSG_BROADCAST message to the output queue.
 * @param[in] topic The topic on which to send (a string object).
 * @param[in] value The value.
 */
void bbzoutmsg_queue_append_broadcast(bbzheap_idx_t topic, bbzheap_idx_t value);
#endif // !BBZ_DISABLE_NEIGHBORS

#ifndef BBZ_DISABLE_SWARMS
/**
 * @brief Appends a new BBZMSG_SWARM message to the output queue.
 * @param[in] robot The robot which owns the swarm data.
 * @param[in] swarms The swarmlist to append.
 * @param[in] lamport The swarmlist's lamport clock.
 */
void bbzoutmsg_queue_append_swarm(bbzrobot_id_t robot,
                                  bbzswarmlist_t swarms,
                                  bbzlamport_t lamport);
#endif // !BBZ_DISABLE_SWARMS

#ifndef BBZ_DISABLE_VSTIGS
/**
 * @brief Appends a new #BBZMSG_VSTIG_PUT/#BBZMSG_VSTIG_QUERY message to the
 * output queue.
 * @param[in] type The type of the message to append.
 * @param[in] rid The robot to whom the data belongs.
 * @param[in] key The string ID corresponding to the value to send.
 * @param[in] value The value to send.
 * @param[in] lamport The lamport clock of the value.
 */
void bbzoutmsg_queue_append_vstig(bbzmsg_payload_type_t type,
                                  bbzrobot_id_t rid,
                                  uint16_t key,
                                  bbzheap_idx_t value,
                                  uint8_t lamport);
#endif // !BBZ_DISABLE_VSTIGS

/**
 * @brief Serializes and returns the first message in the queue.
 * @param[out] buf A buffer (allocated by the caller) to put the serialized payload to send.
 */
void bbzoutmsg_queue_first(bbzmsg_payload_t *buf);

/**
 * @brief Removes the first element of the queue.
 */
void bbzoutmsg_queue_next();

/**
 * @brief Returns the message at the given position in the buffer.
 * @param[in] pos The position of the rquested message.
 * @return The requested message.
 */
#define bbzoutmsg_queue_get(pos) ((bbzmsg_t*)bbzringbuf_at(&vm->outmsgs.queue, pos))
#else // !BBZ_DISABLE_MESSAGES
#define bbzoutmsg_queue_construct(...)
#define bbzoutmsg_queue_destruct(...)
#define bbzoutmsg_queue_size(...) (0)
#define bbzoutmsg_queue_first(...)
void bbzoutmsg_queue_next(){}
#define bbzoutmsg_queue_get(...) ((bbzmsg_t*)NULL)
#endif // !BBZ_DISABLE_MESSAGES

#if defined(BBZ_DISABLE_NEIGHBORS) || defined(BBZ_DISABLE_MESSAGES)
#define bbzoutmsg_queue_append_broadcast(...)
#endif
#if defined(BBZ_DISABLE_VSTIGS) || defined(BBZ_DISABLE_MESSAGES)
#define bbzoutmsg_queue_append_vstig(...)
#endif
#if defined(BBZ_DISABLE_SWARMS) || defined(BBZ_DISABLE_MESSAGES)
#define bbzoutmsg_queue_append_swarm_chunk(...)
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#include "bbzvm.h" // Include AFTER bbzoutmsg.h because of circular dependencies.

#endif // !BBZOUTMSG_H