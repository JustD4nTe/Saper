#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <cmath>

#include "Game.h"


// Initialization for board
void Game::InitBoard() {
	// Create rows 
	board.UpperBoard = new FieldType*[Y];

	for (unsigned i = 0; i < Y; i++) {
		board.UpperBoard[i] = new FieldType[X];
		// Fill all fields in row 
		for (unsigned j = 0; j < X; j++) board.UpperBoard[i][j] = FieldType::BOMB;
	}

	// Initialize board with zero
	board.BackgroundBoard = new int*[Y];
	for (unsigned i = 0; i < Y; i++)
		board.BackgroundBoard[i] = new int[X] {0};

	srand(time(NULL));
	// Count of bombs which were planted
	unsigned BombsCount = 0;

	do {
		unsigned x = rand() % X;
		unsigned y = rand() % Y;

		// When there is not any  bomb
		if (board.BackgroundBoard[y][x] == 0) {
			// Plant it
			board.BackgroundBoard[y][x] = -1;
			BombsCount++;
		}
	} while (BombsCount < Bombs);
}

// Display boards on  screen
void Game::ShowBoards() {
	for (unsigned i = 0; i < Y; i++) {
		for (unsigned j = 0; j < X; j++)
			std::cout << abs(board.BackgroundBoard[i][j]);

		std::cout << std::endl;
	}


	// Prototype of general board
	for (unsigned i = 0; i < Y; i++) {
		std::cout << "|";
		for (unsigned j = 0; j < X; j++)
			std::cout << (char)board.UpperBoard[i][j];

		std::cout << "|" << std::endl;
	}
}