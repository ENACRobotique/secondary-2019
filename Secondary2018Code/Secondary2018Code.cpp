// Do not remove the include below
#include "Secondary2018Code.h"
#include "Metro.h"
#include "params.h"
#include "odometry.h"

Metro controlTime = Metro((unsigned long)(CONTROL_PERIOD * 1000));


//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	Odometry::init();
}

// The loop function is called in an endless loop
void loop()
{
	if(controlTime.check()) {
		Odometry::update();
	}
}
