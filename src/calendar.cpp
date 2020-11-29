#include "calendar.h"

// #define DEBUG

int calendar_number_of_event=0; 
int calendar_event_selected= 0; 
calendar * calendar_array[EVENT_MAX];


calendar::calendar()
{
    if (calendar_number_of_event < EVENT_MAX) {

    	objPos = calendar_number_of_event;
        calendar_array[calendar_number_of_event++] = this;

    } else {
    	#ifdef DEBUG
    	Serial.printf("\n[calendar] FUUUUUUUUUUULLLLLLLL\n");
    	#endif
    }
}

/*  
    calendar_createWeekly : 
    (String _name, time_t _value, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek)
        every day   : slected week day with : _dayOfWeek
        start time  : start at the _value
        end at      : at the start time
        repeat      : none
*/
int calendar_createWeekly(String _name, time_t _value, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler){
	if (calendar_number_of_event < EVENT_MAX) {
		int pos = calendar_number_of_event;

		new calendar();

		calendar_array[pos]->createTime     = now();
		calendar_array[pos]->o_endValue 	= -1;
		calendar_array[pos]->isEnabled 		= true;
		calendar_array[pos]->name 			= _name;
		calendar_array[pos]->onTickHandler 	= _onTickHandler;
		calendar_array[pos]->endTickHandler = _endTickHandler;
		calendar_array[pos]->period			= dtWeeklyAlarm;
		calendar_array[pos]->dayOfWeek		= _dayOfWeek;
		calendar_array[pos]->startValue 	= -1;
		calendar_array[pos]->endValue 		= -1;
		calendar_array[pos]->value 			= (_dayOfWeek-1) * SECS_PER_DAY + _value;
		calendar_array[pos]->startTime 		= _value;
		calendar_array[pos]->nextTrigger 	= _value;
		// if ((_value + previousSunday(now())) <= now()) {
		// 	calendar_array[pos]->nextTrigger = _value + nextSunday(now());
		// } else {
		// 	calendar_array[pos]->nextTrigger = _value + previousSunday(now());
		// }			
		return pos;
	}
}


/*  
    calendar_createWeekly : 
    (String _name, time_t _value, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek)
        every day   : slected week day with : _dayOfWeek
        start time  : start at the _value
        end at      : at (start time + _endValue)
        repeat      : none
*/
int calendar_createWeekly(String _name, time_t _value, time_t _endValue, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler){
	if (calendar_number_of_event < EVENT_MAX) {
		int pos = calendar_number_of_event;

		new calendar();

		calendar_array[pos]->createTime     = now();
		calendar_array[pos]->o_endValue 	= _endValue;
		calendar_array[pos]->isEnabled 		= true;
		calendar_array[pos]->name 			= _name;
		calendar_array[pos]->onTickHandler 	= _onTickHandler;
		calendar_array[pos]->endTickHandler = _endTickHandler;
		calendar_array[pos]->period			= dtWeeklyEndAlarm;
		calendar_array[pos]->dayOfWeek		= _dayOfWeek;
		calendar_array[pos]->startValue 	= -1;
		calendar_array[pos]->endValue 		= (_dayOfWeek-1) * SECS_PER_DAY + (_value + _endValue);
		calendar_array[pos]->value 			= (_dayOfWeek-1) * SECS_PER_DAY + _value;
		calendar_array[pos]->startTime 		= _value;
		calendar_array[pos]->nextTrigger 	= _value;
		// if ((_value + previousSunday(now())) <= now()) {
		// 	calendar_array[pos]->nextTrigger = _value + nextSunday(now());
		// } else {
		// 	calendar_array[pos]->nextTrigger = _value + previousSunday(now());
		// }			
		return pos;
	}
}
int calendar_editWeekly(calendar * obj, time_t _value, time_t _endValue, boolean enabled){
		timeDayOfWeek_t _dayOfWeek 	= obj->dayOfWeek;
		obj->o_endValue 			= _endValue;
		obj->startValue 			= -1;
		obj->endValue 				= (_dayOfWeek-1) * SECS_PER_DAY + (_value + _endValue);
		obj->value 					= (_dayOfWeek-1) * SECS_PER_DAY + _value;
		obj->startTime 				= _value;
		obj->nextTrigger 			= _value;
		if ( (obj->endValue + previousSunday(now())) <= now()) { 
			Serial.printf("\n[calendar_createWeekly] : up to tomorrow\n");
			obj->nextTrigger = _value + nextSunday(now());
			
		}				
}

