/*
 * ITimeService.h
 *
 *  Created on: 18 de feb. de 2016
 *      Author: maxi
 */

#ifndef SRC_ITIMESERVICE_ITIMESERVICE_H_
#define SRC_ITIMESERVICE_ITIMESERVICE_H_

#include "../Time/Time.h"

class ITimeService
{
public:
	ITimeService(){}
	virtual ~ITimeService(){}
	virtual void GetTime(Time* time) = 0;
	virtual void SetMinute(int setMinute) = 0;
	virtual void SetDayOfWeek(Time::DayOfWeek setDayOfWeek) = 0;
};
#endif /* SRC_ITIMESERVICE_ITIMESERVICE_H_ */
