#pragma once

// Possible types of one field
enum FieldType {
	EMPTY = ' ',
	BOMB = '*',
	NUMBER = '0'
};

// Uhm, just size of board counted from 0 (not 1)
struct BoardSize{
	unsigned width;
	unsigned height;

	void SetSize(unsigned x, unsigned y) {
		width = x;
		height = y;
	}
};

// Yup, board structure
// idk what to say more
struct Board {
	// Store size of a boards
	BoardSize size;
	// Number of bombs
	unsigned Bombs = 10;

	// For display
	FieldType** UpperBoard;
	// For bombs and bomb counters
	int** BackgroundBoard;

	// Constructor
	Board();
};