/*  
    calendar_createWeekly : 
    (String _name, time_t _value, time_t _repeat, time_t _endValue, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek)
        every day   : slected week day with : _dayOfWeek
        start time  : start at the _value
        end at      : at the (start time + _endValue)
        repeat      : every _repeat
*/ 
int calendar_createWeekly(String _name, time_t _value, time_t _repeat, time_t _endValue, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler){
	if (calendar_number_of_event < EVENT_MAX) {
		int pos = calendar_number_of_event;

		new calendar();

		calendar_array[pos]->createTime     = now();
		calendar_array[pos]->o_endValue 	= _endValue;
		calendar_array[pos]->isEnabled 		= true;
		calendar_array[pos]->name 			= _name;
		calendar_array[pos]->onTickHandler 	= _onTickHandler;
		calendar_array[pos]->endTickHandler = _endTickHandler;
		calendar_array[pos]->period			= dtWeeklyRepeatAlarm;
		calendar_array[pos]->dayOfWeek		= _dayOfWeek;
		calendar_array[pos]->repeat 		= _repeat;
		calendar_array[pos]->startValue 	= -1;
		calendar_array[pos]->endValue 		= (_dayOfWeek-1) * SECS_PER_DAY + (_value + _endValue);
		calendar_array[pos]->value 			= (_dayOfWeek-1) * SECS_PER_DAY + _value;
		calendar_array[pos]->startTime 		= _value;
		calendar_array[pos]->nextTrigger 	= _value;
		return pos;
	}
}

int calendar_editWeekly(calendar * obj, time_t _value, time_t _repeat, time_t _endValue, boolean enabled){
		timeDayOfWeek_t _dayOfWeek 	= obj->dayOfWeek;
		obj->o_endValue 			= _endValue;
		obj->repeat 				= _repeat;
		obj->startValue 			= -1;
		obj->endValue 				= (_dayOfWeek-1) * SECS_PER_DAY + (_value + _endValue);
		obj->value 					= (_dayOfWeek-1) * SECS_PER_DAY + _value;
		obj->startTime 				= _value;
		obj->nextTrigger 			= _value;
		if ( (obj->endValue + previousSunday(now())) <= now()) { 
			Serial.printf("\n[calendar_createWeekly] : up to tomorrow\n");
			obj->nextTrigger = _value + nextSunday(now());
			
		}				
}


/*  
    calendar_createDaily :
    (String _name, time_t _value, OnTick_t _onTickHandler)
        every day   : all day
        start time  : start at the _value
        end at      : at the start time
        repeat      : 
*/ 
int calendar_createDaily(String _name, time_t _value, OnTick_t _onTickHandler, OnTick_t _endTickHandler){
	if (calendar_number_of_event < EVENT_MAX) {
		int pos = calendar_number_of_event;

		new calendar();

		calendar_array[pos]->createTime     = now();
		calendar_array[pos]->o_endValue 	= -1;
		calendar_array[pos]->isEnabled 		= true;
		calendar_array[pos]->name 			= _name;
		calendar_array[pos]->onTickHandler 	= _onTickHandler;
		calendar_array[pos]->endTickHandler = _endTickHandler;		
		calendar_array[pos]->period			= dtDailyAlarm;
		calendar_array[pos]->dayOfWeek		= dowInvalid;
		calendar_array[pos]->startValue 	= -1;
		calendar_array[pos]->endValue 		= -1;
		calendar_array[pos]->startTime 		= _value;
		if (_value + previousMidnight(now()) <= now()) {
				calendar_array[pos]->value 	= _value + nextMidnight(now());
		} else 	calendar_array[pos]->value 	= _value;		
		calendar_array[pos]->nextTrigger 	= calendar_array[pos]->value;
		return pos;
	}
}
int calendar_editDaily(calendar * obj, time_t _value, boolean enabled){
		obj->o_endValue 	= -1;
		obj->startValue 	= -1;
		obj->endValue 		= -1;
		obj->startTime 		= _value;
		if (_value + previousMidnight(now()) <= now()) {
				obj->value 	= _value + nextMidnight(now());
		} else 	obj->value 	= _value;		
		obj->nextTrigger 	= obj->value;
}

