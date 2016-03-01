/*
 * LigthControllerSpy.cpp
 *
 *  Created on: 13 de feb. de 2016
 *      Author: maxi
 */

#include "../ILightController/ILightController.h"


class LightControllerSpy: public ILightController
{
public:
	enum {LIGHT_ID_UNKNOWN = -1, LIGHT_STATE_UNKNOWN = -1,
			LIGHT_OFF = 0, LIGHT_ON = 1};
	LightControllerSpy()
	{
		lastID = LIGHT_ID_UNKNOWN;
		lastState = LIGHT_STATE_UNKNOWN;
	}
	void On(int id)
	{
		lastID = id;
		lastState = LIGHT_ON;
	}
	void Off(int id)
	{
		lastID = id;
		lastState = LIGHT_OFF;
	}
	int GetLastID()
	{
		return lastID;
	}
	int GetLastState()
	{
		return lastState;
	}
protected:
private:
	 int lastID;
	 int lastState;
};


