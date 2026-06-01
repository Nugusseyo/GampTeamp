#pragma once
#include <iostream>
#include <io.h>
#include <fcntl.h>
//#include <string>
#define NOMINMAX
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <string>
#pragma comment(lib, "winmm.lib")

using std::cout;
using std::endl;
using std::wcout;
using std::string;
using std::wstring;

// 아스키 아트
void SetUnicodeMode();
void SetDefaultMode();

// 다이얼로그
void RenderChar(char c, int delayTime, bool isSkip);
void RenderDialogue(const string& text, int delayTime);

// 창
void SetConsoleGameTitle(const wstring& title);
void SetConsoleSize(int width, int height);
void SetConsoleFullscreen();
void SetConsoleWindowStyle(bool showTitleBar);
void SetConsoleFont(const wstring& fontName, COORD size, UINT weight = FW_NORMAL);

void ShakeConsoleWindow(int intensity, int duration, int interval);
void GoToXY(int x, int y);
BOOL IsGoToXY(int x, int y);
void SetCursorVisible(bool visible, DWORD size = 1);
COORD GetConsoleResolution();

enum class Color
{
    BLACK, BLUE, GREEN, SKYBLUE, RED,
    VIOLET, YELLOW, LIGHT_GRAY, GRAY, LIGHT_BLUE,
    LIGHT_GREEN, CYAN, LIGHT_RED, LIGHT_VIOLET,
    LIGHT_YELLOW, WHITE, END
};
void SetColor(Color textColor = Color::WHITE, Color bgColor = Color::BLACK);
void DrawBar(int x, int y, const string& label,
    int value, int maxValue, int barWidth,
    const string& fillChar = "■", const string& emptyChar = "□");
void DrawTimingBar(int x, int y, const string& label,
    int value, int maxValue, int barWidth, int timingRange,
    int nearTimingRange,
    const string& fillChar = "■", const string& emptyChar = "□");

void DrawLine(char ch, int width);

bool GetKey(int vKey);
bool GetKeyDown(int vKey);
void UpdateInput();
void SetConsoleMouseInputDisabled();
POINT GetMouseCellPos();
void FrameSync(int fps);