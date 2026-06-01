#include "Console.h"
#include "GameState.h"

string timingGameTitle = "타이밍 게임 ";
int barWidth = 15;
int barValue = 0;
int barTimingRange = 1;
int barNearTimingRange = 2;
int barChargeMs = 30;
int curTick = GetTickCount64();
bool barChargeDir = true;

void Init();
void Update();
void Render();
void UpdateTimingBar();
void RenderTimingBar();

int main()
{

	Init();

	while (true)
	{
		UpdateTimingBar();
		RenderTimingBar();
		FrameSync(60);
	}

	return 0;
}

void Init()
{
	SetConsoleSize(WIDTH, HEIGHT);
	SetConsoleWindowStyle(true);
}

void Update()
{

}

void Render()
{

}

void UpdateTimingBar()
{
    UpdateInput();

    if (GetKeyDown(VK_SPACE))
    {
        int center = barWidth / 2;
        int timingStart = center - barTimingRange;
        int timingEnd = center + barTimingRange;
        int nearTimingStart = timingStart - barNearTimingRange;
        int nearTimingEnd = timingEnd + barNearTimingRange;

        if (barValue >= timingStart && barValue <= timingEnd)
        {
            GoToXY(0, HEIGHT - 3);
            SetColor(Color::LIGHT_GREEN);
            cout << "성공!  ";
            SetColor();
            ShakeConsoleWindow(15, 200, 20);
        }
        else if (barValue >= nearTimingStart && barValue <= nearTimingEnd)
        {
            GoToXY(0, HEIGHT - 3);
            SetColor(Color::LIGHT_YELLOW);
            cout << "아쉽!  ";
            SetColor();
            ShakeConsoleWindow(8, 120, 15);
        }
        else
        {
            GoToXY(0, HEIGHT - 3);
            SetColor(Color::LIGHT_RED);
            cout << "실패!  ";
            SetColor();
            ShakeConsoleWindow(5, 80, 10);
        }
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