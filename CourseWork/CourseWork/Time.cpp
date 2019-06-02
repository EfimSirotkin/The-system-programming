#include "Time.h"

void Time::getLocalTime()
{
		time_t t;
		time(&t);
		localTime = localtime(&t);
}