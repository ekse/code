
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>

#define SLEEP_SECONDS 1000
#define WINDOW_TEXT_SIZE 100

int main()
{
	HWND activeWindow;
	DWORD activePid;
	TCHAR title[WINDOW_TEXT_SIZE];
	size_t bytesWritten;
	
	while (true) {
		activeWindow = GetForegroundWindow();
		
		if (!activeWindow) {
			printf("no active window\n");
			goto next;
		}

		bytesWritten = GetWindowText(activeWindow, title, WINDOW_TEXT_SIZE);
		
		if (bytesWritten == 0) {
			printf("failed to read window title\n");
			goto next;
		}

		GetWindowThreadProcessId(activeWindow, &activePid);

		printf("Active window: %ls pid: %d\n", title, activePid);

	   next:
		Sleep(5 * SLEEP_SECONDS);
	}

    return 0;
}

