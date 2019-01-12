#pragma once
#include <Windows.h>

// Helps with console api/WinApi
struct Console {
	// Handlers
	HANDLE hIn;
	HANDLE hOut;

	// Console flags
	DWORD dwConsoleMode;

	// Input in console
	INPUT_RECORD input;

	// Coords of cursor
	COORD crdCursor;

	Console();

	COORD WaitForClick();

};