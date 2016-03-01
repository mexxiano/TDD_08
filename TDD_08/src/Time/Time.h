/*
 * Time.h
 *
 *  Created on: 18 de feb. de 2016
 *      Author: maxi
 */

#ifndef SRC_TIME_TIME_H_
#define SRC_TIME_TIME_H_

class Time
{
public:
	enum DayOfWeek{UNKNOWN = -1, NONE=-1, EVERYDAY=10, WEEKDAY, WEEKEND, SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};
	Time();
	~Time();
	void SetMinuteOfDay(int setMinute);
	void SetDayOfWeek(DayOfWeek setDayOfWeek);
	int GetMinuteOfDay();
	DayOfWeek GetDayOfWeek();
private:
	DayOfWeek itsDayOfWeek;
	int itsMinuteOfDay;
};

#endif /* SRC_TIME_TIME_H_ */
