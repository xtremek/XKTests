 

#include <stdio.h>
#include <stdlib.h>

#include "xktimer.h"

xktimer_t timer;
xktimer_t timer2;

void timer_callback()
{
    printf("Timer Callback!\n");
}

void timer2_callback()
{
    printf("Timer2 Callback!\n");
}

int main(int argc, char **argv)
{
    timer_init();
    
    timer_add(&timer, TIMER_PERIODIC, 1000, &timer_callback);
    timer_add(&timer2, TIMER_PERIODIC, 2000, &timer2_callback);
    
    timer_start(&timer);
    timer_start(&timer2);
    
    while (1) {
        timer_task();
    }
    
    return 0;
}