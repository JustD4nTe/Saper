#include "Board.h"

Board::Board() {
	// default size
	size.SetSize(10, 7);

	// Create rows 
	UpperBoard = new FieldType*[size.height];

	for (unsigned y = 0; y < size.height; y++) {
		UpperBoard[y] = new FieldType[size.width];
		// Fill all fields in row 
		for (unsigned x = 0; x < size.width; x++)
			UpperBoard[y][x] = FieldType::EMPTY;
	}

	// Initialize board with zero
	BackgroundBoard = new int*[size.height];
	for (unsigned y = 0; y < size.height; y++)
		BackgroundBoard[y] = new int[size.width] {0};
}

bool operator<(Mouse a, BoardSize b) {
	if (a.crdPosition.X < b.width && a.crdPosition.Y < b.height)
		return true;
	else
		return false;
}