#include <adri_wifi.h>
#include <adri_tools.h>

// NTP GET REAL TIME
#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

static const    char            ntpServerName[]     = "fr.pool.ntp.org";    // NTP Servers:
const           int             timeZone            = 1;                    // Central European Time
                unsigned int    localPort           = 8888;                 // local port to listen for UDP packets
                WiFiUDP         Udp;
                time_t          prevDisplay         = 0; 

void sendNTPpacket(IPAddress &address);

#include <calendar.h>

boolean debug_calendar_printAll = true;

void myFunc_1(int cPos){
    // Serial.printf("\n\t[myFunc_1]\n");

    int pos = calendar_event_selected;
    // if(pos >= 0) calendarPrint_0(calendar_array[pos]->pos, pos);

}



int* splitTime(String Val) {
    String      aVal            = Val;
    byte        firstIndex      = aVal.indexOf('.');
    byte        secondIndex     = aVal.indexOf('.', firstIndex + 1);
    String      hr              = aVal.substring(0, firstIndex);
    String      minute          = aVal.substring(firstIndex + 1, secondIndex);
    String      sec             = aVal.substring(secondIndex + 1);
    int         _hr             = hr.toInt();
    int         _minute         = minute.toInt();
    int         _sec            = sec.toInt();

    int     *array          = new int[3];
            array[0]        = _hr;
            array[1]        = _minute;
            array[2]        = _sec;
    return array;    
}


void setup()
{
        Serial.begin(115200);
        

    // CONNECT TO WIFI
    IPAddress no_ip = {0, 0, 0, 0};
    wifi_connect_sta("xxx", "xxx", no_ip, no_ip, no_ip);
    // PRINT NETWORK INFOS
    // String s = network_info("DEVICENAME");
    // fsprintln(s.c_str());

    // INIT NTP
    Udp.begin(localPort);
    setSyncProvider(getNtpTime);
    setSyncInterval(10000);

    delay(1000);

    // SET DAY
    char* cDay = dayStr(weekday());
    Serial.printf("%s\n", cDay);
    // int search_day = calendar_date_get_dow("fr", "Vendredi"); 
    int search_day = calendar_date_get_dow("en", String(cDay)); 
    timeDayOfWeek_t thisDay = dowSunday;
    if (search_day >= 0) {
        Serial.printf("\ncalendar_date_get_dow: %s - %s - %s\n", calendar_dates[search_day].day_en, calendar_dates[search_day].day_fr, dayStr(search_day));
        thisDay = calendar_dates[search_day].dow;
    }

    // SPLIT TIME FROM STRING
    String str_time = "13.05.15";
    int *split_time = splitTime(str_time);
    Serial.printf("\nsplittime: %d - %d - %d\n", split_time[0], split_time[1], split_time[2]);


    // SET TIME FOR EVENT TEST
    time_t t1 = AlarmHMS(0,0,10);
    time_t t2 = AlarmHMS(hour(),minute(),second()) + AlarmHMS(0,10,0);
    time_t t3 = AlarmHMS(hour(),minute(),second()) + AlarmHMS(0,0,20);
    time_t t4 = AlarmHMS(0,1,0);
    time_t t5 = AlarmHMS(9,27,0);

// (                        pos,                _name,     _startValue,    _endValue,          _repeat,    _value,     _onTickHandler, _dayOfWeek)
    /*  
        calendar_createWeekly : 
        (String _name, time_t _value, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek)
            every day   : slected week day with : _dayOfWeek
            start time  : start at the _value
            end at      : at the start time
            repeat      : none
    */    
    // calendar_add[0].func(   calendar_add[0].id,     "t1",   -1,             -1,                 -1,         t3,         myFunc_1,       thisDay);
    /*  
        calendar_createWeekly : 
        (String _name, time_t _value, time_t _repeat, time_t _endValue, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek)
            every day   : slected week day with : _dayOfWeek
            start time  : start at the _value
            end at      : at the (start time + _endValue)
            repeat      : every _repeat
    */       
    calendar_add[1].func(   calendar_add[1].id,  "t1",      -1,             AlarmHMS(0,5,0),    10,         t5,         myFunc_1,       thisDay,     myFunc_1);
    /*  
        calendar_createDaily :
        (String _name, time_t _value, OnTick_t _onTickHandler)
            every day   : all day
            start time  : start at the _value
            end at      : at the start time
            repeat      : every _value
    */ 
    // calendar_add[2].func(   calendar_add[2].id,  "t1",      -1,             -1,                 -1,         t5,         myFunc_1,       dowInvalid,     myFunc_1);
    /*  
        calendar_createDaily :
       calendar_createDaily(iName, _value, _repeat, _endValue, _onTickHandler, _dayOfWeek);
            every day   : all day
            start time  : start at the _value
            end at      : at the (_value + _endValue)
            repeat      : every _repeate
    */     
    // calendar_add[3].func(   calendar_add[3].id,  "t1",      -1,             AlarmHMS(0,5,0),    AlarmHMS(0,0,30),         t3,         myFunc_1,       dowInvalid,     myFunc_1);
    /*  
        timer repeat : 
            (String _name, time_t _startValue, time_t _value, OnTick_t _onTickHandler)
            start   : at the start time + _startValue
            end at  : 
            repeat  : every _value
    */    
    // calendar_add[4].func(   calendar_add[4].id,  "t1",      t1,             -1,                 -1,         t4,     myFunc_1,       dowInvalid);



    /*  
        timer repeat : 
            (String _name, time_t _startValue, time_t _value, OnTick_t _onTickHandler)
            start   : at the start time + _startValue
            end at  : 
            repeat  : every _value
    */
    // calendar_createTimer_v1("simple repeat", AlarmHMS(0,0,10), 20,  myFunc_3);

    /*  
        timer repeat : 
            (String _name, time_t _startValue, time_t _endValue, time_t _value, OnTick_t _onTickHandler)
            start   : at the start time + _startValue
            end at  : at the start time + _endvalue
            repeat  : every _value
    */
    // calendar_createTimer_v1("simple repeat", AlarmHMS(0,0,10), AlarmHMS(0,1,0), 20,  myFunc_3); 

    /*  
        timer repeat : 
            (String _name, time_t _startValue, time_t _value, OnTick_t _onTickHandler)
            start   : at the _startValue
            end at  : 
            repeat  : every _value
    */
    // calendar_createTimer_v2("simple repeat", t2, 20,  myFunc_3);

    /*  
        timer repeat : 
            (String _name, time_t _startValue, time_t _endValue, time_t _value, OnTick_t _onTickHandler)
            start   : at the _startValue
            end at  : at the _endValue
            repeat  : every _value
    */
    // calendar_createTimer_v2("simple repeat", t2, t3, 10,  myFunc_3);   
  
}

