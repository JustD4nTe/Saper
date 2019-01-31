#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>

struct Timer {
	HANDLE hOut;
	short x;
	Timer() {};
	Timer(short width, HANDLE handlerOut) : x(width), hOut(handlerOut) {};
	void StartTimer() {
		/*SetConsoleCursorPosition(hOut, COORD{x, 5});
		std::cout << "Timer: " << std::flush;*/
		unsigned min = 0;
		unsigned sec = 0;
		auto start = std::chrono::high_resolution_clock::now();
		while(true){
			if (sec == 60) {
				min++;
				sec = 0;
			}
			SetConsoleCursorPosition(hOut, COORD{ x + 8, 5 });
			std::cout  << (sec++ > 10 ? sec : ( '0' + (char)sec)) << std::flush;
			std::this_thread::sleep_until(start + (sec + 1)*std::chrono::seconds(1));
		}
	}
};