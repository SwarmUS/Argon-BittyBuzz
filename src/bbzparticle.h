/**
 * @file bbzkilobot.h
 * @brief Definition of Kilobot's library used in the BittyBuzz's vm
 * implementation for Kilobots.
 */

#ifndef BITTYBUZZ_BBZKILOBOT_H
#define BITTYBUZZ_BBZKILOBOT_H

#include <stdint.h>
#include "bbzmessage.h"
#include "bbzmessage_crc.h"

#include "bittybuzz/bbzvm.h"
#include "bittybuzz/util/bbzstring.h"
#include "bzzsymbols.h"

#define RGB(r,g,b) (((r)&3)|(((g)&3)<<2)|(((b)&3)<<4))
#define TICKS_PER_SEC 31

/**
 * @brief Distance measurement.
 *
 * Every time a message is received by a kilobot, it collects two 10 bit
 * measurements that represent the signal strength of the received
 * message after going through an operational amplifier. This data
 * structure stores these two measurements.
 *
 * Using these two measurements it is possible to estimate the distance
 * of the sender.
 */
typedef struct PACKED distance_measurement_t {
    int16_t low_gain;  ///< Low gain 10-bit signal-strength measurement.
    int16_t high_gain; ///< High gain 10-bit signal-strength measurement.
} distance_measurement_t;

typedef void (*message_rx_t)(message_t *, distance_measurement_t *d);

typedef message_t *(*message_tx_t)(void);

typedef void (*message_tx_success_t)(void);

typedef void (*kilo_setup_func)();

extern volatile uint16_t kilo_tx_period;

/**
 * @brief Kilobot unique identifier.
 *
 * This variable holds a 16-bit positive integer which is designated as
 * the kilobot's unique identifier during calibration.
 */
extern uint16_t particle_uid;

/**
 * @brief Pauses the program for the specified amount of time.
 *
 * This function receives as an argument a positive 16-bit integer @p ms
 * that represents the number of milliseconds for which to pause the
 * program.
 *
 * @param ms Number of milliseconds to pause the program (there are 1000
 * milliseconds in a second).
 *
 * @note While its easy to create short delays in the program execution
 * using this function, the processor of the kilobot cannot perform
 * other tasks during this delay functions. In general its preferable to
 * use timers to create delays.
 * @see kilo_ticks
 */
void bbz_particle_delay(uint16_t ms);

/**
 * @brief Initialize kilobot hardware.
 *
 * TODO Change the list of what this function does.
 * This function initializes all hardware of the kilobots. This includes
 * calibrating the hardware oscillator, setting hardware timers,
 * configuring ports, setting up analog-to-digital converters,
 * registering system interrupts and the initializing the messaging
 * subsystem.
 *
 * It is recommended that you call this function as early as possible
 * inside the `main` function of your program.
 */
void bbz_particle_init();

/**
 * @brief Start bittybuzz event loop.
 *
 * This function receives one parameter, @p setup, which is a function
 * that will be called once to perform any initialization required by
 * the bittybuzz VM, usually C closure registering.
 *
 * Using the overhead controller it is possible to interrupt the event
 * loop to trigger events such as program start, program reset, and
 * program restart.
 *
 * @param setup put your setup code here, to be run only once.
 */
void bbz_particle_start(void (*setup)(void));


#endif // !BITTYBUZZ_BBZKILOBOT_H
