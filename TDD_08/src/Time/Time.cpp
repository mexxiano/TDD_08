/*
 * Time.cpp
 *
 *  Created on: 18 de feb. de 2016
 *      Author: maxi
 */

#include "Time.h"

Time::Time()
{
	this->itsDayOfWeek = Time::UNKNOWN;
	this->itsMinuteOfDay = Time::UNKNOWN;
}


Time::~Time()
{
}

void Time::SetMinuteOfDay(int setMinute)
{
	this->itsMinuteOfDay = setMinute;
}


void Time::SetDayOfWeek(DayOfWeek setDayOfWeek)
{
	this->itsDayOfWeek = setDayOfWeek;
}


int Time::GetMinuteOfDay()
{
	return this->itsMinuteOfDay;
}


Time::DayOfWeek Time::GetDayOfWeek()
{
	return this->itsDayOfWeek;
}
