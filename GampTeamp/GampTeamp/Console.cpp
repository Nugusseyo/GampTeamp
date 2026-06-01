#include "Console.h"

void SetUnicodeMode()
{
	(void)_setmode(_fileno(stdout), _O_U16TEXT);
}

void SetDefaultMode()
{
	(void)_setmode(_fileno(stdout), _O_TEXT);
}

void RenderChar(char c, int delayTime, bool isSkip)
{
	cout << c;
	if (strchr("@#$%^&*", c))
	{

	}
	if (isSkip)
		return;
	int calcDelay = delayTime + (rand() % 11 - 5);

	switch (c)
	{
	case '#':
		Sleep(100);
		cout << "\b \b";
		break;
	case '?':
		calcDelay += 300; // 0.3초
		break;
	case '!':
		calcDelay += 200; // 0.2초
		break;
	case '.':
		calcDelay += 400; // 0.4초
		break;
	case '\n':
		calcDelay += 500; // 0.5초
		break;
	case ' ':
		calcDelay += 50; // 0.05초
		break;
	}
	Sleep(std::max(0, calcDelay));
}

void RenderDialogue(const string& text, int delayTime)
{
	bool isSkip = false;
	for (int i = 0; i < text.size(); i++)
	{
		if (!isSkip && _kbhit())
		{
			_getch();
			isSkip = true;
		}
		RenderChar(text[i], delayTime, isSkip);
	}
}

void SetConsoleGameTitle(const wstring& title)
{
	SetConsoleTitle(title.c_str());
}

void SetConsoleSize(int width, int height)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// 뷰포트
	SMALL_RECT rect = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(handle, true, &rect);

	// 버퍼
	COORD size = { (short)width, (short)height };
	SetConsoleScreenBufferSize(handle, size);

	rect.Right = width - 1;
	rect.Bottom = height - 1;
	SetConsoleWindowInfo(handle, true, &rect);

	// 가운데 설정
	HWND hWnd = GetConsoleWindow();

	//RECT windowRect;
	//GetWindowRect(hWnd, &windowRect);
	//int windowWidth = windowRect.right - windowRect.left;
	//int windowHeight = windowRect.bottom - windowRect.top;

	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(handle, false, &fontInfo);

	int windowWidth = fontInfo.dwFontSize.X * width;
	int windowHeight = fontInfo.dwFontSize.Y * height;
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int posX = (screenWidth - windowWidth) / 2;
	int posY = (screenHeight - windowHeight) / 2;

	SetWindowPos(hWnd, nullptr, posX, posY, 0, 0, SWP_NOSIZE);
}

void SetConsoleFullscreen()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(handle, false, &fontInfo);

	SetConsoleDisplayMode(handle,
		CONSOLE_FULLSCREEN_MODE, 0);

	int wWidth = GetSystemMetrics(SM_CXSCREEN) / fontInfo.dwFontSize.X;
	int wHeight = GetSystemMetrics(SM_CYSCREEN) / fontInfo.dwFontSize.Y;

	SetConsoleSize(wWidth, wHeight);
}

void SetConsoleWindowStyle(bool showTitleBar)
{
	HWND hWnd = GetConsoleWindow();
	LONG style = GetWindowLong(hWnd, GWL_STYLE);
	// NAND
	style &= ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_SYSMENU;

	if (!showTitleBar)
		style &= ~WS_CAPTION;

	SetWindowLong(hWnd, GWL_STYLE, style);

	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0,
		SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}

void SetConsoleFont(const wstring& fontName, COORD size, UINT weight)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info = {};
	info.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	info.dwFontSize = size; // 폭, 높이
	info.FontWeight = weight; // FW_ ~ 
	// 폰트 이름 복사
	wcscpy_s(info.FaceName, fontName.c_str());
	SetCurrentConsoleFontEx(handle, false, &info);

}