/*  
    calendar_createDaily :
   calendar_createDaily(iName, _value, _repeat, _endValue, _onTickHandler, _dayOfWeek);
        every day   : all day
        start time  : start at the _value
        end at      : at the (_value + _endValue)
        repeat      : none
*/ 
int calendar_createDaily(String _name, time_t _value, time_t _endValue, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler){
	if (calendar_number_of_event < EVENT_MAX) {
		int pos = calendar_number_of_event;

		new calendar();

		calendar_array[pos]->createTime     = now();
		calendar_array[pos]->o_endValue		= _endValue;
		calendar_array[pos]->isEnabled 		= true;
		calendar_array[pos]->isOneShot 		= true;
		calendar_array[pos]->name 			= _name;
		calendar_array[pos]->onTickHandler 	= _onTickHandler;
		calendar_array[pos]->endTickHandler = _endTickHandler;		
		calendar_array[pos]->period			= dtDailyEndAlarm;
		calendar_array[pos]->dayOfWeek		= _dayOfWeek;
		calendar_array[pos]->startValue 	= -1;
		calendar_array[pos]->startTime 		= _value;
		if ((_value+_endValue) + previousMidnight(now()) <= now()) {
			// Serial.printf("\nset nextmidnight\n");
				calendar_array[pos]->value 	= _value + nextMidnight(now());
		} else 	calendar_array[pos]->value 	= _value;	
		calendar_array[pos]->endValue 		= calendar_array[pos]->value + _endValue;
		calendar_array[pos]->nextTrigger 	= calendar_array[pos]->value;
		return pos;
	}
}
int calendar_editDaily(calendar * obj, time_t _value, time_t _endValue, boolean enabled){
		obj->startValue 	= -1;
		obj->o_endValue 	= _endValue;
		obj->startTime 		= _value;
		if ((_value+_endValue) + previousMidnight(now()) <= now()) {
				obj->value 	= _value + nextMidnight(now());
		} else 	obj->value 	= _value;	
		obj->endValue 		= obj->value + _endValue;
		obj->nextTrigger 	= obj->value;
}

/*  
    calendar_createDaily :
   calendar_createDaily(iName, _value, _repeat, _endValue, _onTickHandler, _dayOfWeek);
        every day   : all day
        start time  : start at the _value
        end at      : at the (_value + _endValue)
        repeat      : every _repeate
*/ 
int calendar_createDaily(String _name, time_t _value, time_t _repeat, time_t _endValue, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler){
	if (calendar_number_of_event < EVENT_MAX) {
		int pos = calendar_number_of_event;

		new calendar();

		calendar_array[pos]->createTime     = now();
		calendar_array[pos]->o_endValue		= _endValue;
		calendar_array[pos]->isEnabled 		= true;
		calendar_array[pos]->name 			= _name;
		calendar_array[pos]->onTickHandler 	= _onTickHandler;
		calendar_array[pos]->endTickHandler = _endTickHandler;		
		calendar_array[pos]->period			= dtDailyRepeatAlarm;
		calendar_array[pos]->dayOfWeek		= _dayOfWeek;
		calendar_array[pos]->repeat 		= _repeat;
		calendar_array[pos]->startValue 	= -1;
		calendar_array[pos]->startTime 		= _value;
		if ((_value+_endValue) + previousMidnight(now()) <= now()) {
			// Serial.printf("\nset nextmidnight\n");
				calendar_array[pos]->value 	= _value + nextMidnight(now());
		} else 	calendar_array[pos]->value 	= _value;	
		calendar_array[pos]->endValue 		= calendar_array[pos]->value + _endValue;
		calendar_array[pos]->nextTrigger 	= calendar_array[pos]->value;
		return pos;
	}
}
int calendar_editDaily(calendar * obj, time_t _value, time_t _repeat, time_t _endValue, boolean enabled){
		obj->repeat 		= _repeat;
		obj->startValue 	= -1;
		obj->o_endValue 	= _endValue;
		obj->startTime 		= _value;
		if ((_value+_endValue) + previousMidnight(now()) <= now()) {
				obj->value 	= _value + nextMidnight(now());
		} else 	obj->value 	= _value;	
		obj->endValue 		= obj->value + _endValue;
		obj->nextTrigger 	= obj->value;
}

