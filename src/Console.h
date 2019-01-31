#pragma once
#include <Windows.h>

struct BoardSize;

struct Mouse {
	COORD crdPosition;
	DWORD dwButtonState;

	friend bool operator<(Mouse a, BoardSize b);
};

// Helps with console api/WinApi
struct Console {
	// Handlers
	HANDLE hIn;
	HANDLE hOut;
	CONSOLE_CURSOR_INFO hConsoleCursorInfo;

	// Console flags
	DWORD dwConsoleMode;

	// Input in console
	INPUT_RECORD input;

	// Coords of cursor
	Mouse UserMouse;
	   

	// Constructor
	Console();

	// Methods
	void WaitForClick();
	void ChangeCursorVisibility(bool disable = true);
	void SetCursorPosition(const COORD crdPosition);
};