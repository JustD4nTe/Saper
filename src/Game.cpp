#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Game.h"

// Constructor
Game::Game() {
	InitBoard();

	ShowBoards();
}

// Randomize mines on map
void Game::SetBombs() {
	// Seed ;)
	srand(time(NULL));

	// Count of bombs which were planted
	unsigned BombsCount = 0;

	do {
		unsigned x = rand() % board.size.width;
		unsigned y = rand() % board.size.height;

		// When there is not any  bomb
		if (board.BackgroundBoard[y][x] == 0) {
			// Plant it
			board.BackgroundBoard[y][x] = -1;
			BombsCount++;
		}
	} while (BombsCount < board.Bombs); // until we get all bombs
}
}

// Initialization for board
void Game::InitBoard() {
	SetBombs();
}

// Display boards on  screen
void Game::ShowBoards() {
	for (unsigned y = 0; y < board.size.height; y++) {
		for (unsigned x = 0; x < board.size.width; x++) {
			if (board.BackgroundBoard[y][x] == -1)
				std::cout << "*";
			else
				std::cout << board.BackgroundBoard[y][x];
		}
		std::cout << std::endl;
	}


	// Prototype of general board
	for (unsigned y = 0; y < board.size.height; y++) {
		for (unsigned x = 0; x < board.size.width; x++)
			std::cout << (char)board.UpperBoard[y][x];

		std::cout << std::endl;
	}
}