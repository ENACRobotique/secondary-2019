// Do not remove the include below
#include "Secondary2018Code.h"


//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(13, OUTPUT);
}

// The loop function is called in an endless loop
void loop()
{
	digitalWrite(13, HIGH);
	delay(200);
	digitalWrite(13, LOW);
	delay(200);
}
