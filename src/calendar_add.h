
#ifndef CALENDAR_ADD_H
    #define CALENDAR_ADD_H

    #include <TimeLib.h>
    #include <arduino.h>
    #include "calendar.h"
    #include "calendar_date.h"
    
    typedef void (*OnTick_t)(int cPos);  

    struct calendar_addEvent {
        char * name;
        char * desc;
        int id;
        int (*func)(int pos, char * _name, time_t _startValue, time_t _endValue, time_t _repeat, time_t _value, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler);
    } ;
    extern uint8_t calendar_addCount;
    extern calendar_addEvent calendar_add[];

    int calendarAdd(int pos, char * _name, time_t _startValue, time_t _endValue, time_t _repeat, time_t _value, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler);

    void calendarPrint_0(int fPos, int ePos);
    void calendarPrint();
    void calendarPrint_f(int fPos, int ePos, String & s);

#endif
