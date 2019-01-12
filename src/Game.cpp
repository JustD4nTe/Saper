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
	srand((unsigned)time(NULL));

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

// TODO: discover better algo
// Searching bombs then increment value in nearby fields
// (8 directions)
void Game::CountNearbyBombs() {
	for (int y = 0; y < (int)board.size.height; y++) {
		for (int x = 0; x < (int)board.size.width; x++) {
			if (board.BackgroundBoard[y][x] == -1) {
				if ((x - 1) >= 0) {
					if(board.BackgroundBoard[y][x - 1] != -1)
						board.BackgroundBoard[y][x - 1]++;

					if ((y - 1) >= 0) {
						if(board.BackgroundBoard[y - 1][x - 1] != -1)
							board.BackgroundBoard[y - 1][x - 1]++;
					}
					if ((y + 1) < (int)board.size.height) {
						if(board.BackgroundBoard[y + 1][x - 1] != -1)
							board.BackgroundBoard[y + 1][x - 1]++;
					}
				}

				if ((y - 1) >= 0) {
					if (board.BackgroundBoard[y - 1][x] != -1)
						board.BackgroundBoard[y - 1][x]++;
				}
				if ((y + 1) < (int)board.size.height) {
					if (board.BackgroundBoard[y + 1][x] != -1)
						board.BackgroundBoard[y + 1][x]++;
				}

				if ((x + 1) < (int)board.size.width) {
					if (board.BackgroundBoard[y][x + 1] != -1)
						board.BackgroundBoard[y][x + 1]++;

					if ((y - 1) >= 0) {
						if (board.BackgroundBoard[y - 1][x + 1] != -1)
							board.BackgroundBoard[y - 1][x + 1]++;
					}
					if ((y + 1) < (int)board.size.height) {
						if (board.BackgroundBoard[y + 1][x + 1] != -1)
							board.BackgroundBoard[y + 1][x + 1]++;
					}
				}
			}
		}
	}
}

// Initialization for board
void Game::InitBoard() {
	SetBombs();
	CountNearbyBombs();
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