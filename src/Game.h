#pragma once
#include "Board.h"
#include "Console.h"

// "Core" of this game
struct Game {
	Board board;
	Console cmd;


	// Methods
	Game();

	void SetBombs();
	void InitBoard();

	void ShowBoards();
};