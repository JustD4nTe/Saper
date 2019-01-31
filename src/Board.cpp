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

	NumberOfAllFieldsWithoutBombs = ((size.width * size.height) - Bombs);
	NumberOfTakenFields = 0;
}

bool operator<(Mouse a, BoardSize b) {
	// Frame is around board, so we don't need click that
	if (a.crdPosition.X == 0 || a.crdPosition.Y == 0)
		return false;

	if ((a.crdPosition.X - 1 )< b.width && (a.crdPosition.Y - 1) < b.height)
		return true;

	else
		return false;
}