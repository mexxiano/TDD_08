#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "ILightController/ILightController.h"
#include "LightControllerSpy/LightControllerSpy.cpp"
#include "TimeServiceFake/TimeServiceFake.cpp"
#include "Time/time.h"
#include "LightScheduler/LightScheduler.h"

void thisIsATest() {
	ASSERTM("start writing tests", false);	
}

void createLightController()
{
	LightControllerSpy myLCSpy;

	ASSERT_EQUAL(myLCSpy.LIGHT_ID_UNKNOWN , myLCSpy.GetLastID());
	ASSERT_EQUAL(myLCSpy.LIGHT_STATE_UNKNOWN, myLCSpy.GetLastState());

}

void RememberTheLastLightIdControlled()
{
	LightControllerSpy myLCSpy;
	myLCSpy.On(10);
	ASSERT_EQUAL(10, myLCSpy.GetLastID());
	ASSERT_EQUAL(LightControllerSpy::LIGHT_ON, myLCSpy.GetLastState());
}


void createFakeTimeController()
{
	Time time;
	TimerServiceFake timeService;

	timeService.GetTime(&time);

	ASSERT_EQUAL(Time::UNKNOWN, time.GetMinuteOfDay());
	ASSERT_EQUAL(Time::UNKNOWN, time.GetDayOfWeek());
}


void setFakeTimeController()
{
	Time time;
	TimerServiceFake timeService;

	timeService.SetMinute(142);
	timeService.SetDayOfWeek(Time::SUNDAY);

	timeService.GetTime(&time);

	ASSERT_EQUAL(142,time.GetMinuteOfDay());
	ASSERT_EQUAL(Time::SUNDAY, time.GetDayOfWeek());

}


void noScheduleNothingHappens()
{
	TimerServiceFake timeService;
	LightControllerSpy lightController;
	LightScheduler lightScheduler(&timeService, &lightController);

	timeService.SetMinute(100);
	timeService.SetDayOfWeek(Time::MONDAY);

}


void ScheduleOnEverydayItsTime()
{
	TimerServiceFake timeService;
	LightControllerSpy lightController;
	LightScheduler lightScheduler(&timeService, &lightController);

	lightScheduler.ScheduleTurnOn(3, Time::EVERYDAY,1200);

	timeService.SetDayOfWeek(Time::MONDAY);
	timeService.SetMinute(1200);

	lightScheduler.WakeUp();

	ASSERT_EQUAL(3,lightController.GetLastID());
	ASSERT_EQUAL(LightControllerSpy::LIGHT_ON,lightController.GetLastState());
}


void ScheduleOffEverydayItsTime()
{
	TimerServiceFake timeService;
	LightControllerSpy lightController;
	LightScheduler lightScheduler(&timeService, &lightController);

	lightScheduler.ScheduleTurnOff(3, Time::EVERYDAY,1200);

	timeService.SetDayOfWeek(Time::MONDAY);
	timeService.SetMinute(1200);

	lightScheduler.WakeUp();

	ASSERT_EQUAL(3,lightController.GetLastID());
	ASSERT_EQUAL(LightControllerSpy::LIGHT_OFF,lightController.GetLastState());
}


void ScheduleTuesdayButItsMonday()
{
	TimerServiceFake timeService;
	LightControllerSpy lightController;
	LightScheduler lightScheduler(&timeService, &lightController);

	lightScheduler.ScheduleTurnOn(3, Time::TUESDAY,1200);

	timeService.SetDayOfWeek(Time::MONDAY);
	timeService.SetMinute(1200);

	lightScheduler.WakeUp();

	ASSERT_NOT_EQUAL_TO(3,lightController.GetLastID());
	ASSERT_NOT_EQUAL_TO((int)LightControllerSpy::LIGHT_ON,(int) lightController.GetLastState());
}


void ScheduleTuesdayAndItsTuesday()
{
	TimerServiceFake timeService;
	LightControllerSpy lightController;
	LightScheduler lightScheduler(&timeService, &lightController);

	lightScheduler.ScheduleTurnOn(3, Time::TUESDAY,1200);

	timeService.SetDayOfWeek(Time::TUESDAY);
	timeService.SetMinute(1200);

	lightScheduler.WakeUp();

	ASSERT_EQUAL(3,lightController.GetLastID());
	ASSERT_EQUAL(LightControllerSpy::LIGHT_ON,lightController.GetLastState());
}


void ScheduleWeekEndItsFriday()
{
	TimerServiceFake timeService;
	LightControllerSpy lightController;
	LightScheduler lightScheduler(&timeService, &lightController);

	lightScheduler.ScheduleTurnOn(3, Time::WEEKEND,1200);

	timeService.SetDayOfWeek(Time::FRIDAY);
	timeService.SetMinute(1200);

	lightScheduler.WakeUp();

	ASSERT_NOT_EQUAL_TO(3,(int)lightController.GetLastID());
	ASSERT_NOT_EQUAL_TO((int)LightControllerSpy::LIGHT_ON,(int)lightController.GetLastState());
}


void ScheduleWeekEndItsSaturday()
{
	TimerServiceFake timeService;
	LightControllerSpy lightController;
	LightScheduler lightScheduler(&timeService, &lightController);

	lightScheduler.ScheduleTurnOn(3, Time::WEEKEND,1200);

	timeService.SetDayOfWeek(Time::SATURDAY);
	timeService.SetMinute(1200);

	lightScheduler.WakeUp();

	ASSERT_EQUAL(3, (int)lightController.GetLastID());
	ASSERT_EQUAL((int)LightControllerSpy::LIGHT_ON,(int)lightController.GetLastState());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	s.push_back(CUTE(createLightController));
	s.push_back(CUTE(RememberTheLastLightIdControlled));
	s.push_back(CUTE(createFakeTimeController));
	s.push_back(CUTE(setFakeTimeController));
	s.push_back(CUTE(ScheduleOnEverydayItsTime));
	s.push_back(CUTE(ScheduleOffEverydayItsTime));
	s.push_back(CUTE(ScheduleTuesdayButItsMonday));
	s.push_back(CUTE(ScheduleTuesdayAndItsTuesday));
	s.push_back(CUTE(ScheduleWeekEndItsFriday));
	s.push_back(CUTE(ScheduleWeekEndItsSaturday));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



