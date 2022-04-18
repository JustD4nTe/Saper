#ifndef BOARD_H
#define BOARD_H

#include <Windows.h>

#include "Console.h"

// Possible types of one field
enum FieldType {
	EMPTY = ' ',
	BOMB = '#',
	NUMBER = 'N',
	FLAG = 'F',
	NOTHING = '0'
};

// Just size of board counted from 0 (not 1)
struct BoardSize{
	unsigned width;
	unsigned height;

	void SetSize(unsigned x, unsigned y) {
		width = x;
		height = y;
	}

	friend bool operator<(Mouse a, BoardSize b);
};

// Yup, board structure
// idk what to say more
struct Board {
	// Store size of a boards
	BoardSize size;

	// Number of bombs
	unsigned Bombs = 10;

	// Some important variables
	unsigned int NumberOfAllFieldsWithoutBombs;
	unsigned int NumberOfTakenFields;

	// For display
	FieldType** UpperBoard;
	// For bombs and bomb counters
	int** BackgroundBoard;

	// Constructor
	Board();
};

#endif