/*	
	timer repeat : 
		(String _name, time_t _startValue, time_t _value, OnTick_t _onTickHandler)
		start 	: at the start time + _startValue
		end at 	: 
		repeat 	: every _value
*/
int calendar_createTimer_v1(String _name, time_t _startValue, time_t _value, OnTick_t _onTickHandler, OnTick_t _endTickHandler){
	if (calendar_number_of_event < EVENT_MAX) {
		int pos = calendar_number_of_event;

		new calendar();
		_startValue = now() + _startValue;

		calendar_array[pos]->createTime     = now();
		calendar_array[pos]->o_endValue		= -1;
		calendar_array[pos]->isEnabled 		= true;
		calendar_array[pos]->name 			= _name;
		calendar_array[pos]->onTickHandler 	= _onTickHandler;
		calendar_array[pos]->endTickHandler = _endTickHandler;		
		calendar_array[pos]->period			= dtTimer;
		calendar_array[pos]->dayOfWeek		= dowInvalid;
		calendar_array[pos]->repeat 		= -1;
		calendar_array[pos]->endValue 		= -1;
		calendar_array[pos]->value 			= _value;		
		calendar_array[pos]->startValue 	= _startValue;
		calendar_array[pos]->startTime 		= _startValue;
		calendar_array[pos]->nextTrigger 	= _value;
		return pos;
	}
}
/*	
	timer repeat : 
		(String _name, time_t _startValue, time_t _endValue, time_t _value, OnTick_t _onTickHandler)
		start 	: at the start time + _startValue
		end at 	: at the start time + _endvalue
		repeat 	: every _value
*/
int calendar_createTimer_v1(String _name, time_t _startValue, time_t _endValue, time_t _value, OnTick_t _onTickHandler, OnTick_t _endTickHandler){
	if (calendar_number_of_event < EVENT_MAX) {
		int pos = calendar_number_of_event;

		new calendar();

		calendar_array[pos]->o_endValue		= _endValue;

		_startValue = now() + _startValue;
		_endValue 	= now() + _endValue;

		calendar_array[pos]->createTime     = now();
		calendar_array[pos]->isEnabled 		= true;
		calendar_array[pos]->name 			= _name;
		calendar_array[pos]->onTickHandler 	= _onTickHandler;
		calendar_array[pos]->endTickHandler = _endTickHandler;		
		calendar_array[pos]->period			= dtTimer;
		calendar_array[pos]->dayOfWeek		= dowInvalid;
		calendar_array[pos]->startTime 		= _startValue;
		calendar_array[pos]->startValue 	= _startValue;
		calendar_array[pos]->endValue 		= _endValue;
		calendar_array[pos]->value 			= _value;
		calendar_array[pos]->nextTrigger 	= _value;
		return pos;
	}
}

