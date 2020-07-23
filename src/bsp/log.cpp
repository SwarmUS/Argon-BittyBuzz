#include "log.h"
#include <stdio.h>
#include <stdarg.h>

int Log_Write(int priority, const char *format, ...){
    if (BSP_LOG_PRIORITY <= priority){
        va_list args;
        va_start(args, format);

        size_t string_size = (size_t)vsnprintf(NULL, 0, format, args)+1;
        char* string = (char*) malloc(string_size);

        if(string != NULL){
            vsnprintf(string, string_size, format, args);
            Serial.printlnf(string);
            free(string);
        }
        else {
            Serial.printf("Could not allocate memory for buffer");
        }

        
        va_end(args);
        return 0;
    }
    return 1;
}

int Log_Init(){
    Serial.begin(9600);
    return 0;
}
