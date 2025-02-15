#include <avr/pgmspace.h>

const PROGMEM int8_t biases[] = {
    0, 0, 0, 0, 0, 0, 0, 0,  
    4, 0, 0, 0, 1, 0, 0, 0,  
    -1, -2, 3, -1,  
};


const PROGMEM int8_t weights[] = {
    -1, 0, 1, 1, 0, -1, 0, -1, 1, 1, 0, 0, 0, -1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, -1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, 0, -1, 0, 0, -1, 0, 1, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, -1, 0, 0, 0, 0, 1, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, -1, -1, 0, 1, 0, 0, 0, -1, 0, 0, 0, 1, 0, -1, 0, 1, -1, 0, -1, 0, -1, 1, -1, 1, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, -1, 0, 0, 0, -1, 1, -1, 1, -1, 0, 0, 1, -1, 0, 0, 0, 0, 1, -1, 0, -1, 0, 0, 1, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 1, 0, 0, 1, -1, 1, 1, 1, -1, 1, -1, 0, 1, 1, -1, 1, -1, -1, 1, 0, -1, 0, -1, 1, 1, 0, 0, 1, 0, 0, 1, -1, -1, 1, 0, 0, 0, -1, -1, 1, 0, 0, 1, 0, 0, 0, -1, 0, 0, 1, 0, 1, -1, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, -1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, 1, 0, -1, 0, 0, 1, 1, 1, -1, 1, -1, 1, 0, 0, 0, 1, 0, 1, 0, 1, -1, 1, 0, 1, 0, 0, 0, 0, -1, 0, 1, 0, 0,  
    -1, 0, 0, 1, 1, 0, -1, 0, 1, 0, 0, -1, -1, 0, 1, 0, 1, 0, -1, 0, 1, 0, 0, 0, 0, -1, 0, 1, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, -1, -1, 1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, -1, -1, 0, 0, -1, -1, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1, 0, 0, -1, 0, 0, 0, -1, -1, 0, 1, -1, 0, 0, -1, 0, 1, 0, 0, -1, -1, 0, 1, -1, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, -1, 1, -1, 0, -1, 1, 0, 1, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, -1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, -1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, -1, -1, 0, 1, 1, 0, 0, 0, 0, 1, 1,  
    0, -1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, -1, 1, 1, 0, 0, -1, -1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 1, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, -1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 1, 0, -1, 1, 0, -1, 0, 0, 0, 0, 0, 1, 1, -1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, -1, 1, 0, 1, 0, -1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, -1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, -1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, -1, 0, -1, 0, 0, -1, 0, 0, -1, 0, 1, 0, 0,  
    0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, -1, 0, 1, 0, 1, 0, -1, -1, 1, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 1, -1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, -1, 1, 0, 0, 1, 0, -1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 1, 0, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, -1, -1, 0, 1, 1, 0, -1, -1, -1, 0, 0, -1, 0, 1, -1, 0, 0, 1, 0, 0, -1, 0, 1, 0, -1, 0, 0, 0, 0, 0, -1, 0, -1, 0, 1, 0, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, -1, -1, 1, 0, 0, 0, 0, -1, 0, -1, 0, 0, -1, 0, 1, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1,  
    1, -1, 0, 0, -1, 0, 1, -1, 0, -1, 0, 1, 1, -1, 0, 0, 0, 1, 1, -1, 0, 0, 0, 0, 0, -1, 0, -1, 1, 0, 0, -1, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 1, -1, 0, -1, 0, 0, 1, 0, -1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, -1, 0, 0, 0, 1, 0, -1, 1, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 1, 0, -1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, -1, 0, 0, 0, 0, -1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, -1, 0, -1, 0, 0, 0, 1, 1, -1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, -1, 1, 1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 1, 0, -1, 0, 1, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 1, 1, 0, -1, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, -1, 1, 0, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, -1,  
    -1, -1, 0, 1, 1, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, -1, -1, 1, 0, 0, -1, -1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 1, 1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 1, -1, 1, 0, 0, 1, 1, -1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 1, 0, 0, -1, -1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 1, 0, 0, 0, -1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, -1, -1, 1, 0, 0, 0, -1, -1, 0, 1, 1, 0, 0, -1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, -1, -1, 0, 2, 1, 0, 0, -1, 0, 0, 1, 1, -1, 0, 0, 1, 0, 0, 0,  
    -1, 1, -1, 0, 1, 0, 0, -1, -1, 0, 1, -1, 0, 0, -1, -1, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, 1, 1, -1, -1, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, -1, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 1, 0, 0, 1, 0, 0, -1, -1, 0, 0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, -1, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, 0, -1, 0, -1, 0, 0, 0, -2, -1, 0, 0, 0, 0, -1, -1, 0, -1, -1, 0, 0, 0, -1, -1, 0, 0, -1, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, -1, -1, -1, 0, 0, 0, -1, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, -1, 0, 0, 1, -2, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 1, -1, 0, 0, 0, -1, 1, -1, 0, 0, -1,  
    0, 0, 1, 0, 0, 0, -1, 1, 0, 1, 0, 0, -1, 0, 1, 0, 1, -1, -1, -1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, -1, 0, 1, 0, 0, 0, -1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, -1, 0, 0, 1, -1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, -1, 0, -1, 1, 0, 0, 0, 0, 1, 1, 0, -1, 0, -1, 0, 0, 0, 0, 0, -1, 1, 0, -1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, -1, -1, 0, 1, 0, 0, -1, 0, 1, 1, 0, -1, -1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, -1, -1, 0, 0, 0, 0, 0,  

    0, 0, -1, -2, -2, 2, 3, 2,  
    3, 3, 1, 1, -1, 3, 3, 3,  
    -1, -1, -1, -2, 0, 0, -1, -2,  
    -2, 3, -2, 0, 2, -3, -2, -2,  
    4, 3, 0, 3, -3, -4, -3, -3,  
    -1, 2, 0, 3, -3, -2, 1, -3,  
    1, -3, 4, 3, 4, 3, 3, 3,  
    0, -1, 0, -1, -1, 2, 3, 2,  

    -2, 3, 0, 0, -2, 2, 0, 0,  
    -5, -1, 3, 0, 2, 1, 1, -2,  
    2, -2, -2, -1, 3, -3, -3, -4,  
    -3, 0, -3, 0, 4, -5, -3, -4,  
};