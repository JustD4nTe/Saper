#include <windows.h>

#include "Game.h"

int main()
{
	Game game;

	game.Start();

	game.EndScreen();

	system("pause");
	return 0;
}