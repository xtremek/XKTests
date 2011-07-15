 
project (XKTimerTest)

set ( xktimer_srcs
    xktimer.c
)  

add_executable ( xktimer-test main.c ${xktimer_srcs} )
add_executable ( xktimer-plus-test main+.c ${xktimer_srcs} )
target_link_libraries( xktimer-test )
target_link_libraries( xktimer-plus-test )