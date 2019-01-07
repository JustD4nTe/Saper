#pragma once

// Possible types of one field
enum FieldType {
	EMPTY = ' ',
	BOMB = '*',
	NUMBER = '0'
};


// Yup, board structure
// idk what to say more
struct Board {
	// For display
	FieldType** UpperBoard;
	// For bombs and bomb counters
	int** BackgroundBoard;
};