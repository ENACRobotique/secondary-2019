/*
 // Do not remove the incl	supprimé :        Secondary2019Code/.cproject
	supprimé :        Secondary2019Code/.project
	supprimé :        Secondary2019Code/.settings/language.settings.xml
	supprimé :        Secondary2019Code/.settings/org.eclipse.cdt.codan.core.prefs
	supprimé :        Secondary2019Code/.settings/org.eclipse.cdt.core.prefs
	supprimé :        Secondary2019Code/spec.d
ude below	supprimé :        Secondary2019Code/.cproject
	supprimé :        Secondary2019Cod	supprimé :        Secondary2019Code/.cproject
	supprimé :        Secondary2019Code/.project
	supprimé :        Secondary2019Code/.settings/language.settings.xml
	supprimé :        Secondary2019Code/.settings/org.eclipse.cdt.codan.core.prefs
	supprimé :        Secondary2019Code/.settings/org.eclipse.cdt.core.prefs
	supprimé :        Secondary2019Code/spec.d
e/.project
	supprimé :        Secondary2019Code/.settings/language.settings.xml
	supprimé :        Secondary2019Code/.settings/org.eclipse.cdt.codan.core.prefs
	supprimé :        Secondary2019Code/.settings/org.eclipse.cdt.core.prefs
	supprimé :        Secondary2019Code/spec.d
*/
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
//unsigned int temps[4] = {5000,500/speed*1000, 2000, 500/speed * 1000};
int xdep = 50;
int ydep = 420;
Servo mandibuleGauche = Servo();
Servo mandibuleDroite = Servo();


void setup()
{
	pinMode(led, OUTPUT);
	/*digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(1000);               // wait for a second
	digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
	delay(1000);*/
	Serial.begin(115200);
	//while(!Serial){}
	//Serial.println("INIT Serial");
	Odometry::init();
	//Serial.println("INIT odom");
	MotorControl::init();
	//Serial.println("INIT motor");
	//fsmSupervisor.init(&tiretteState);
	controlTime.reset();
	navigatorTime.reset();
	deb = millis();
	Odometry::set_pos(xdep, ydep, 0);
	mandibuleGauche.attach(SERVO2);
	mandibuleGauche.write(MANDIBULE_GAUCHE_HAUT);
	mandibuleDroite.attach(SERVO1);
	mandibuleDroite.write(MANDIBULE_DROITE_HAUT);
}

int i = 0;

// The loop function is called in an endless loop
void loop()
{
	/*if(millis() - deb > 3000){
		mandibuleGauche.write(MANDIBULE_GAUCHE_HAUT);
		mandibuleDroite.write(MANDIBULE_DROITE_HAUT);
	}*/
	if(i == 0){
			navigator.move_to(540, 420);
			i++;
	}
	if(navigator.isTrajectoryFinished() && i == 1){
			navigator.turn_to(90);
			i++;
	}
	if(navigator.isTrajectoryFinished() && i == 2){
			navigator.move_to(540, 1040);
			i++;
	}
	if(navigator.isTrajectoryFinished() && i == 3){
			navigator.turn_to(0);
			i++;
			mandibuleDroite.write(MANDIBULE_DROITE_BAS);
			mandibuleGauche.write(MANDIBULE_GAUCHE_BAS);
	}
	if(navigator.isTrajectoryFinished() && i == 4){
			navigator.move_to(110, 1040);
			i++;
	}
	if(navigator.isTrajectoryFinished() && i == 5){
			navigator.turn_to(90);
			i++;
		}
	if(navigator.isTrajectoryFinished() && i == 6){
			navigator.move_to(110,440);
			i++;

	}
	if(navigator.isTrajectoryFinished() && i == 7){
					navigator.move_to(110, -20);
					mandibuleDroite.write(MANDIBULE_DROITE_HAUT);
					mandibuleGauche.write(MANDIBULE_GAUCHE_HAUT);
					i++;
	}
	/*if(navigator.isTrajectoryFinished() && i == 5){
			navigator.turn_to(270);
			i++;
	}
	if(navigator.isTrajectoryFinished() && i == 6){
			navigator.move_to(xdep, ydep);
			i++;
	}*/

	//MotorControl::set_cons(speed, 0);
	/*if(i == 0){
		navigator.move_to(490 + 50,420);
		i++;
	}
	if(navigator.isTrajectoryFinished() && i == 1){
		navigator.turn_to(90);
		//navigator.move_to(0,0);
		i++;
	}
	if(navigator.isTrajectoryFinished() && i == 2){
			//navigator.turn_to(180);
			navigator.move_to(490 + 50,620 + 420);
			i++;
	}*/
	/*if(navigator.isTrajectoryFinished() && i == 3){
			navigator.turn_to(180);
			//navigator.move_to(0,0);
			i++;
	}
	if(navigator.isTrajectoryFinished() && i == 4){
				//navigator.turn_to(180);
				navigator.move_to(50,620 + 420);
				i++;
	}
/*
	if((millis() - deb) > 2000){
				MotorControl::set_cons(speed, 0);
				deb = millis();
				speed = -speed;
	}
*/
	/*if((millis() - deb) > temps[i]){
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
	}*/

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
		navigator.update();

	}


}
