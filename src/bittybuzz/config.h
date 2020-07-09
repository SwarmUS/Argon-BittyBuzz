#ifndef BBZZ_CONFIG_H
#define BBZZ_CONFIG_H

/**
 * @brief Total size of heap in bytes.
 */
#define BBZHEAP_SIZE 1088

/**
 * @brief Elements per table segment.
 */
#define BBZHEAP_ELEMS_PER_TSEG 5
/**
 * @brief Size of the stack in bytes.
 */
#define BBZSTACK_SIZE 96

/**
 * @brief Index of end of the heap's space reserved for lambdas'
 * activation record.
 * @note The maximum value is 0xFE (254)
 */
#define BBZHEAP_RSV_ACTREC_MAX 28

/**
 * @brief Virtual stigmergy's capacity.
 */
#define BBZVSTIG_CAP 3

/**
 * @brief Maximum number of neighbors.
 */
#define BBZNEIGHBORS_CAP 15BBZZ_


/**
 * @brief Capacity of the input message queue.
 */
#define BBZINMSG_QUEUE_CAP 10

/**
 * @brief Capacity of the output message queue.
 */
#define BBZOUTMSG_QUEUE_CAP 10

/**
 * @brief Lamport Clock Threashold (max accepting range).
 */
#define BBZLAMPORT_THRESHOLD 50

/**
 * @brief Max recursion depth for the heap's
 *        Garbage Collector marking function.
 */
#define BBZHEAP_GCMARK_DEPTH 8

/**
 * @brief The maximum number of messages to process
 * every instruction.
 */
#define BBZMSG_IN_PROC_MAX 10

/**
 * @brief The period between two (2) neighbors' data garbage-collection.
 */
#define BBZNEIGHBORS_CLR_PERIOD 10

/**
 * @brief The number of timestep before the neighbors' GC that we start to mark neighbors data.
 */
#define BBZNEIGHBORS_MARK_TIME 4

/**
 * @brief Whether to compile in DEBUG_VM mode.
 */
#define DEBUG_VM

// ==============================
// =  FEATURE-DISABLING MACROS  =
// ==============================

/**
 * @brief Whether we are crosscompiling.
 */
//#define BBZCROSSCOMPILING

/**
 * @brief Whether to use high memory optimizations.
 */
//#define BBZ_XTREME_MEMORY

/**
 * @brief Whether to use normal or priority queue for out-messages
 */
//#define BBZ_USE_PRIORITY_SORT

/**
 * @brief Whether to disable the neighbor structure.
 */
#define BBZ_DISABLE_NEIGHBORS

/**
 * @brief Whether to disable the stigmergy structure.
 */
//#define BBZ_DISABLE_VSTIGS

/**
 * @brief Whether to disable the swarm structure.
 */
//#define BBZ_DISABLE_SWARMS

/**
 * @brief Whether to disable the use of messages in BittyBuzz.
 */
//#define BBZ_DISABLE_MESSAGES

/**
 * @brief Whether to disable Python behaviors of closures.
 * @brief Make closures behave like in JavaScript.
 */
//#define BBZ_DISABLE_PY_BEHAV

/**
 * @brief Whether we disable the broadcasting of our swarmlist to
 * neighboring robots.
 * @todo Currently, BittyBuzz requires this feature to be disabled.
 */
#define BBZ_DISABLE_SWARMLIST_BROADCASTS

#endif // !BBZZ_CONFIG_H