void ShakeConsoleWindow(int intensity, int duration, int interval)
{
	// intensity : 얼마나 세게 줄지 쉐이크 강도
	// duration : 얼마나 오래 흔들지 시간
	// interval : 한번 흔들고 덤
	HWND hWnd = GetConsoleWindow();
	RECT windowRect;
	GetWindowRect(hWnd, &windowRect);
	int originX = windowRect.left;
	int originY = windowRect.top;

	int cnt = duration / interval;
	for (int i = 0; i < cnt; i++)
	{
		// -10 ~ 10
		// // rand() % 21 - 10;
		// -intensity ~ +intensity;
		int offsetX = rand() % (intensity * 2 + 1) - intensity;
		int offsetY = rand() % (intensity * 2 + 1) - intensity;
		SetWindowPos(hWnd, nullptr,
			originX + offsetX,
			originY + offsetY,
			0, 0, SWP_NOSIZE);
		Sleep(interval);
	}

	SetWindowPos(hWnd, nullptr, originX, originY, 0, 0, SWP_NOSIZE);
}

void GoToXY(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD curPos = { (short)x, (short)y };
	SetConsoleCursorPosition(handle, curPos);
}

BOOL IsGoToXY(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD curPos = { (short)x, (short)y };
	return SetConsoleCursorPosition(handle, curPos);
}

void SetCursorVisible(bool visible, DWORD size)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = visible; // on, off
	curInfo.dwSize = size; // 1 ~ 100
	SetConsoleCursorInfo(handle, &curInfo);
}

COORD GetConsoleResolution()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	short width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	short height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	//return COORD{ width, height };
	return { width, height };
}

void SetColor(Color textColor, Color bgColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int text = (int)textColor;
	int bg = (int)bgColor;
	SetConsoleTextAttribute(handle, (bg << 4) | text);
}

void DrawBar(int x, int y, const string& label, int value, int maxValue, int barWidth, const string& fillChar, const string& emptyChar)
{
	Color color;
	if (value > maxValue * 0.6f)
		color = Color::LIGHT_GREEN;
	else if (value > maxValue * 0.3f)
		color = Color::LIGHT_YELLOW;
	else
		color = Color::LIGHT_RED;

	GoToXY(x, y);
	SetColor();
	cout << label;
	SetColor(color);

	int filledCount = barWidth * value / maxValue;
	for (int i = 0; i < barWidth; i++)
		cout << (i < filledCount ? fillChar : emptyChar);
	SetColor();
	// 10 / 100
	int digits = std::to_string(maxValue).length();
	cout << " " << std::setw(digits) << value << "/" <<
		std::setw(digits) << maxValue;

}

void DrawLine(char ch, int width)
{
	cout << std::setfill(ch) << std::setw(width) << "" << std::setfill(' ');
}

bool GetKey(int vKey)
{
	return GetAsyncKeyState(vKey) & 0x8000;
}
constexpr int KEY_COUNT = 256;
static bool prevDown[KEY_COUNT] = {};
static bool curDown[KEY_COUNT] = {};
bool GetKeyDown(int vKey)
{
	return curDown[vKey] && !prevDown[vKey];
}

void UpdateInput()
{
	for (int i = 0; i < 256; i++)
	{
		prevDown[i] = curDown[i];
		curDown[i] = GetAsyncKeyState(i) & 0x8000;
	}

	//bool cur = GetAsyncKeyState(vKey) & 0x8000;
	//bool down = cur && !prevDown[vKey];
	//prevDown[vKey] = cur;
	//return down;
}

void SetConsoleMouseInputDisabled()
{
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(handle, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode &= ~ENABLE_INSERT_MODE;

	mode |= ENABLE_MOUSE_INPUT;

	mode |= ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(handle, mode);
}

POINT GetMouseCellPos()
{
	POINT pt;
	GetCursorPos(&pt);
	HWND hWnd = GetConsoleWindow();
	ScreenToClient(hWnd, &pt);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(handle, false, &fontInfo);

	POINT cellPos = { pt.x / fontInfo.dwFontSize.X,
		pt.y / fontInfo.dwFontSize.Y };

	return POINT();
}

void FrameSync(int fps)
{
	static ULONGLONG prevTick = GetTickCount64();
	ULONGLONG curTick = GetTickCount64();
	ULONGLONG targetTick = 1000 / fps;
	ULONGLONG elapsed = curTick - prevTick;
	if (elapsed < targetTick)
	{
		Sleep(targetTick - elapsed);
	}

	prevTick = GetTickCount64();
	prevTick = curTick;
}
