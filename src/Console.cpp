#include "Console.h"


// Constructor
Console::Console() {
	// Get console handlers
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get information about console(flags)
	GetConsoleMode(hIn, &dwConsoleMode);

	// Little annoying stuff => disable QuickEdit
	// it's blocks mouse event in Win10
	dwConsoleMode |= ENABLE_MOUSE_INPUT;
	dwConsoleMode &= ~ENABLE_QUICK_EDIT_MODE;
	// Save changes 
	SetConsoleMode(hIn, dwConsoleMode | ENABLE_EXTENDED_FLAGS);
}