 
#include <stdio.h>
#include <stdlib.h>

#include "XKTimer+.h"

Timer_t timer;
Timer_t timer2;

void Timer_Callback()
{
    printf("Timer Callback!\n");
}

void Timer2_Callback()
{
    printf("Timer2 Callback!\n");
}

int main(int argc, char **argv)
{    
    Timer_Init();
    
    Timer_Add(&timer, TIMER_PERIODIC, 1000, &Timer_Callback);
    Timer_Add(&timer2, TIMER_PERIODIC, 2000, &Timer2_Callback);
    
    Timer_Start(&timer);
    Timer_Start(&timer2);
    
    while (1) {
        Timer_Task();
    }
    
    return 0;
}