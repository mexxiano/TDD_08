/*
 * LightScheduler.h
 *
 *  Created on: 18 de feb. de 2016
 *      Author: maxi
 */

#ifndef SRC_LIGHTSCHEDULER_LIGHTSCHEDULER_H_
#define SRC_LIGHTSCHEDULER_LIGHTSCHEDULER_H_

#ifndef Time
#include "../Time/Time.h"
#endif

#ifndef ITimeService
#include "../ITimeService/ITimeService.h"
#endif

#ifndef ILightController
#include "../ILightController/ILightController.h"
#endif

class LightScheduler
{
public:
	enum TurnState{TurnOff=0,TurnOn = 1};
	typedef enum TurnState EventState;

	//enum Day {NONE=-1, EVERYDAY=10, WEEKDAY, WEEKEND,
	//SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};
	//typedef enum Day Day;
	typedef Time::DayOfWeek Day;

	LightScheduler(ITimeService* timeService, ILightController* lightController);
	~LightScheduler();
	void ScheduleTurnOn(int id, Day day,int minuteOfDay);
	void ScheduleTurnOff(int id, Day day,int minuteOfDay);
	void RemoveSchedule();
	void WakeUp();
protected:
	ITimeService * itsTimeService;
	ILightController * itsLightController;
	void scheduleEvent(int id, int minuteOfDay , Day day, EventState event);
private:

};
#endif /* SRC_LIGHTSCHEDULER_LIGHTSCHEDULER_H_ */
