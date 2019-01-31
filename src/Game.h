#pragma once
#include "Board.h"

enum GameStatus {
	inProgress,
	Win,
	Lose
};

// "Core" of this game
struct Game {
	Board board;
	Console cmd;

	GameStatus game;

	// Methods
	Game();

	void SetBombs();
	void CountNearbyBombs();

	void InitBoard();

	void DrawFrame();


	void Start();
	void EndScreen();
};