#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

#include "Game.h"


// Constructor
Game::Game() {
	InitBoard();

	game = GameStatus::inProgress;

	FlagCounter = board.Bombs;
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

void Game::DrawFrame() {
	constexpr char LEFT_UP_FRAME  = (char)201;
	constexpr char LEFT_DOWN_FRAME = (char)200;
	constexpr char RIGHT_DOWN_FRAME = (char)188;
	constexpr char RIGHT_UP_FRAME = (char)187;

	constexpr char LEFT_RIGHT_FRAME = (char)205;
	constexpr char UP_DOWN_FRAME = (char)186;

	// Set start position
	cmd.SetCursorPosition(COORD{0, 0});
	std::cout << LEFT_UP_FRAME;
	// Width is increase by 1 because it's counted from 0
	std::cout << std::setw(board.size.width + 1) << std::setfill(LEFT_RIGHT_FRAME) << RIGHT_UP_FRAME << std::endl;
	for (unsigned i = 0; i < board.size.height; i++) {
		std::cout << UP_DOWN_FRAME << std::setw(board.size.width + 1) << std::setfill(' ') << UP_DOWN_FRAME << std::endl;
	}
	std::cout << LEFT_DOWN_FRAME;
	std::cout << std::setw(board.size.width + 1) << std::setfill(LEFT_RIGHT_FRAME) << RIGHT_DOWN_FRAME << std::endl;
}


// All game
void Game::Start() {
	// Drawning frame for board on screen
	DrawFrame();
	WriteInfo();

	Mouse* UserMouse = &cmd.UserMouse;

	// General loop 
	while (game == GameStatus::inProgress) {	
		cmd.WaitForClick();

		// User must indicate a board
		if (*UserMouse < board.size) {

			// Substract by 1 because around board exist frame 
			FieldType* ptrActualPositionUP = &board.UpperBoard[UserMouse->crdPosition.Y - 1][UserMouse->crdPosition.X - 1];
			int* ptrActualPositionBB = &board.BackgroundBoard[UserMouse->crdPosition.Y - 1][UserMouse->crdPosition.X - 1];

			// Set/Remove flag
			if (UserMouse->dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
				
				// Put flag only when field is empty
				if (*ptrActualPositionUP == FieldType::EMPTY && FlagCounter > 0) {
					*ptrActualPositionUP = FieldType::FLAG;
					std::cout << (char)*ptrActualPositionUP;
					FlagCounter--;
					UpdateFlags();
				}
				// Remove flag only when in this field is a flag
				else if (*ptrActualPositionUP == FieldType::FLAG) {
					*ptrActualPositionUP = FieldType::EMPTY;
					std::cout << (char)*ptrActualPositionUP;
					FlagCounter++;
					UpdateFlags();
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

void Game::WriteInfo() {
	cmd.SetCursorPosition(COORD{ static_cast<short>(board.size.width + 5), 2 });
	std::cout << "Flags: " << FlagCounter << std::endl;
	// TODO: TIMER
}

void Game::UpdateFlags() {
	// 5 + "Flags: ".length
	cmd.SetCursorPosition(COORD{ static_cast<short>(board.size.width + 12), 2 });
	std::cout << FlagCounter << ' ' << std::endl;
}