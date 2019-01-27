#pragma once
#include "Board.h"

// "Core" of this game
struct Game {
	Board board;
	Console cmd;


	// Methods
	Game();

	void SetBombs();
	void CountNearbyBombs();

	void InitBoard();

	void ShowBoard();


	void Start();
};