#include "calendar_add.h"
// #define DEBUG
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

PROGMEM calendar_addEvent calendar_add [] = { 
	{(char*)"weekly", 					(char*)"", 0, &calendarAdd},
	{(char*)"weekly_repeat", 			(char*)"", 1, &calendarAdd},
	{(char*)"daily", 					(char*)"", 2, &calendarAdd},
	{(char*)"daily_repeat", 			(char*)"", 3, &calendarAdd},
	{(char*)"timer_start", 				(char*)"", 4, &calendarAdd},
	{(char*)"timer_start_end", 			(char*)"", 5, &calendarAdd},
	{(char*)"timer_startDay", 			(char*)"", 6, &calendarAdd},
	{(char*)"timer_startDay_endDay", 	(char*)"", 7, &calendarAdd},
	{(char*)"weekly_end", 				(char*)"", 8, &calendarAdd},
	{(char*)"daily_end", 				(char*)"", 9, &calendarAdd},
};
uint8_t calendar_addCount = ARRAY_SIZE(calendar_add);
int calendar_addPos;

int calendarAdd(int pos, char * _name, time_t _startValue, time_t _endValue, time_t _repeat, time_t _value, OnTick_t _onTickHandler, timeDayOfWeek_t _dayOfWeek, OnTick_t _endTickHandler){
	String iName = ce_char_to_string(_name);
	int cPos = -1;
	switch(pos) {
		case 0: 
			cPos = calendar_createWeekly(iName, _value, _onTickHandler, _dayOfWeek, _endTickHandler); 	
			if (cPos != -1) calendar_array[cPos]->pos = 0;
		break;

		case 1: 
			cPos = calendar_createWeekly(iName, _value, _repeat, _endValue, _onTickHandler, _dayOfWeek, _endTickHandler);
			if (cPos != -1) calendar_array[cPos]->pos = 1;
		break;

		case 2: 
			cPos = calendar_createDaily(iName, _value, _onTickHandler, _endTickHandler);			
			if (cPos != -1) calendar_array[cPos]->pos = 2;
		break;	

		case 3: 
			cPos = calendar_createDaily(iName, _value, _repeat, _endValue, _onTickHandler, _dayOfWeek, _endTickHandler);
			if (cPos != -1) calendar_array[cPos]->pos = 3;
		break;	

		case 4: 
			cPos = calendar_createTimer_v1(iName, _startValue, _value, _onTickHandler, _endTickHandler);			
			if (cPos != -1) calendar_array[cPos]->pos = 4;
		break;

		case 5: 
			cPos = calendar_createTimer_v1(iName, _startValue, _endValue, _value, _onTickHandler, _endTickHandler);	
			if (cPos != -1) calendar_array[cPos]->pos = 5;
		break;	

		case 6: 
			cPos = calendar_createTimer_v2(iName, _startValue, _value, _onTickHandler, _endTickHandler);		
			if (cPos != -1) calendar_array[cPos]->pos = 6;
		break;

		case 7: 
			cPos = calendar_createTimer_v2(iName, _startValue, _endValue, _value, _onTickHandler, _endTickHandler);	
			if (cPos != -1) calendar_array[cPos]->pos = 7;
		break;
		
		case 8: 
			cPos = calendar_createWeekly(iName, _value, _endValue, _onTickHandler, _dayOfWeek, _endTickHandler);
			if (cPos != -1) calendar_array[cPos]->pos = 1;
		break;	

		case 9: 
			cPos = calendar_createDaily(iName, _value, _endValue, _onTickHandler, _dayOfWeek, _endTickHandler);
			if (cPos != -1) calendar_array[cPos]->pos = 3;
		break;	

	}
	return cPos;
}

