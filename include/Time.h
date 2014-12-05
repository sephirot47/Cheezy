#ifndef TIME_H
#define TIME_H

#include <SDL2/SDL.h>

//Vector, Joan xD... No se si tot eso esta be, xD... nomes m aborria i he pillat la wiki de la sdl i he buscat algo que semblés faciolte xD
//Suposo que s'haurà de borrar todo de totes formes xD, així que nop feu massa cas de les tonteries que he escrit.

//ESTA PERFECTE!!!!!!!!!!!!! (victor)

/*TODO:

    Sleep functions.
    Functions to get time of today(day month year hour blah blah) formatted into a string
*/

using namespace std;
class Time
{
public:

    ///\brief Returns the time in seconds since the engine started
    static float getSeconds(); //Retorna Segons des de que s'inicia SDL

    ///\brief Returns the time in milisecs since the engine started
	static long getMiliseconds(); //Retorna Milisegons des de que s'inicia SDL
};
#endif // TIME_H
