
#ifndef CALENDAR_DATE_H
    #define CALENDAR_DATE_H

    #include <TimeLib.h>
    #include <arduino.h>

    struct calendar_date {
        char            * day_en;
        char            * day_fr;
        timeDayOfWeek_t  dow;
        // int     position;
        // int     type;
        // int     load;
        // String  (* getValue ) ();
        // void    (* setValue ) (String value);
        // void    (* set ) (String value);
    } ;

    int calendar_date_get_dow(String country, String day); 
    int calendar_date_get_dow(String country, char* day); 
    String calendar_date_get_dowStr(String country, String day) ;

    String ce_char_to_string(char * name);

    extern uint8_t calendar_dateCount;
    extern calendar_date calendar_dates[];

    struct calendar_month {
        char            * mon_en;
        char            * mon_fr;
        char            * mon_short;

    } ;

    extern uint8_t calendar_monthCount;
    extern calendar_month calendar_months[];    
    int calendar_date_get_mon(String country, String mon); 
    int calendar_date_get_mon(String country, char* mon); 
    String calendar_date_get_monStr(String country, String day) ;
    
#endif
