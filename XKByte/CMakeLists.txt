 
project (XKByteTest)

set ( xkbyte_srcs
   byte.c
   includes.h
)

add_executable ( xkbyte-test main.c ${xkbyte_srcs} )
target_link_libraries( xkbyte-test )