String cal_info_parm(String name, String value , String sep, int len, String last, String tdb1, String tdb2) {
   String s=name;
   int size = s.length();
   while (size<len) s+=" ";
   return tdb1+s+sep+tdb2+value+last;
}
void calendarPrint_0(int fPos, int ePos){
#ifdef DEBUG
	String fName = ce_char_to_string(calendar_add[fPos].name);
	String fDesc = ce_char_to_string(calendar_add[fPos].desc);

	String name;
	String s_period;
	dt_alarmPeriod period;

	time_t value;
	time_t endValue;
	String s_value;

	time_t trigger;
	String s_trigger = "";
	time_t triggerNext;
	String s_triggerNext = "";
	String triggerDay = "";
	String weeklyEvent = "déactiver";
	String dailyEvent = "déactiver";

	String s_rt;
	String s_currentDay;

	String s_repeatValue = "déactiver";

	String s_startValue = "déactiver";;
	String s_endValue = "déactiver";;

	String startTime;
	String createTime;

	String enable;
	String pos;
	String v;

		pos 	= String(ePos);

		enable 	= String(calendar_array[ePos]->isEnabled);

		name 	= calendar_array[ePos]->name;

		value 	= calendar_array[ePos]->value;
		v 				= String(value);

		s_value = timer_toString(value);

		endValue 			= calendar_array[ePos]->endValue;
		period 				= calendar_array[ePos]->period;
		s_period			= calendar_period_to_string(calendar_array[ePos]->period);



		if (calendar_array[ePos]->startValue == -1) {
			trigger 		= calendar_array[ePos]->nextTrigger - now();
		}
		else {
			trigger 		= calendar_array[ePos]->nextTrigger - now();
		}

		if (calendar_array[ePos]->startValue != -1) s_startValue 	= timer_toString(calendar_array[ePos]->startValue);
	
		s_trigger 			= timer_toString(trigger);
		triggerNext 		= now()+trigger;
		s_triggerNext 		= timer_toString(triggerNext);
		triggerDay 			= dayStr(day(value));

		if (period == dtWeeklyRepeatAlarm) 	{
			s_repeatValue 	= timer_toString(calendar_array[ePos]->repeat);
			s_endValue 		= timer_toString(endValue);
		}
		if (period == dtDailyRepeatAlarm) 	{
			s_repeatValue 	= timer_toString(calendar_array[ePos]->repeat);
			s_endValue 		= timer_toString(endValue);
		}
		if (period == dtTimer) 	{
			s_repeatValue 	= timer_toString(calendar_array[ePos]->value);
			if (endValue != -1) s_endValue = timer_toString(endValue);
		}
		if (period == dtDailyAlarm) 	{
		}

		if ((period == dtWeeklyAlarm) 	|| (period == dtWeeklyRepeatAlarm)) weeklyEvent = triggerDay;
		if ((period == dtDailyAlarm) 	|| (period == dtDailyRepeatAlarm)) 	dailyEvent = "activer";

		startTime = timer_toString(calendar_array[ePos]->startTime);
		createTime = timer_toString(calendar_array[ePos]->createTime);

		Serial.flush();

		// yield();
		
		Serial.printf("\n[calendarPrint_0] #%s : %s\n",pos.c_str(), name.c_str());

		String s="";

		s += cal_info_parm("function name", 					fName,        	":", 40, "\n", "", " ");
		s += cal_info_parm("function desc", 					fDesc,        	":", 40, "\n", "", " ");
		s += cal_info_parm("function pos",						String(fPos), 	":", 40, "\n", "", " ");
		s += cal_info_parm("event name",						name,        	":", 40, "\n", "", " ");
		s += cal_info_parm("event pos",							pos,        	":", 40, "\n", "", " ");
		s += cal_info_parm("event period",						s_period,		":", 40, "\n", "", " ");
		s += cal_info_parm("event enable",						enable,        	":", 40, "\n", "", " ");
		s += cal_info_parm("event created",						createTime, 	":", 40, "\n", "", " ");

		s += cal_info_parm("event journalier",					dailyEvent, 	":", 40, "\n", "", " ");
		s += cal_info_parm("event hebdomadaire", 				weeklyEvent, 	":", 40, "\n", "", " ");

		s += cal_info_parm("lancement initial de l'event", 		startTime, 		":", 40, "\n", "", " ");

		s += cal_info_parm("lancement de l'event", 				s_triggerNext, 	":", 40, "\n", "", " ");
		s += cal_info_parm("prochain lancement dans",			s_trigger, 		":", 40, "\n", "", " ");
		s += cal_info_parm("lancement differe", 				s_startValue, 	":", 40, "\n", "", " ");
		s += cal_info_parm("repetition de l'evenat", 			s_repeatValue, 	":", 40, "\n", "", " ");
		s += cal_info_parm("fin de la repetition", 				s_endValue, 	":", 40, "\n", "", " ");

		Serial.printf("%s", s.c_str());

		Serial.printf("[calendarPrint_0] END\n");

		// if (calendar_array[ePos]->period == dtWeeklyRepeatAlarm) {	
		// 	s += cal_info_parm("repetition de l'event",						s_repeatValue, 		":", 18, "\n", "", "   ");}
		// else if (calendar_array[ePos]->period == dtTimer) {
		// 	s += cal_info_parm("repetition de l'event",						s_repeatValue, 		":", 18, "\n", "", "   ");}

	
#endif
}

