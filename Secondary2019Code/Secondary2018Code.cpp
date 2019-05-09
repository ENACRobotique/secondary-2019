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

//The setup function is called once at startup of the sketch

float speed = 200;
float omega = PI / 2;
int led = 13;
int deb;
unsigned int temps[4] = {5000,500/speed*1000, 2000, 500/speed * 1000};

void setup()
{
	pinMode(led, OUTPUT);
	/*digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(1000);               // wait for a second
	digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
	delay(1000);*/
	Serial.begin(115200);
	//while(!Serial){}
	Serial.println("INIT Serial");
	Odometry::init();
	Serial.println("INIT odom");
	MotorControl::init();
	Serial.println("INIT motor");
	//fsmSupervisor.init(&tiretteState);
	controlTime.reset();
	navigatorTime.reset();
	deb = millis();
	Odometry::set_pos(0, 0, 0);
	//navigator.move_to(1000,0);
}

int i = 0;

// The loop function is called in an endless loop
void loop()
{


	//MotorControl::set_cons(speed, 0);
	//navigator.move_to(1000,0);


	if((millis() - deb) > temps[i]){
		if(i == 0){
			MotorControl::set_cons(speed, 0);
			deb = millis();
			i++;
		}
		else if(i == 1){
			MotorControl::set_cons(0, omega);
			deb = millis();
			i++;
		}
		else if(i == 2){
			MotorControl::set_cons(speed, 0);
			deb = millis();
			i++;
		}
		else if(i == 3){
			MotorControl::set_cons(0, 0);
			deb = millis();
		}
	}

	/*analogWrite(MOT1_PWM, 200);
	digitalWrite(MOT1_DIR, 0);
	analogWrite(MOT2_PWM, 200);
	digitalWrite(MOT2_DIR, 1);*/

	//fsmSupervisor.update();

	if(controlTime.check()) {
		Odometry::update();
		MotorControl::update();
	}

	if(navigatorTime.check()) {
		//navigator.update();

	}


}