/*  
    timer repeat : 
        (String _name, time_t _startValue, time_t _value, OnTick_t _onTickHandler)
        start   : at the _startValue
        end at  : 
        repeat  : every _value
*/
int calendar_createTimer_v2(String _name, time_t _startValue, time_t _value, OnTick_t _onTickHandler, OnTick_t _endTickHandler){
	if (calendar_number_of_event < EVENT_MAX) {
		int pos = calendar_number_of_event;

		new calendar();

		calendar_array[pos]->o_endValue		= -1;

		calendar_array[pos]->createTime     = now();
		calendar_array[pos]->isEnabled 		= true;
		calendar_array[pos]->name 			= _name;
		calendar_array[pos]->onTickHandler 	= _onTickHandler;
		calendar_array[pos]->endTickHandler = _endTickHandler;		
		calendar_array[pos]->period			= dtTimer;
		calendar_array[pos]->dayOfWeek		= dowInvalid;
		calendar_array[pos]->startValue 	= _startValue;
        if (_startValue + previousMidnight(now()) <= now()) {
          	calendar_array[pos]->startValue = _startValue + nextMidnight(now());
        } else {
          	calendar_array[pos]->startValue = _startValue + previousMidnight(now());
        }
		calendar_array[pos]->startTime 		= _startValue;
		calendar_array[pos]->endValue 		= -1;
		calendar_array[pos]->value 			= _value;
		calendar_array[pos]->nextTrigger 	= _value;
		return pos;
	}
}
/*  
    timer repeat : 
        (String _name, time_t _startValue, time_t _endValue, time_t _value, OnTick_t _onTickHandler)
        start   : at the _startValue
        end at  : at the _endValue
        repeat  : every _value
*/
int calendar_createTimer_v2(String _name, time_t _startValue, time_t _endValue, time_t _value, OnTick_t _onTickHandler, OnTick_t _endTickHandler){
	if (calendar_number_of_event < EVENT_MAX) {
		int pos = calendar_number_of_event;

		new calendar();
		
		calendar_array[pos]->o_endValue		= _endValue;

		calendar_array[pos]->createTime     = now();
		calendar_array[pos]->isEnabled 		= true;
		calendar_array[pos]->name 			= _name;
		calendar_array[pos]->onTickHandler 	= _onTickHandler;
		calendar_array[pos]->endTickHandler = _endTickHandler;		
		calendar_array[pos]->period			= dtTimer;
		calendar_array[pos]->dayOfWeek		= dowInvalid;
		calendar_array[pos]->startValue 	= _startValue;
        if (_startValue + previousMidnight(now()) <= now()) {
          	calendar_array[pos]->startValue = _startValue + nextMidnight(now());
        } else {
          	calendar_array[pos]->startValue = _startValue + previousMidnight(now());
        }
		calendar_array[pos]->endValue 		= _endValue;
        if (_endValue + previousMidnight(now()) <= now()) {
          	calendar_array[pos]->endValue = _endValue + nextMidnight(now());
        } else {
          	calendar_array[pos]->endValue = _endValue + previousMidnight(now());
        }
        calendar_array[pos]->startTime 		= _startValue;
		calendar_array[pos]->value 			= _value;
		calendar_array[pos]->nextTrigger 	= now()+_value;
		return pos;
	}
}

int calendar_edit(calendar * obj, time_t _value, time_t _repeat, time_t _endValue, boolean enabled){
	if (obj->period == dtDailyAlarm) 		{calendar_editDaily(obj, _value, enabled);}
	if (obj->period == dtDailyRepeatAlarm) 	{calendar_editDaily(obj, _value, _repeat, _endValue, enabled);}
	if (obj->period == dtDailyEndAlarm) 	{calendar_editDaily(obj, _value, _endValue, enabled);}
	if (obj->period == dtWeeklyRepeatAlarm)	{calendar_editWeekly(obj, _value, _repeat, _endValue, enabled);}
	if (obj->period == dtWeeklyEndAlarm)	{calendar_editWeekly(obj, _value, _endValue, enabled);}

}

String timer_toString(time_t t) {
    char tmpStr[100];
    sprintf(tmpStr, "%02d:%02d:%02d", hour(t), minute(t), second(t));
    return String(tmpStr);
}

time_t calendar::currentTrigger() {return nextTrigger - now();}

int calendar::setNext(){ 
		time_t time = now();

		if (period == dtExplicitAlarm) {

		} else if (period == dtDailyAlarm) {		
			nextTrigger = value + nextMidnight(time);
		} else if (period == dtDailyRepeatAlarm) {
			nextTrigger = value + nextMidnight(time);	
		} else if (period == dtDailyEndAlarm) {
			nextTrigger = value + nextMidnight(time);					
		} else if (period == dtWeeklyAlarm) {
			nextTrigger = value + nextSunday(time);	
		} else if (period == dtWeeklyEndAlarm) {
			nextTrigger = value + nextSunday(time);
		} else if (period == dtWeeklyRepeatAlarm) {
			nextTrigger = value + nextSunday(time);			
		} else {

		}
}


