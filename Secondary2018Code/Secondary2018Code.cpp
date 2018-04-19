// Do not remove the include below
#include "Secondary2018Code.h"
#include "Metro.h"
#include "params.h"
#include "odometry.h"
#include "motorControl.h"
#include "Navigator.h"
#include "StateMachine/FSMSupervisor.h"
#include "StateMachine/TiretteState.h"
Metro controlTime = Metro((unsigned long)(CONTROL_PERIOD * 1000));
Metro navigatorTime = Metro(NAVIGATOR_TIME_PERIOD * 1000);

int i=0;

float x, y;

bool done=false;

float target[][2] = {
		{400, -400},
		{400, 0},
		{0,-400},
		{0,0}};

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	Odometry::init();
	MotorControl::init();
	delay(4000);
	controlTime.reset();
	navigatorTime.reset();
	fsmSupervisor.init(&tiretteState);

}

// The loop function is called in an endless loop
void loop()
{
	fsmSupervisor.update();
	if(controlTime.check()) {
		Odometry::update();
		MotorControl::update();
	}
	if(navigatorTime.check()) {
		navigator.update();
		/*if(navigator.isTrajectoryFinished()){
			Serial.print("Trajectoire finie :");
			Serial.println(i);
			i = (1+i)%4;
			navigator.move_to(target[i][0],target[i][1]);
		}*/
	}
}
