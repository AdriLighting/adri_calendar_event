
#ifndef CALENDAR_H
	#define CALENDAR_H
	#include <TimeLib.h>
   	#include <arduino.h>
	#include "calendar_date.h"
	#include "calendar_add.h"

	extern "C" {
		#include "user_interface.h"
	}	 
	
	#define EVENT_MAX 16

	#define AlarmHMS(_hr_, _min_, _sec_) (_hr_ * SECS_PER_HOUR + _min_ * SECS_PER_MIN + _sec_)

	#define dtIsAlarm(_type_)  (_type_ >= dtExplicitAlarm && _type_ < dtLastAlarmType)

	typedef enum {
		dtMillisecond,
		dtSecond,
		dtMinute,
		dtHour,
		dtDay
	} dtUnits_t;


	typedef enum {
		dtNotAllocated,
		dtTimer,
		dtExplicitAlarm,
		dtDailyAlarm,
		dtDailyEndAlarm,
  		dtDailyRepeatAlarm,
		dtWeeklyAlarm,
		dtWeeklyEndAlarm,
		dtWeeklyRepeatAlarm,
		dtLastAlarmType
	} dt_alarmPeriod ;


	typedef void (*OnTick_t)(int cPos);  

	class calendar {
		public:
			int 				objPos;
			int 				pos;
			String 				name;

			time_t 				createTime 	= 0;
			time_t 				startTime 	= 0;

			time_t 				value 		= 0;
			time_t 				startValue 	= 0;
			time_t 				endValue 	= 0;
			time_t 				o_endValue 	= -1;
			time_t 				repeat 		= 0;
			time_t 				nextTrigger	= 0;
			
			OnTick_t 			onTickHandler;
			OnTick_t 			endTickHandler;

			dt_alarmPeriod 		period;
			timeDayOfWeek_t 	dayOfWeek;

			boolean 			isEnabled;  
			boolean 			isOneShot =true;  

			calendar();
				time_t 	currentTrigger();
				int 	updateNextTrigger(int pos);
				int 	setNext();
				boolean isRepeatAlarm();
	};

    extern int calendar_number_of_event; 
    extern int calendar_event_selected;
    extern calendar * calendar_array[];

	String 	calendar_period_to_string(dt_alarmPeriod mod);
	void 	calendar_update_all() ;	

	int 	calendar_createWeekly(String _name, time_t _value, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler);
	int 	calendar_createWeekly(String _name, time_t _value, time_t _repeat, time_t _endValue, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler);

	int 	calendar_createWeekly(String _name, time_t _value, time_t _endValue, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler);

	int 	calendar_createDaily(String _name, time_t _value, OnTick_t _onTickHandler, OnTick_t _endTickHandler);
	int 	calendar_createDaily(String _name, time_t _value, time_t _repeat, time_t _endValue, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler);

	int 	calendar_createDaily(String _name, time_t _value, time_t _endValue, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler);
	
	int 	calendar_createTimer_v1(String _name, time_t _startValue, time_t _value, OnTick_t _onTickHandler, OnTick_t _endTickHandler);
	int 	calendar_createTimer_v1(String _name, time_t _startValue, time_t _endValue, time_t _value, OnTick_t _onTickHandler, OnTick_t _endTickHandler);

	int 	calendar_createTimer_v2(String _name, time_t _startValue, time_t _value, OnTick_t _onTickHandler, OnTick_t _endTickHandler);	
	int 	calendar_createTimer_v2(String _name, time_t _startValue, time_t _endValue, time_t _value, OnTick_t _onTickHandler, OnTick_t _endTickHandler);

	String timer_toString(time_t t);

	int calendar_edit(calendar * obj, time_t _value, time_t _repeat, time_t _endValue, boolean enabled);
#endif

// // attempt to create an alarm and return true if successful
// AlarmID_t TimeAlarmsClass::create(time_t value, OnTick_t onTickHandler, uint8_t isOneShot, dtAlarmPeriod_t alarmType)
// {
//   if ( ! ( (dtIsAlarm(alarmType) && now() < SECS_PER_YEAR) || (dtUseAbsoluteValue(alarmType) && (value == 0)) ) ) {
//     // only create alarm ids if the time is at least Jan 1 1971
//     for (uint8_t id = 0; id < dtNBR_ALARMS; id++) {
//       if (Alarm[id].Mode.alarmType == dtNotAllocated) {
//         // here if there is an Alarm id that is not allocated
//         Alarm[id].onTickHandler = onTickHandler;
//         Alarm[id].Mode.isOneShot = isOneShot;
//         Alarm[id].Mode.alarmType = alarmType;
//         Alarm[id].value = value;
//         enable(id);
//         return id;  // alarm created ok
//       }
//     }
//   }
//   return dtINVALID_ALARM_ID; // no IDs available or time is invalid
// }

		// 	if ( (value + endValue) <= time) {

		// 		Serial.printf("\n\t[updateNextTrigger dtWeeklyRepeatAlarm] eventName: %s - upd: day has passed then set for the next week.\n", name.c_str());
		// 		nextTrigger = value + nextSunday(time);
		// 		endValue = -1;	
		// 		return 1;	
		// 	} 	

		// if (calendar_array[i]->period == dtWeeklyRepeatAlarm) { 
		// 	if (calendar_array[i]->endValue != -1) { 
		// 		time_t wr_t = calendar_array[i]->endValue ;
		// 		String wr_s = timer_toString(wr_t);
		// 		String s_rt = timer_toString(now());
		// 		if (now() >= wr_t) {
		// 			Serial.printf("\n\t[updateNextTrigger dtWeeklyRepeatAlarm] eventName: %s | %s - %s - upd: day has passed then set for the next week.\n", s_rt.c_str(), wr_s.c_str(), calendar_array[i]->name.c_str());
		// 			calendar_array[i]->nextTrigger = calendar_array[i]->value + nextSunday(now());
		// 		}
		// 	}
		// }				