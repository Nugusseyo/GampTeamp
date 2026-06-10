#include "TimingBar.h"

string timingGameTitle = "타이밍 게임 ";
int barWidth = 15;
int barValue = 0;
int barTimingRange = 1;
int barNearTimingRange = 2;
int barChargeMs = 10;
int baseBarChargeMs = barChargeMs;
int curTick = 0;
bool barChargeDir = true;

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