/* This source file is part of the XKFirmware project */

/*! \file *********************************************************************
 *
 * \brief Timer functions to facilitate timing tasks.
 *
 * Go to timer.h for full timer documentation.
 *
 * \author 				Jesse L. Zamora - xtremekforever@gmail.com
 *
 ******************************************************************************/

/* Standard Library Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* Time Includes */
#include <assert.h>
#include <time.h>

#include "xktimer.h"

/*#ifndef clock
extern clock_t clock();
#endif*/

/**
 * \brief		The array of timers.
 *
 * This array is used to store the various timers in use. The ID of the
 * timer is the same as the index in this array, so the ID cannot be
 * larger than MAX_TIMERS or the program will fail.
 */
xktimerp_t *	timer_ref;

//! The index of the last added timer + 1
int	 			timer_ref_idx;

int timer_ref_size()
{
    int size =  sizeof(timer_ref) / TIMER_POINTER_SIZE;
	return size;
}

void timer_init()
{
	timer_ref = (xktimerp_t *)malloc(1 * TIMER_POINTER_SIZE);
	timer_ref_idx = 0;
    
    printf("XKTimer Init\n");
    printf("Timer Resolution: %d\n", TIMER_RESOLUTION);
    printf("Clocks Per Sec: %ld\n", CLOCKS_PER_SEC);
}

clock_t timer_clock()
{
	return clock() / (CLOCKS_PER_SEC / TIMER_RESOLUTION);
}

bool timer_assert(xktimer_t * timer)
{
	return timer != NULL;
}

void timer_update_tcks(xktimer_t * timer)
{
	if (!timer_assert(timer)) return;

	timer->tcks = timer_clock() + timer->timeout;
}

void timer_add(xktimer_t * timer, uint8_t type, int timeout, void (*callback)())
{
	if (!timer_assert(timer)) return;

	timer->type = type;
	timer->enabled = false;
	timer->timeout = timeout;
	timer->callback = callback;

	timer_update_tcks(timer);

	if (timer_ref == NULL) {
		return;
	} else {
		if (timer_ref_idx + 1 >= timer_ref_size()) {
			// Reallocate for more timers
			timer_ref = (xktimerp_t *)realloc(timer_ref, (timer_ref_idx + 1) * TIMER_POINTER_SIZE);
		}
	}

	// Allocate the memory for this timer pointer
	timer_ref[timer_ref_idx] = (xktimerp_t)malloc(TIMER_POINTER_SIZE);
	// Now copy the pointer to the timer struct
	timer_ref[timer_ref_idx] = timer;
	// Increment for the next timer
	timer_ref_idx++;
}

clock_t timer_next_timeout(xktimer_t * timer)
{
	if (!timer_assert(timer)) return 0;

	return timer->tcks - clock();
}

void timer_set_timeout(xktimer_t * timer, uint32_t timeout)
{
	if (!timer_assert(timer)) return;

	// Set the timeout value
	timer->timeout = timeout;
	// Now update the timer ticks
	timer_update_tcks(timer);
}

void timer_start(xktimer_t * timer)
{
	if (!timer_assert(timer)) return;

	timer->enabled = true;

	timer_update_tcks(timer);
}

void timer_stop(xktimer_t * timer)
{
	if (!timer_assert(timer)) return;

	timer->enabled = false;
}

bool timer_running(xktimer_t * timer)
{
	if (!timer_assert(timer)) return false;

	return timer->enabled;
}

void timer_wait(int ms)
{
	clock_t timestamp = timer_clock();

	while (timer_clock() < timestamp + ms) {
		//watchdog_clear();
	}
}

bool timer_periodic(clock_t * tcks, uint32_t period)
{
	if (timer_clock() >= *tcks + period) {
		*tcks = timer_clock();
		return true;
	}

	return false;
}

void timer_handle(xktimer_t * timer)
{
	if (!timer_assert(timer)) return;

	if (!timer->enabled) return;

	if (timer_clock() >= timer->tcks) {

		if (timer->type == TIMER_SINGLE_SHOT) {
			timer->enabled = false;
		}

		timer_update_tcks(timer);

		if (timer->callback) {
			timer->callback();
		}
	}
}

void timer_task()
{
	int i;

	for (i = 0; i < timer_ref_idx; i++) {
		timer_handle(timer_ref[i]);
	}
}