void calendarPrint_f(int fPos, int ePos, String & s){
// #ifdef DEBUG
	String fName = ce_char_to_string(calendar_add[fPos].name);
	String fDesc = ce_char_to_string(calendar_add[fPos].desc);

	String name;
	String s_period;
	dt_alarmPeriod period;

	time_t value;
	time_t endValue;
	String s_value;

	time_t trigger;
	String s_trigger = "";
	time_t triggerNext;
	String s_triggerNext = "";
	String triggerDay = "";
	String weeklyEvent = "déactiver";
	String dailyEvent = "déactiver";

	String s_rt;
	String s_currentDay;

	String s_repeatValue = "déactiver";

	String s_startValue = "déactiver";;
	String s_endValue = "déactiver";;

	String startTime;
	String createTime;

	String enable;
	String pos;
	String v;

		pos 	= String(ePos);

		enable 	= String(calendar_array[ePos]->isEnabled);

		name 	= calendar_array[ePos]->name;

		value 	= calendar_array[ePos]->value;
		v 				= String(value);

		s_value = timer_toString(value);

		endValue 			= calendar_array[ePos]->endValue;
		period 				= calendar_array[ePos]->period;
		s_period			= calendar_period_to_string(calendar_array[ePos]->period);



		if (calendar_array[ePos]->startValue == -1) {
			trigger 		= calendar_array[ePos]->nextTrigger - now();
		}
		else {
			trigger 		= calendar_array[ePos]->nextTrigger - now();
		}

		if (calendar_array[ePos]->startValue != -1) s_startValue 	= timer_toString(calendar_array[ePos]->startValue);
	
		s_trigger 			= timer_toString(trigger);
		triggerNext 		= now()+trigger;
		s_triggerNext 		= timer_toString(triggerNext);
		triggerDay 			= dayStr(day(value));

		if (period == dtWeeklyRepeatAlarm) 	{
			s_repeatValue 	= timer_toString(calendar_array[ePos]->repeat);
			s_endValue 		= timer_toString(endValue);
		}
		if (period == dtDailyRepeatAlarm) 	{
			s_repeatValue 	= timer_toString(calendar_array[ePos]->repeat);
			s_endValue 		= timer_toString(endValue);
		}
		if (period == dtTimer) 	{
			s_repeatValue 	= timer_toString(calendar_array[ePos]->value);
			if (endValue != -1) s_endValue = timer_toString(endValue);
		}
		if (period == dtDailyAlarm) 	{
		}

		if ((period == dtWeeklyAlarm) 	|| (period == dtWeeklyRepeatAlarm)) weeklyEvent = triggerDay;
		if ((period == dtDailyAlarm) 	|| (period == dtDailyRepeatAlarm)) 	dailyEvent = "activer";

		startTime = timer_toString(calendar_array[ePos]->startTime);
		createTime = timer_toString(calendar_array[ePos]->createTime);

		s="\n[calendarPrint_0] #"+pos+" : "+name+"\n";

		s += cal_info_parm("function name", 					fName,        	":", 40, "\n", "", " ");
		s += cal_info_parm("function desc", 					fDesc,        	":", 40, "\n", "", " ");
		s += cal_info_parm("function pos",						String(fPos), 	":", 40, "\n", "", " ");
		s += cal_info_parm("event name",						name,        	":", 40, "\n", "", " ");
		s += cal_info_parm("event pos",							pos,        	":", 40, "\n", "", " ");
		s += cal_info_parm("event period",						s_period,		":", 40, "\n", "", " ");
		s += cal_info_parm("event enable",						enable,        	":", 40, "\n", "", " ");
		s += cal_info_parm("event created",						createTime, 	":", 40, "\n", "", " ");

		s += cal_info_parm("event journalier",					dailyEvent, 	":", 40, "\n", "", " ");
		s += cal_info_parm("event hebdomadaire", 				weeklyEvent, 	":", 40, "\n", "", " ");

		s += cal_info_parm("lancement initial de l'event", 		startTime, 		":", 40, "\n", "", " ");

		s += cal_info_parm("lancement de l'event", 				s_triggerNext, 	":", 40, "\n", "", " ");
		s += cal_info_parm("prochain lancement dans",			s_trigger, 		":", 40, "\n", "", " ");
		s += cal_info_parm("lancement differe", 				s_startValue, 	":", 40, "\n", "", " ");
		s += cal_info_parm("repetition de l'evenat", 			s_repeatValue, 	":", 40, "\n", "", " ");
		s += cal_info_parm("fin de la repetition", 				s_endValue, 	":", 40, "\n", "", " ");
		s += "\n";

		// if (calendar_array[ePos]->period == dtWeeklyRepeatAlarm) {	
		// 	s += cal_info_parm("repetition de l'event",						s_repeatValue, 		":", 18, "\n", "", "   ");}
		// else if (calendar_array[ePos]->period == dtTimer) {
		// 	s += cal_info_parm("repetition de l'event",						s_repeatValue, 		":", 18, "\n", "", "   ");}

	
// #endif
}

void calendarPrint(){
	for( int i = 0; i < calendar_number_of_event; i++) { 

		if (calendar_array[i] == NULL) continue;
		calendarPrint_0(calendar_array[i]->pos, i);


	}
}