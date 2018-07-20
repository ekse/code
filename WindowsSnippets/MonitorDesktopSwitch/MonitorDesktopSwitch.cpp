#include "stdafx.h"
#include "Windows.h"

#include <iostream>

int main()
{
	HANDLE event = OpenEvent(SYNCHRONIZE, true, L"WinSta0_DesktopSwitch");
	
	if (!event) {
		std::cout << "OpenEvent failed: " << std::endl;
	}
	while (true) {
		if (WaitForSingleObject(event, INFINITE) == WAIT_OBJECT_0) {
			std::cout << "WinSta0_DesktopSwitch was signaled" << std::endl;
			HDESK desktop = OpenInputDesktop(NULL, true, GENERIC_READ);
			if (!desktop) {
				std::cout << "Failed to open desktop" << std::endl;
				return -1;
			}

			wchar_t desktop_name[100];
			if (GetUserObjectInformation(desktop, UOI_NAME, desktop_name, sizeof(desktop_name), nullptr)) {
				std::wcout << L"Desktop name: " << desktop_name << std::endl;
			}
			// Query UOI_USER_SID to get the SID of the user associated to the desktop.
		}
	}
	return 0;
}

