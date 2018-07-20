#include "stdafx.h"

#include <iostream>

#include "Windows.h"

BOOL EnumDesktopCallback(LPSTR desktop, LPARAM lParam)
{
	std::cout << "Desktop name: " << desktop << std::endl;
	return TRUE;
}

int main()
{
	while (true)
	{
		EnumDesktopsA(GetProcessWindowStation(), EnumDesktopCallback, 0);
		std::cout << std::endl;
		Sleep(2000);
	}
	
	return 0;
}

