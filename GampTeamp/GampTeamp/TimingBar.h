#pragma once
#include "Console.h"
#include "GameState.h"

extern string timingGameTitle;
extern int barWidth;
extern int barValue;
extern int barTimingRange;
extern int barNearTimingRange;
extern int barChargeMs;
extern int baseBarChargeMs;
extern int curTick;
extern bool barChargeDir;

void UpdateTimingBar();
void RenderTimingBar();