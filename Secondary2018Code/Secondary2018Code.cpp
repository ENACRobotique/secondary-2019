// Do not remove the include below
#include "Secondary2018Code.h"
#include "Metro.h"
#include "params.h"
#include "odometry.h"
#include "motorControl.h"

Metro controlTime = Metro((unsigned long)(CONTROL_PERIOD * 1000));
Metro test = Metro(3000);
int i=0;
int tab_speed[] = {0, 100, 0, -100};
float tab_omega[] = {0, 0.5, 0, -0.5} ;
//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	Odometry::init();
	MotorControl::init();
}

// The loop function is called in an endless loop
void loop()
{
	if(controlTime.check()) {
		Odometry::update();
		MotorControl::update();
	}
	if(test.check()) {
		MotorControl::set_cons(tab_speed[i%4], tab_omega[i%4]);
		i++;

	}
	//MotorControl::set_cons(50, 0);
}