void loop()
{
    calendar_update_all() ;
    // return;
    if (now() != prevDisplay) { 
        prevDisplay = now();
        // calendar_update_all() ;
        
        // calendar_print_all() ;

    }   
    keyboard_loop  ();
}
void calendar_test(){
        fsprintf("\n[%s]\n", timer_toString(now()).c_str());

    for( int i = 0; i < calendar_number_of_event; i++) { 

        fsprintf("#%-5d[nextTrigger: %10s]",i ,timer_toString(calendar_array[i]->nextTrigger).c_str());
        fsprintf(" [value+pm: %10s]" ,timer_toString(calendar_array[i]->value+previousMidnight(now())).c_str());
        fsprintfs("\n");



    }
}
void calendar_print_all() {

    if (!debug_calendar_printAll) return;

    String name;
    String period;

    time_t value;
    String s_value;

    time_t trigger;
    String s_trigger = "";
    time_t triggerNext;
    String s_triggerNext = "";
    String triggerDay = "";

    String s_rt;
    String s_currentDay;

    String s_repeatValue = "";

    String s_startValue;
    String s_endValue;

    String enable;
    String pos;
    String v;

        s_rt            = timer_toString(now());
        s_currentDay    = dayStr(weekday(now()));

    Serial.printf("\n[calendar_print_all] %s %s \n", s_currentDay.c_str(), s_rt.c_str() );
    for( int i = 0; i < calendar_number_of_event; i++) { 

        if (calendar_array[i] == NULL) continue;


        pos     = String(i);
        while (pos.length()<5) pos+=" ";

        enable  = String(calendar_array[i]->isEnabled);
        while (enable.length()<5) enable+=" ";

        name    = calendar_array[i]->name;
        while (name.length()<10) name+=" ";

        value   = calendar_array[i]->value;
        v               = String(value);
        while (v.length()<10) v+=" ";

        s_value = timer_toString(value);
        while (s_value.length()<10) s_value+=" ";

        if (calendar_array[i]->period == dtTimer)               {s_repeatValue = timer_toString(value);}
        if (calendar_array[i]->period == dtWeeklyRepeatAlarm)   {s_repeatValue = timer_toString(calendar_array[i]->repeat);}
        if (calendar_array[i]->period == dtDailyRepeatAlarm)    {s_repeatValue = timer_toString(calendar_array[i]->repeat);}

        while (s_repeatValue.length()<10) s_repeatValue+=" ";

        period  = calendar_period_to_string(calendar_array[i]->period);
        while (period.length()<14) period+=" ";


        if (calendar_array[i]->isEnabled) {

            if (calendar_array[i]->endValue != -1) {
                s_endValue      = timer_toString(calendar_array[i]->endValue);
            } else s_endValue   = "";

            if (calendar_array[i]->startValue == -1) {
                trigger         = calendar_array[i]->nextTrigger - now();
                s_startValue    = "";
            }
            else {
                trigger         = calendar_array[i]->startValue - now();
                s_startValue    = timer_toString(calendar_array[i]->startValue);
            }   

            s_trigger           = timer_toString(trigger);
            triggerNext         = now()+trigger;
            s_triggerNext       = timer_toString(triggerNext);

            if (calendar_array[i]->period == dtWeeklyAlarm)         triggerDay = dayStr(day(value));
            if (calendar_array[i]->period == dtWeeklyRepeatAlarm)   triggerDay = dayStr(day(value));
            if (calendar_array[i]->period == dtDailyRepeatAlarm)    triggerDay = dayStr(weekday(triggerNext));
            if (calendar_array[i]->period == dtDailyAlarm)          triggerDay = dayStr(weekday(triggerNext));
            if (calendar_array[i]->period == dtTimer)               triggerDay = dayStr(weekday()); 

        } else {
            s_endValue   = "";
            s_startValue = "";
            s_trigger = "";
            s_triggerNext = "";
            triggerDay = "";
        }

        while (s_trigger.length()<10)       s_trigger+=" ";
        while (s_triggerNext.length()<10)   s_triggerNext+=" ";
        while (triggerDay.length()<10)      triggerDay+=" ";
        while (s_startValue.length()<10)    s_startValue+=" ";      
        while (s_endValue.length()<10)      s_endValue+=" ";    



            Serial.printf("pos: %s enable: %s name: %s period: %s V: %s R: %s StV: %s EnV: %s TI: %s TND: %s TN: %s\n", 
                pos.c_str(), 
                enable.c_str(), 
                name.c_str(), 
                period.c_str(), 
                s_value.c_str(), 
                s_repeatValue.c_str(),
                s_startValue.c_str(),
                s_endValue.c_str(),
                s_trigger.c_str(),
                triggerDay.c_str(),
                s_triggerNext.c_str());     

                        
    }

    Serial.printf("\n[calendar_print_all] END\n" );

}
String toggle(boolean *f, String s) {
    boolean b=*f;
    b=!b;
    *f=b;
    String t=s+" "; t+=(b)?"on":"off";
    return t + "\n";
}
String user_menu_info(){
    String s;

    s += "w = restart esp\n";
    s += "a = debug calender_printAll\n";
    s += "z = calendar_print_all\n";
    s += "e = del\n";
    s = "\n[MENU]\n" + s + "\n";
    return s;
}
String user_menu(char c) {
    String s;
    String send_str;

    switch (c) {
        case 'm' : s = user_menu_info();                                            break;
        case 'a' : toggle(&debug_calendar_printAll, "debug_calendar_printAll");     break;
        case 'z' : calendar_print_all();                                            break;
        case 'e' : calendarPrint();                                                 break;
        case 'r' : calendar_test();                                                 break;

        case 'w' : 
            s = "ESP.reset";
            delay(1000);
            ESP.reset(); 
            break;


        default  : if  (c!=char(10) && (c!=char(13)) ) { s= "command "+String(c)+" not known (ASCII " + String(int(c)) + ")\n";  }
    }
    return s;
}
void keyboard_setup (){}
void keyboard_end   (){}
void keyboard_loop  (){
    // char input[20];
    // if (ADwfifi_telnet_get(input)) {
    //     char c=input[0];
    //     String s=user_menu(c);
    //     debug_mode=both;
    //     ADwfifi_debug(&s);
    // }   
    if (Serial.available()) {
        char c=Serial.read();
        String s=user_menu(c);
        // debug_mode=both;
        debugPrint(s);
    }


}


