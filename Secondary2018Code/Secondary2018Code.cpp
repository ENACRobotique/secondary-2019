// Do not remove the include below
#include "Secondary2018Code.h"
#include "Metro.h"
#include "params.h"
#include "odometry.h"
#include "motorControl.h"
#include "trajectory.h"
#include "behaviour.h"

Metro controlTime = Metro((unsigned long)(CONTROL_PERIOD * 1000));
Metro test = Metro(100);

int i=0;

float x = 1000;
float y = 0;

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	Odometry::init();
	MotorControl::init();

	delay(4000);
	controlTime.reset();
	test.reset();
}

// The loop function is called in an endless loop
void loop()
{

	if(controlTime.check()) {
		Odometry::update();
		MotorControl::update();
	}
	if(test.check()) {
		if(i==0){
			i=turn(x,y);
		}
		else{
			forward(x,y);
		}
		//MotorControl::set_cons(50, 0);
	}
}
