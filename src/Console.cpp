#include "Console.h"

#define NORMAL_COLOR 0x0f
#define HOVER_COLOR 0xf0

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
	// looks better without it
	ChangeCursorVisibility();

	UserMouse = Mouse();
}

// Enable/Disable cursor visibility in CMD
void Console::ChangeCursorVisibility(bool disable)
{
	GetConsoleCursorInfo(hOut, &hConsoleCursorInfo);

	hConsoleCursorInfo.bVisible = hConsoleCursorInfo.bVisible & !disable;
	SetConsoleCursorInfo(hOut, &hConsoleCursorInfo);

}

// Waiting for user move
void Console::WaitForClick() {
	DWORD NumRead{};

	while (true){
		ReadConsoleInput(hIn,& input, 1, &NumRead);

		switch (input.EventType){
		case MOUSE_EVENT:
				// Assign variables
				UserMouse.crdPosition = input.Event.MouseEvent.dwMousePosition;
				UserMouse.dwButtonState = input.Event.MouseEvent.dwButtonState;

				// Set mouse position
				SetCursorPosition(UserMouse.crdPosition);
				SetConsoleTextAttribute(hOut, HOVER_COLOR);
				return;
		}
	}
}

// Set cursor position
void Console::SetCursorPosition(const COORD crdPosition) {
	SetConsoleCursorPosition(hOut, crdPosition);
}

char Console::ChangeColor(char (*ptrGetChar)(Board* board, unsigned x, unsigned y), Board* board) {
	SetConsoleTextAttribute(hOut, NORMAL_COLOR);
	return  ptrGetChar(board, UserMouse.crdPosition.X, UserMouse.crdPosition.Y);
}