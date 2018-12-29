#include <windows.h>

#include "Game.h"
using namespace std;

int main()
{
	Game game;
	game.InitBoard();
	game.ShowBoards();


	system("pause");
	return 0;
}