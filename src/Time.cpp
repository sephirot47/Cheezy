#include "Time.h"
#include "Debug.h"

long Time::getMiliseconds() {
	return SDL_GetTicks();
}

float Time::getSeconds() {
	return SDL_GetTicks()/1000;
}
