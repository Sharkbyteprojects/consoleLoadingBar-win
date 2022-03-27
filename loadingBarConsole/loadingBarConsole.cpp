#include "framework.h"
#include "loadingBarConsole.h"

CloadingBarConsole::CloadingBarConsole() :pcent(0)
{
	pcent = (int*)std::malloc(sizeof(int));
	memset(pcent, 0, sizeof(int));
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	return;
}

#define colorA(cc) (cc==colorcode::OK ? (BACKGROUND_GREEN) : \
	cc == colorcode::SUSPEND ? (BACKGROUND_RED | BACKGROUND_GREEN) : BACKGROUND_RED)

void CloadingBarConsole::render()
{
	CONSOLE_SCREEN_BUFFER_INFO i;
	ZeroMemory(&i, sizeof(i));
	double xt = static_cast<double>(*pcent) / 100.0;
	SHORT xs = 100;
	if (GetConsoleScreenBufferInfo(hConsole, &i) != 0) {
#define apx 3
		xt *= i.dwSize.X - apx;
		xs = (i.dwSize.X - 1) - apx;
#undef apx
		if (i.dwCursorPosition.X > 0)
			std::cout << "\r" << std::flush;
	}
	else {
		xt *= 100;
		std::cout << "\r" << std::flush;
	}

	for (int c = 0; c <= xs; c++) {
		SetConsoleTextAttribute(hConsole, colorA(cc) | (c >= xt ? 0 : BACKGROUND_INTENSITY));
		std::cout << " ";
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void CloadingBarConsole::setPercent(int percent)
{
	*pcent = percent;
}

CloadingBarConsole::~CloadingBarConsole()
{
	std::free(pcent);
}

void CloadingBarConsole::setColorCode(colorcode cc)
{
	this->cc = cc;
}
