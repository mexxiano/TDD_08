/*
 * LightScheduler.cpp
 *
 *  Created on: 18 de feb. de 2016
 *      Author: maxi
 */
#include "LightScheduler.h"

typedef struct
	{
		int id;
		int minuteOfDay;
		LightScheduler::Day day;
		LightScheduler::EventState event;
	} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

void processEventDueNow(Time * time, ScheduledLightEvent * lightEvent, ILightController * lightController);
static void operateLights( ScheduledLightEvent * lightEvent, ILightController * lightController);
static bool doesLightRespondToday(Time * time, int reactionDay);

LightScheduler::LightScheduler(ITimeService* timeService , ILightController* lightController)
{

	this->itsTimeService = timeService;
	this->itsLightController = lightController;
	scheduledEvent.id = - 1;
}


LightScheduler::~LightScheduler()
{
}


void LightScheduler::RemoveSchedule()
{
}


void LightScheduler::WakeUp()
{
	Time time;
	this->itsTimeService->GetTime(&time);
	processEventDueNow(&time, &scheduledEvent, this->itsLightController);
}


 void LightScheduler::scheduleEvent(int id, int minuteOfDay,  Day day, EventState event)
 {
	scheduledEvent.id = id;
	scheduledEvent.minuteOfDay = minuteOfDay;
	scheduledEvent.day = day;
	scheduledEvent.event = event ;
}


void LightScheduler::ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
	this->scheduleEvent(id, minuteOfDay , day, LightScheduler::TurnOn);
}


void LightScheduler::ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
	this->scheduleEvent(id, minuteOfDay , day, LightScheduler::TurnOff);
}


void processEventDueNow(Time * time, ScheduledLightEvent * lightEvent, ILightController * lightController)
{

	int today = time->GetDayOfWeek();

	if(lightEvent->id == -1) //UNUSED^
	{
		return;
	}

	if(!doesLightRespondToday(time,lightEvent->day))
	{
		return;
	}

	if(time->GetMinuteOfDay() != lightEvent->minuteOfDay)
	{
		return;
	}

	operateLights(lightEvent , lightController);
}


void operateLights( ScheduledLightEvent * lightEvent, ILightController * lightController)
{
	if(lightEvent->event == LightScheduler::TurnOn)
	{
		lightController->On(lightEvent->id);
	}
	else if(lightEvent->event == LightScheduler::TurnOff)
	{
		lightController->Off(lightEvent->id);
	}
}


static bool doesLightRespondToday(Time * time, int reactionDay)
{
	int today = time->GetDayOfWeek();

	if(reactionDay == Time::EVERYDAY)
	{
		return true;
	}

	if(reactionDay == today)
	{
		return true;
	}

	if(reactionDay == Time::WEEKEND && (today == Time::SATURDAY || today == Time::SUNDAY))
	{
		return true;
	}

	if(reactionDay == Time::WEEKDAY && (today >= Time::MONDAY && today <= Time::FRIDAY))
	{
		return true;
	}

	return false;

	}
