#include "Juego.h"
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[])
{
    Game* Juego;
    Juego = new Game(800, 800, "MAVII Proyecto 2");
    Juego->Loop();

    return 0;
}
