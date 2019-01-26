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

	// Disable cursor, we don't need it
	// look better without it
	ChangeCursorVisibility();
}

// Enable/Disable cursor visibility in CMD
void Console::ChangeCursorVisibility(bool disable)
{
	GetConsoleCursorInfo(hOut, &hConsoleCursorInfo);

	hConsoleCursorInfo.bVisible = hConsoleCursorInfo.bVisible & !disable;
	SetConsoleCursorInfo(hOut, &hConsoleCursorInfo);
}

COORD Console::WaitForClick() {

	DWORD NumRead;

	while (true){
		ReadConsoleInput(hIn,& input, 1, &NumRead);

		switch (input.EventType){
		case MOUSE_EVENT:
			crdCursor = input.Event.MouseEvent.dwMousePosition;
			if (input.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				SetConsoleTextAttribute(hOut, BACKGROUND_GREEN);
				SetConsoleCursorPosition(hOut, crdCursor);
				return crdCursor;
			}
			if (input.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
				SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
				SetConsoleCursorPosition(hOut, crdCursor);
				return crdCursor;
			}
		}
	}
	return COORD();
}