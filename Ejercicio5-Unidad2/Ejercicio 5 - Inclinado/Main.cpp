#include "Juego.h" 
#include <tchar.h> 

using namespace sf;

int _tmain(int argc, _TCHAR* argv[])
{
    Game* Juego;
    Juego = new Game(800, 800, "MAVII Ejercicio 5");
    Juego->Loop();

    return 0;
}
