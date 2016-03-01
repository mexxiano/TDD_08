/*
 * TimeServiceFace.cpp
 *
 *  Created on: 18 de feb. de 2016
 *      Author: maxi
 */

#include "../ITimeService/ITimeService.h"

class TimerServiceFake : public ITimeService
{
public:


	TimerServiceFake()
	{

	}


	void GetTime(Time* time)
	{
		*time = this->itsTime;
	}


	void SetMinute(int setMinute)
	{
		this->itsTime.SetMinuteOfDay(setMinute);
	}


	void SetDayOfWeek(Time::DayOfWeek setDayOfWeek)
	{
		this->itsTime.SetDayOfWeek(setDayOfWeek);
	}


private:
	Time itsTime;

};
