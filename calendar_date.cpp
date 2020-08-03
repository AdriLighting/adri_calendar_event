#include "calendar_date.h"
#include "calendar.h"

char PROGMEM dayStr0_en [] = "Err";
char PROGMEM dayStr1_en [] = "Sunday";
char PROGMEM dayStr2_en [] = "Monday";
char PROGMEM dayStr3_en [] = "Tuesday";
char PROGMEM dayStr4_en [] = "Wednesday";
char PROGMEM dayStr5_en [] = "Thursday";
char PROGMEM dayStr6_en [] = "Friday";
char PROGMEM dayStr7_en [] = "Saturday";

char PROGMEM dayStr0_fr [] = "Err";
char PROGMEM dayStr1_fr [] = "Dimanche";
char PROGMEM dayStr2_fr [] = "Lundi";
char PROGMEM dayStr3_fr [] = "Mardi";
char PROGMEM dayStr4_fr [] = "Mercredi";
char PROGMEM dayStr5_fr [] = "Jeudi";
char PROGMEM dayStr6_fr [] = "Vendredi";
char PROGMEM dayStr7_fr [] = "Samedi";

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

PROGMEM calendar_date calendar_dates [] = { 
	{dayStr0_en, dayStr0_fr, dowInvalid},
	{dayStr1_en, dayStr1_fr, dowSunday},
	{dayStr2_en, dayStr2_fr, dowMonday},
	{dayStr3_en, dayStr3_fr, dowTuesday},
	{dayStr4_en, dayStr4_fr, dowWednesday},
	{dayStr5_en, dayStr5_fr, dowThursday},
	{dayStr6_en, dayStr6_fr, dowFriday},
	{dayStr7_en, dayStr7_fr, dowSaturday},
};
uint8_t calendar_dateCount = ARRAY_SIZE(calendar_dates);

String ce_char_to_string(char * name){
    char buffer[200];
    sprintf(buffer, "%s", name);
    return String(buffer);
}

int calendar_date_get_dow(String country, String day) {
	int ret = -1;
	String iDay;
	for (int i = 0; i < calendar_dateCount; ++i) {
		if (country == "fr") iDay = ce_char_to_string(calendar_dates[i].day_fr);
		if (country == "en") iDay = ce_char_to_string(calendar_dates[i].day_en);

		if ( iDay == day) {
			ret = i;
			break;
		}
		
	}
	return ret;
}
String calendar_date_get_dowStr(String country, String day) {
    	// Serial.printf("\n[calendar_date_get_dowStr] search_day: %s\n", day.c_str());
	
	String ret = "";
	String iDay;
	for (int i = 0; i < calendar_dateCount; ++i) {
		if (country == "fr") iDay = ce_char_to_string(calendar_dates[i].day_fr);
		if (country == "en") iDay = ce_char_to_string(calendar_dates[i].day_en);

		if ( iDay == day) {
			if (country == "en") ret = ce_char_to_string(calendar_dates[i].day_fr);
			if (country == "fr") ret = ce_char_to_string(calendar_dates[i].day_en);
			break;
		}
		
	}
	return ret;
}

int calendar_date_get_dow(String country, char* day) {
	int ret = -1;
	char* iDay;
	for (int i = 0; i < calendar_dateCount; ++i) {
		if (country == "fr") iDay = calendar_dates[i].day_fr;
		if (country == "en") iDay = calendar_dates[i].day_en;

		if ( iDay == day) {
			ret = i;
			break;
		}
		
	}
	return ret;
}


char PROGMEM monthStr0_en []  = "Err";
char PROGMEM monthStr1_en []  = "January";
char PROGMEM monthStr2_en []  = "February";
char PROGMEM monthStr3_en []  = "March";
char PROGMEM monthStr4_en []  = "April";
char PROGMEM monthStr5_en []  = "May";
char PROGMEM monthStr6_en []  = "June";
char PROGMEM monthStr7_en []  = "July";
char PROGMEM monthStr8_en []  = "August";
char PROGMEM monthStr9_en []  = "September";
char PROGMEM monthStr10_en []  = "October";
char PROGMEM monthStr11_en []  = "November";
char PROGMEM monthStr12_en []  = "December";

char PROGMEM monthStr0_fr []  = "Err";
char PROGMEM monthStr1_fr []  = "Janvier";
char PROGMEM monthStr2_fr []  = "Fevrier";
char PROGMEM monthStr3_fr []  = "Mars";
char PROGMEM monthStr4_fr []  = "Avril";
char PROGMEM monthStr5_fr []  = "Mai";
char PROGMEM monthStr6_fr []  = "Juin";
char PROGMEM monthStr7_fr []  = "Juillet";
char PROGMEM monthStr8_fr []  = "Aout";
char PROGMEM monthStr9_fr []  = "Septembre";
char PROGMEM monthStr10_fr []  = "Octobre";
char PROGMEM monthStr11_fr []  = "Novembre";
char PROGMEM monthStr12_fr []  = "Decembre";


PROGMEM calendar_month calendar_months [] = { 
	{monthStr0_en, monthStr0_fr, "err"},
	{monthStr1_en, monthStr1_fr, "Jan"},
	{monthStr2_en, monthStr2_fr, "Fev"},
	{monthStr3_en, monthStr3_fr, "Mar"},
	{monthStr4_en, monthStr4_fr, "Avr"},
	{monthStr5_en, monthStr5_fr, "Mai"},
	{monthStr6_en, monthStr6_fr, "Jun"},
	{monthStr7_en, monthStr7_fr, "Jui"},
	{monthStr8_en, monthStr8_fr, "Aou"},
	{monthStr9_en, monthStr9_fr, "Sep"},
	{monthStr10_en, monthStr10_fr, "Oct"},
	{monthStr11_en, monthStr11_fr, "Nov"},
	{monthStr12_en, monthStr12_fr, "Dec"},
};
uint8_t calendar_monthCount = ARRAY_SIZE(calendar_months);

int calendar_date_get_mon(String country, String mon) {
	int ret = -1;
	String iMon;
	for (int i = 0; i < calendar_monthCount; ++i) {
		if (country == "fr") iMon = ce_char_to_string(calendar_months[i].mon_fr);
		if (country == "en") iMon = ce_char_to_string(calendar_months[i].mon_en);

		if ( iMon == mon) {
			ret = i;
			break;
		}
		
	}
	return ret;
}
String calendar_date_get_monStr(String country, String mon) {
	String ret = "";
	String iMon;
	for (int i = 0; i < calendar_monthCount; ++i) {
		if (country == "fr") iMon = ce_char_to_string(calendar_months[i].mon_fr);
		if (country == "en") iMon = ce_char_to_string(calendar_months[i].mon_en);

		if ( iMon == mon) {
			if (country == "en") ret = ce_char_to_string(calendar_months[i].mon_fr);
			if (country == "fr") ret = ce_char_to_string(calendar_months[i].mon_en);
			break;
		}
		
	}
	return ret;
}
int calendar_date_get_mon(String country, char* mon) {
	int ret = -1;
	char* iMon;
	for (int i = 0; i < calendar_monthCount; ++i) {
		if (country == "fr") iMon = calendar_months[i].mon_fr;
		if (country == "en") iMon = calendar_months[i].mon_en;

		if ( iMon == mon) {
			ret = i;
			break;
		}
		
	}
	return ret;
}

