/* This header is part of the XKFirmware project */

/*! \file *********************************************************************
 *
 * \brief Timer functions to facilitate timing tasks.
 *
 * \section intro 			Introduction
 * This module uses the global tc_ticks variable to implement a timer
 * which calls a timeout (or callback) function once the timer has timed
 * out. In order to create a new timer, an instance of the timer_t struct
 * must be created and passed to timer_add() or timer_add_dual(). The
 * timer_t struct contains information to keep track of the timer's elapsed
 * time, running status, and a pointer to the timer callback.
 *
 * Currently, there are 3 different types of timer available:
 *  - Single Shot Timer
 *  - Periodic Timer
 *  - Dual State Timer
 *
 * \section internals		Internals
 * The timer module is designed around the cross-platform C++ clock()
 * function. The clock() function usually returns
 *
 * \section timer-example 	Simple Timer Example
 * \code
 *
 * #include "timer.h"
 *
 * timer_t timer;
 *
 * void timer_single_shot()
 * {
 *     // Do stuff...
 *
 *     // You can also change the timeout:
 *     timer_set_timeout(&timer, 5000);
 * }
 *
 * void main()
 * {
 *     // Create a new single shot timer that expires after 1 second
 *     timer_add(&timer, TIMER_SINGLE_SHOT, 1000, &timer_single_shot);
 *
 *     // Now we start the timer
 *     timer_start(&timer);
 *
 *     while (1) {
 *         timer_task();
 *     }
 * }
 *
 * \endcode
 *
 * This code will run the timer_single_shot() function after 1 second of
 * program execution. Also, the above example demonstrates how to restart
 * the timer and also how to change the timeout.
 *
 * A periodic timer functions the same way as a single shot timer, except
 * that TIMER_PERIODIC must be passed to the timer_add() function. A
 * periodic timer will restart the timer upon each timeout as opposed to
 * a single shot timer.
 *
 * \section timer-dual-example	Dual-State Timer Example
 *
 * \code
 *
 * #include <stdio.h>
 *
 * #include "timer.h"
 *
 * timer_t timer;
 *
 * void timer_dual_state(int state)
 * {
 *     // Do some stuff...
 *
 *     printf("State: %d\n", state);
 *
 *     // To change the timeout:
 *     timer_set_timeout_dual(&timer, 1500, 900);
 * }
 *
 * void main()
 * {
 *     // Add a new dual state timer
 *     timer_add_dual(&timer, 700, 300, &timer_dual_state);
 *
 *     // Start the timer...
 *     timer_start(&timer);
 *
 *     while (1) {
 *         timer_task();
 *     }
 * }
 *
 * \endcode
 *
 * The dual-state timer differs from the other timers in that you must
 * specify 2 timeout values rather than simply 1. The dual-state timer
 * functions by using the first specified timeout value to expire, then
 * passes a state of 0 to the callback function. Then, it does the same
 * with the second timeout but passes a state of 1 to the callback
 * function. After this, it restarts itself and runs the first timeout.
 *
 * \note The timer_task() function must be run from the main program loop
 * 		 in order for this module to work, since this function is in charge
 * 		 of keeping track of the list of timers.
 *
 * - Compiler:      	GNU GCC on any platform.
 * - Supported devices: Any device or platform with a milli-second timer.
 *
 * \author 				Jesse L. Zamora - xtremekforever@gmail.com
 *
 ******************************************************************************/

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

/**
 * \name Timer Types
 */
//! @{
/**
 * \brief		Single shot timer
 *
 * This timer simply runs for the specified time until it has timed
 * out, upon which it stops.
 */
#define TIMER_SINGLE_SHOT			1
/**
 * \brief		Periodic timer
 *
 * This timer runs for the specified time and continues until the
 * user stops it.
 */
#define TIMER_PERIODIC				2
//! @}

//! The maximum number of timers available.
#define MAX_TIMERS					30

#define TIMER_NONE					255

#define TIMER_RESOLUTION			1000

#define TIMER_SIZE					sizeof(xktimer_t)
#define TIMER_POINTER_SIZE			sizeof(xktimerp_t)

/**
 * \brief 		The timer vector structure.
 *
 * This timer vector structure allows this module to create an
 * array of timers that contain the timer type, state variables,
 * the timeout, and elapsed time information, as well as a pointer
 * to the callback function.
 */
typedef struct {
	//! The timer type which can be single shot, periodic, or dual-state
	uint8_t type;
	//! If enabled, the timer is running.
	bool enabled;

	//! The first timeout value, used for all timer types
	uint32_t timeout;
	//! Holds the elapsed time
	clock_t tcks;

	//! Pointer to the callback function to call on timeout
	void (*callback)(void);
} xktimer_t;

typedef xktimer_t * xktimerp_t;

/**
 * \brief			Add a new timer to the array
 *
 * Adds a new timer to the array using the specified id, type, timeout,
 * and callback.
 *
 * If the type parameter is anything other than single shot or periodic, it
 * will be set to single shot by default.
 *
 * \param timer		A pointer to the timer struct to add
 * \param type		The timer type to use.
 * \param timeout	The timeout in ms for this timer. This can be changed by
 * 					calling timer_set_timeout() with the ID after the timer has
 * 					been created.
 * \param callback	A pointer to the callback function to call upon timeout.
 *
 * \return TRUE		Successfully added timer
 * \return FALSE	Either the timer already existed or it exceeded the maximum
 * 					number of timers.
 */
extern void timer_add(xktimer_t * timer,
					  uint8_t type,
					  int timeout,
					  void (*callback)());

/**
 * \brief			Get the next timeout for the given timer
 *
 * This function calculates how many ms are left before the given timer
 * will time out.
 *
 * \param timer			A pointer to the timer to calculate the next
 * 						timeout from.
 *
 * \retval uint32_t		The next timeout value in ms.
 */
extern clock_t timer_next_timeout(xktimer_t * timer);

/**
 * \brief			Set the timeout for the given timer
 *
 * \param id		The ID of the timer to modify.
 * \param timeout	The timeout value to set.
 */
extern void timer_set_timeout(xktimer_t * timer,
							   uint32_t timeout);

/**
 * \brief			Starts the specified timer
 *
 * This routine resets the elapsed time and sets the enabled field to 1.
 *
 * \param id		The ID of the desired timer.
 */
extern void timer_start(xktimer_t * timer);

/**
 * \brief			Stops the specified timer
 *
 * This routine resets the elapsed time and sets the enabled field to 0.
 *
 * \param id		The ID of the desired timer.
 */
extern void timer_stop(xktimer_t * timer);

/**
 * \brief			Returns the timer running state.
 *
 * \param id		The ID of the desired timer
 *
 * \return TRUE		The timer is running.
 * \return FALSE	The timer is NOT currently running.
 */
extern bool timer_running(xktimer_t * timer);

/**
 * \brief			Handles all the timer tasks for this module.
 *
 * This routine simply keeps track of the elapsed times for the various
 * timers in the timer_vector array. Upon a timer timing out, this function
 * will run the callback function and for dual-state timers, will set the
 * state variable to continue on to the next state.
 */
extern void timer_task();

extern bool timer_periodic(clock_t * tcks, uint32_t period);

extern void timer_handle(xktimer_t * timer);

extern void timer_wait(int ms);

#endif
