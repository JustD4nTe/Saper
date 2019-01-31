#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Game.h"

// Constructor
Game::Game() {
	InitBoard();

	game = GameStatus::inProgress;
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
void Game::ShowBoard() {
	// Prototype of general board
	for (unsigned y = 0; y < board.size.height; y++) {
		for (unsigned x = 0; x < board.size.width; x++)
			std::cout << (char)board.UpperBoard[y][x];

		std::cout << std::endl;
	}
}

char GetCharacter(Board* board, unsigned x, unsigned y) {
	return (board->UpperBoard[y][x] != FieldType::NUMBER ? (char)board->UpperBoard[y][x] : (char)(board->BackgroundBoard[y][x] + 48));
}

// All game
void Game::Start() {
	// Drawning board on screen
	ShowBoard();

	Mouse* UserMouse = &cmd.UserMouse;

	// General loop 
	while (game == GameStatus::inProgress) {
		std::cout << cmd.ChangeColor(&GetCharacter, &board);
		cmd.WaitForClick();

		// User must indicate a board
		if (*UserMouse < board.size) {

			FieldType* ptrActualPositionUP = &board.UpperBoard[UserMouse->crdPosition.Y][UserMouse->crdPosition.X];
			int* ptrActualPositionBB = &board.BackgroundBoard[UserMouse->crdPosition.Y][UserMouse->crdPosition.X];

			// Set/Remove flag
			if (UserMouse->dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
				
				// Put flag only when field is empty
				if (*ptrActualPositionUP == FieldType::EMPTY) {
					*ptrActualPositionUP = FieldType::FLAG;
					std::cout << (char)*ptrActualPositionUP;
				}
				// Remove flag only when in this field is a flag
				else if (*ptrActualPositionUP == FieldType::FLAG) {
					*ptrActualPositionUP = FieldType::EMPTY;
					std::cout << (char)*ptrActualPositionUP;
				}
			}

			// Uncover fields
			else if (UserMouse->dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				// Can't be there any flag
				if (*ptrActualPositionUP != FieldType::FLAG) {
					// Game Over
					if (*ptrActualPositionBB == -1) {
						*ptrActualPositionUP = FieldType::BOMB;
						std::cout << "#" << std::flush;
						game = GameStatus::Lose;
					}

					// Reveal number of nearby bombs
					else {
						*ptrActualPositionUP = FieldType::NUMBER;
						std::cout << *ptrActualPositionBB << std::flush;
					}
				}
			}
			
			else{
				std::cout << GetCharacter(&board, UserMouse->crdPosition.X, UserMouse->crdPosition.Y);
			}
		}
	}
}

// When game is end
// some text will be displayed
void Game::EndScreen() {
	COORD crdEndScreenPosition;
	crdEndScreenPosition.X = 0;
	crdEndScreenPosition.Y = board.size.height + 3;

	cmd.SetCursorPosition(crdEndScreenPosition);

	switch (game){
	case Win:
		std::cout << "You win!! Congratulations :D\n" << std::flush;
		break;
	case Lose:
		std::cout << "You lose, try again :<\n" << std::flush;
		break;
	}
}