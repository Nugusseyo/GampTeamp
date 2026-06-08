#include "Console.h"
#include "GameState.h"

string timingGameTitle = "타이밍 게임 ";
string pickaxeName = "낡아빠진 곡괭이";
Color pickaxeColor = Color::LIGHT_GRAY;
int barWidth = 15;
int barValue = 0;
int barTimingRange = 1;
int barNearTimingRange = 2;
int barChargeMs = 10;
int baseBarChargeMs = barChargeMs;
int curTick = GetTickCount64();
bool barChargeDir = true;

GameState gameState = {};

Position& pos = gameState.player.pos;
Position prev = pos;

void Init();
void Update();
void Render();
void UpdateTimingBar();
void RenderTimingBar();
void RenderPickaxe();

void AsciiInit(int x, int y)
{
    SetUnicodeMode();
    SetColor(pickaxeColor);

    vector<wstring> pickaxe =
    {
        L"        ⠀⠀⠀⢀⣀⣀⣀⠀⠀⠀",
        L"        ⠀⠀⠀⠺⠿⠿⢿⣷⣶⡆",
        L"        ⠀⠀⠀⠀⠀⣠⣾⠟⣿⣷",
        L"        ⠀⠀⠀⣠⣾⠟⠁⠀⣿⣿",
        L"        ⠀⣠⣾⠟⠁⠀⠀⠀⠈⠃",
        L"        ⠘⠛⠁⠀              ",
    };

    for (int i = 0; i < pickaxe.size(); i++)
    {
        GoToXY(x, y + i);
        wcout << pickaxe[i];
    }

    SetColor();
    SetDefaultMode();
}

int main()
{
	Init();

    srand((unsigned int)nullptr);

    pos.x = (WIDTH - 1) / 2;

	while (true)
	{
        UpdateInput();
        Update();
        Render();
		UpdateTimingBar();
        RenderTimingBar();
        RenderPickaxe();
		FrameSync(60);
	}

	return 0;
}

void Init()
{
    SetConsoleSize(WIDTH, HEIGHT);
    SetConsoleMouseInputDisabled();
    SetCursorVisible(false);
	SetConsoleWindowStyle(false);

    AsciiInit(WIDTH - 18, HEIGHT - 6);
}


void Update()
{
    ULONGLONG now = GetTickCount64();
    if (now - gameState.player.lastMoveTime >= gameState.player.moveInterval)
    {
        if (GetKey(VK_UP) || GetKey('W')) pos.y--;
        if (GetKey(VK_DOWN) || GetKey('S')) pos.y++;
        if (GetKey(VK_LEFT) || GetKey('A')) pos.x--;
        if (GetKey(VK_RIGHT) || GetKey('D')) pos.x++;

        // 경계 클램프
        pos.x = max(0, min(WIDTH - 1, pos.x));
        pos.y = max(0, min(HEIGHT - 8, pos.y));

        if (!(prev == pos))
            gameState.player.lastMoveTime = now;
    }
}

void Render()
{
    static Position prevPos = gameState.player.pos;
    Position& pos = gameState.player.pos;

    // 이전 위치 지우기
    GoToXY(prevPos.x, prevPos.y);
    cout << ' ';

    // 현재 위치 그리기
    GoToXY(pos.x, pos.y);
    SetColor(Color::CYAN);
    cout << '@';
    SetColor();

    prevPos = pos;
}

void UpdateTimingBar()
{
    if (GetKeyDown(VK_SPACE))
    {
        int center = barWidth / 2;
        int timingStart = center - barTimingRange;
        int timingEnd = center + barTimingRange;
        int nearTimingStart = timingStart - barNearTimingRange;
        int nearTimingEnd = timingEnd + barNearTimingRange;

        if (barValue >= timingStart && barValue <= timingEnd)
        {
            GoToXY(timingGameTitle.length() + barWidth - 4, HEIGHT - 2);
            SetColor(Color::LIGHT_GREEN);
            cout << " 성공!!           ";
            SetColor();
            ShakeConsoleWindow(15, 200, 20);
        }
        else if (barValue >= nearTimingStart && barValue <= nearTimingEnd)
        {
            GoToXY(timingGameTitle.length() + barWidth - 5, HEIGHT - 2);
            SetColor(Color::LIGHT_YELLOW);
            cout << "애매하다;;     ";
            SetColor();
            ShakeConsoleWindow(8, 120, 15);
        }
        else
        {
            GoToXY(timingGameTitle.length() + barWidth - 4, HEIGHT - 2);
            SetColor(Color::LIGHT_RED);
            cout << "실패ㅜㅜ       ";
            SetColor();
            ShakeConsoleWindow(5, 80, 10);
        }

        barChargeMs = baseBarChargeMs + (rand() % 5 - 2);
        barChargeMs = max(1, barChargeMs);
    }

    if (GetTickCount64() - curTick >= barChargeMs)
    {
        if (barValue == barWidth - 1)
            barChargeDir = false;
        else if (barValue == 0)
            barChargeDir = true;
        if (barChargeDir)
            barValue++;
        else
            barValue--;
        curTick = GetTickCount64();
    }
}

void RenderTimingBar()
{
    DrawTimingBar(0, HEIGHT - 1, timingGameTitle, barValue, barWidth, barWidth, barTimingRange, barNearTimingRange);
}

void RenderPickaxe()
{
    GoToXY(WIDTH - pickaxeName.size(), HEIGHT - 1);
    SetColor(Color::WHITE);
    cout << pickaxeName;
    SetColor();
}