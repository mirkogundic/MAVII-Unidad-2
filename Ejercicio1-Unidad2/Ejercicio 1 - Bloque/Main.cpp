#include "Juego.h"
#include <tchar.h>

using namespace sf;
int _tmain(int argc, _TCHAR* argv[])
{
    Game* Juego;
    Juego = new Game(800, 600, "MAVII Proyecto 1");
    Juego->Loop();

    return 0;
}