#include "log.h"
#include <stdarg.h>

int Log_Write(int priority, const char *format, ...){
    if (BSP_LOG_PRIORITY <= priority){
        va_list args;
        va_start(args, format);

        Serial.printlnf(format, args);
        
        va_end(args);

        return 0;
    }

    return 1;
}

int Log_Init(){
    Serial.begin(9600);
    return 0;
}
