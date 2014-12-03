#include "Time.h"
#include "Debug.h"

long Time::getMiliseconds() {
	return SDL_GetTicks();
}

float Time::getMicroseconds() {
	return SDL_GetTicks()/1000;
}

float Time::getSeconds() {
	return SDL_GetTicks()/1000000;
}
