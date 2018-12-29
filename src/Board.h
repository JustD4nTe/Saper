#pragma once

enum FieldType {
	EMPTY = ' ',
	BOMB = '*',
	NUMBER = '0'
};

struct Board {
	FieldType** UpperBoard;
	int** BackgroundBoard;
};