boolean calendar::isRepeatAlarm(){ 
	if (period == dtDailyRepeatAlarm) 	return true; 
	if (period == dtWeeklyRepeatAlarm) 	return true; 
	return false;
}

int calendar::updateNextTrigger(int pos){

	time_t time = now();

	if (dtIsAlarm(period) && nextTrigger <= time) {

		if (period == dtExplicitAlarm) {
			// is the value a specific date and time in the future
			nextTrigger = value;  // yes, trigger on this value
			return 1;
		} else if (period == dtDailyAlarm) {		
			if ((value + previousMidnight(now())) <= time) {
				#ifdef DEBUG
					Serial.printf("\n\t[1 dtDailyAlarm] pos: %d - [%s <= %s] %s -> upd: time has passed then set for tomorrow.\n", 
						pos, timer_toString(endValue + previousMidnight(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + nextMidnight(time)).c_str());						
				#endif
				nextTrigger = value + nextMidnight(time);
				return 1;									
			}	
			else {
				#ifdef DEBUG
					Serial.printf("\n\t[0 dtDailyAlarm] pos: %d - [%s >= %s] %s -> upd: set the date to today and add the time given in value\n", 
						pos, timer_toString(value + previousMidnight(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + previousMidnight(time)).c_str());
				#endif					
				nextTrigger = value + previousMidnight(time);
				return 0;
			}
		} else if (period == dtDailyRepeatAlarm) {
			if ((value + previousMidnight(now())) <= time) {
				if ( (endValue) <= time) {
					#ifdef DEBUG
						Serial.printf("\n\t[1 dtDailyRepeatAlarm] pos: %d - [%s <= %s] %s -> upd: repeat.\n", 
							pos, timer_toString(endValue).c_str(), timer_toString(time).c_str(), timer_toString(time + repeat).c_str());
					#endif
					nextTrigger = time + repeat;

				}
				if (endValue + previousMidnight(now()) <= time) {
					#ifdef DEBUG
						Serial.printf("\n\t[2 dtDailyRepeatAlarm] pos: %d - [%s <= %s] %s -> upd: time has passed then set for tomorrow.\n", 
							pos, timer_toString(endValue + previousMidnight(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + nextMidnight(time)).c_str());						
					#endif
					nextTrigger = value + nextMidnight(time);
					return 2;
				}
				return 1;
			} else {
				#ifdef DEBUG
					Serial.printf("\n\t[0 dtDailyRepeatAlarm] pos: %d - [%s >= %s] %s -> upd: set the date to today and add the time given in value\n", 
						pos, timer_toString(value + previousMidnight(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + previousMidnight(time)).c_str());
				#endif
				nextTrigger = value + previousMidnight(time);
				return 0;
			}	
		} else if (period == dtDailyEndAlarm) {
			if ((value + previousMidnight(now())) <= time) {
				if (isOneShot){
					isOneShot= false;
					return 1;
				}	
				if (endValue + previousMidnight(now()) <= time) {
					#ifdef DEBUG
						Serial.printf("\n\t[2 dtDailyRepeatAlarm] pos: %d - [%s <= %s] %s -> upd: time has passed then set for tomorrow.\n", 
							pos, timer_toString(endValue + previousMidnight(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + nextMidnight(time)).c_str());						
					#endif
					isOneShot= true;	
					nextTrigger = value + nextMidnight(time);
					return 2;
				}
				
			} else {
				#ifdef DEBUG
					Serial.printf("\n\t[0 dtDailyRepeatAlarm] pos: %d - [%s >= %s] %s -> upd: set the date to today and add the time given in value\n", 
						pos, timer_toString(value + previousMidnight(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + previousMidnight(time)).c_str());
				#endif
				isOneShot= true;	
				nextTrigger = value + previousMidnight(time);
				return 0;
			}						
		} else if (period == dtWeeklyAlarm) {
			if ((value + previousSunday(now())) <= time) {
				#ifdef DEBUG
					Serial.printf("\n\t[1 dtWeeklyAlarm] pos: %d - [%s <= %s] %s -> upd: time has passed then set for the next week.\n", 
						pos, timer_toString(value + previousSunday(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + nextSunday(time)).c_str());						
				#endif
				nextTrigger = value + nextSunday(time);
				return 1;
			} else {
				#ifdef DEBUG
					Serial.printf("\n\t[0 dtWeeklyAlarm] pos: %d - [%s >= %s] %s -> upd: set the date to today and add the time given in value\n", 
						pos, timer_toString(value + previousSunday(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + previousSunday(time)).c_str());
				#endif
				nextTrigger = value + previousSunday(time);
				return 0;
			}
		} else if (period == dtWeeklyEndAlarm) {
			if ( (value + previousSunday(now())) <= time) {
				if (isOneShot){
					isOneShot= false;
					return 1;
				}			
				if ( (endValue + previousSunday(now())) <= time) { 
					#ifdef DEBUG
						Serial.printf("\n\t[2 dtWeeklyEndAlarm] pos: %d - [%s <= %s] %s -> upd: time has passed then set for the next week.\n", 
							pos, timer_toString(endValue + previousSunday(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + nextSunday(time)).c_str());						
					#endif
					nextTrigger = value + nextSunday(time);
					isOneShot = true;
					return 2;
				}
				
			} else {
				#ifdef DEBUG
					Serial.printf("\n\t[0 dtWeeklyRepeatAlarm] pos: %d - [%s >= %s] %s -> upd: set the date to today and add the time given in value\n", 
						pos, timer_toString(value + previousSunday(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + previousSunday(time)).c_str());
				#endif
				nextTrigger = value + previousSunday(time);
				isOneShot = true;
				return 0;
			}

		} else if (period == dtWeeklyRepeatAlarm) {
			if ( (value + previousSunday(now())) <= time) {
				if ( (endValue) <= time) {
					#ifdef DEBUG
						Serial.printf("\n\t[1 dtWeeklyRepeatAlarm] pos: %d - [%s <= %s] %s -> upd: repeat.\n", 
							pos, timer_toString(endValue).c_str(), timer_toString(time).c_str(), timer_toString(time + repeat).c_str());
					#endif
					nextTrigger = time + repeat;
				}
				if ( (endValue + previousSunday(now())) <= time) { 
					#ifdef DEBUG
						Serial.printf("\n\t[2 dtWeeklyRepeatAlarm] pos: %d - [%s <= %s] %s -> upd: time has passed then set for the next week.\n", 
							pos, timer_toString(endValue + previousSunday(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + nextSunday(time)).c_str());						
					#endif
					nextTrigger = value + nextSunday(time);
					return 2;
				}
				return 1;
			} else {
				#ifdef DEBUG
					Serial.printf("\n\t[0 dtWeeklyRepeatAlarm] pos: %d - [%s >= %s] %s -> upd: set the date to today and add the time given in value\n", 
						pos, timer_toString(value + previousSunday(now())).c_str(), timer_toString(time).c_str(), timer_toString(value + previousSunday(time)).c_str());
				#endif
				nextTrigger = value + previousSunday(time);
				return 0;
			}
					
		} else {
			// its not a recognized alarm type - this should not happen
				#ifdef DEBUG
					Serial.printf("\n\t[updateNextTrigger dtDailyAlarm] pos: %d - eventName: %s - upd:its not a recognized alarm type, this should not happen\n", pos, name.c_str());
				#endif
				return 0;
			// Mode.isEnabled = false;  // Disable the alarm
		}
	} 
	if (period == dtTimer) {
		#ifdef DEBUG
			Serial.printf("\n\t[updateTrigger dtTimer] pos: %d - eventName: %s - upd: -\n", pos, name.c_str());
		#endif
		nextTrigger = time + value;
		return 1;
	}	
	return -1;
}


String calendar_period_to_string(dt_alarmPeriod mod) {
	String ret;
	switch (mod) {
		case dtNotAllocated: 		ret = "dtNotAllocated"; 		break;
		case dtTimer: 				ret = "dtTimer"; 				break;
		case dtExplicitAlarm: 		ret = "dtExplicitAlarm"; 		break;
		case dtDailyAlarm: 			ret = "dtDailyAlarm"; 			break;
		case dtDailyRepeatAlarm:	ret = "dtDailyRepeat"; 			break;
		case dtWeeklyAlarm: 		ret = "dtWeeklyAlarm"; 			break;
		case dtWeeklyEndAlarm: 		ret = "dtWeeklyEndAlarm";		break;
		case dtWeeklyRepeatAlarm:	ret = "dtWeeklyRepeat";			break;
		case dtDailyEndAlarm:		ret = "dtDailyEndAlarm";		break;
	}
	return ret;
}
boolean calendar_firstRound = false;
void calendar_update_all() {

	for( int i = 0; i < calendar_number_of_event; i++) { 

		calendar_event_selected = -1;

		if (calendar_array[i] == NULL) continue;

		// if (!calendar_array[i]->isEnabled) continue;

		if ((calendar_array[i]->isEnabled) && (calendar_array[i]->period == dtTimer) ){ 
			if (calendar_array[i]->endValue != -1) { 
				if ((now() >= calendar_array[i]->endValue)) {
					#ifdef DEBUG
						Serial.printf("endValue: %s\n", timer_toString(calendar_array[i]->endValue).c_str() );
						Serial.printf("now: %s\n", timer_toString(now()).c_str() );
					#endif
					calendar_array[i]->isEnabled 	= false;
					continue;	
				}
			}
		}

		if (calendar_array[i]->startValue != -1) {

			if ((now() >= calendar_array[i]->startValue)) {

				if ( (now() >= calendar_array[i]->nextTrigger)) {

					calendar_array[i]->startValue = -1;

					int upd = calendar_array[i]->updateNextTrigger(i);
					if (calendar_array[i]->isEnabled) {
						OnTick_t TickHandler 	= calendar_array[i]->onTickHandler;
						OnTick_t endTickHandler = calendar_array[i]->endTickHandler;						
						if ((calendar_array[i]->period == dtDailyAlarm) || (calendar_array[i]->period == dtWeeklyAlarm)) {  
							if ((upd == 1 ) && (TickHandler != NULL)) {
								// Serial.printf("\n{test 2 1} %s\n", calendar_array[i]->name.c_str());
								calendar_event_selected = i;
								(*TickHandler)(i);
								(*endTickHandler)(i);						
							}				
						} else {
							if ((upd == 1 ) && (TickHandler != NULL)) {
								calendar_event_selected = i;
								(*TickHandler)(i);     // call the handler
							}	
							if ((upd == 2 ) && (endTickHandler != NULL)) {
								// Serial.printf("\n{test 1 3} %s\n", calendar_array[i]->name.c_str());
								calendar_event_selected = i;
								(*endTickHandler)(i);
							}											
						}
					}
				}
			}

		} else {

			if ( (now() >= calendar_array[i]->nextTrigger)) {

				int upd = calendar_array[i]->updateNextTrigger(i);
				if (!calendar_firstRound) {
					continue;
				}
				if (calendar_array[i]->isEnabled) {
					OnTick_t TickHandler 	= calendar_array[i]->onTickHandler;
					OnTick_t endTickHandler = calendar_array[i]->endTickHandler;					
					if ((calendar_array[i]->period == dtDailyAlarm) || (calendar_array[i]->period == dtWeeklyAlarm)) { 

						if ((upd == 1 ) && (TickHandler != NULL)) {
							// Serial.printf("\n{test 2 1} %s\n", calendar_array[i]->name.c_str());
							calendar_event_selected = i;
							(*TickHandler)(i);
							(*endTickHandler)(i);						
						}
					} else {
						if ((upd == 1 ) && (TickHandler != NULL)) {
							calendar_event_selected = i;
							(*TickHandler)(i);     // call the handler
						}
						if ((upd == 2 ) && (endTickHandler != NULL)) {
							// Serial.printf("\n{test 2 3} %s\n", calendar_array[i]->name.c_str());
							calendar_event_selected = i;
							(*endTickHandler)(i);
						}											
					}		
				}		
			}
		}
		
	}
	if (!calendar_firstRound) {
		calendar_firstRound = true;
	}	
}

