#pragma once
#include "Board.h"
#include "Console.h"

// "Core" of this game
struct Game {
	// Board size
	unsigned X = 10;
	unsigned Y = 8;
	// Number of bombs
	unsigned Bombs = 10;


	Board board;
	Console cmd;


	// Methods
	Game();

	void InitBoard();
	void InitCmd();

	void ShowBoards();
};