#pragma once
#include <Windows.h>

// Helps with console api/WinApi
struct Console {
	HANDLE hIn;
	HANDLE hOut;

	DWORD dwConsoleMode;

	INPUT_RECORD input;

	COORD crdCursor;

	Console();
};