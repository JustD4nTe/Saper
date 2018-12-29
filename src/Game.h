#pragma once
#include "Board.h"


struct Game {
	unsigned X = 10;
	unsigned Y = 8;
	unsigned Bombs = 10;


	Board board;


	void InitBoard();
	void ShowBoards();
};