bool IsDst(int hour, int day, int month, int dow)  //north american dst  dow 0=SUN
{
    // if (WebServer.daylight == false) return false; //option to disable DST

                                                     //January, february, and december are out.
    if (month < 3 || month > 11) { return false; }
    //April to October are in
    if (month > 3 && month < 11) { return true; }
    int previousSunday = day - dow;
    //In march, we are DST if our previous sunday was on or after the 8th.
    if (month == 3) { return previousSunday >= 8; }
    //In november we must be before the first sunday to be dst.
    //That means the previous sunday must be before the 1st.
    return previousSunday <= 0;
}

/*-------- NTP code ----------*/
const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime() {

    IPAddress ntpServerIP; // NTP server's ip address

    while (Udp.parsePacket() > 0) ; // discard any previously received packets
    // Serial.println("Transmit NTP Request");
    // get a random server from the pool
    WiFi.hostByName(ntpServerName, ntpServerIP);
    Serial.print(ntpServerName);
    Serial.print(": ");
    Serial.println(ntpServerIP);
    sendNTPpacket(ntpServerIP);
    uint32_t beginWait = millis();
    while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
        // Serial.println("Receive NTP Response");
        Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
        unsigned long secsSince1900;
        // convert four bytes starting at location 40 to a long integer
        secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
        secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
        secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
        secsSince1900 |= (unsigned long)packetBuffer[43];
        // return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;

        secsSince1900 = secsSince1900 - 2208988800UL + (timeZone * SECS_PER_HOUR);
        if (IsDst(hour(secsSince1900), day(secsSince1900), month(secsSince1900), dayOfWeek(secsSince1900) - 1)) secsSince1900 += 3600;  //add hour if DST           
        return secsSince1900;
    }
  }
  // Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

