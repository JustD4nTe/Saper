#ifndef GAME_H
#define GAME_H

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

	// How many flags we can put 
	unsigned FlagCounter;

	// Methods
	Game();

	void SetBombs();
	void CountNearbyBombs();

	void InitBoard();

	void DrawFrame();
	void WriteInfo();

	void UpdateFlags();

	void RevealEmptyFields(int x, int y);

	void Check();

	void Start();
	void EndScreen();
};

#endif
