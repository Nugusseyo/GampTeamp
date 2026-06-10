#pragma once
#include "Enums.h"
#include <Windows.h>
#include <vector>

constexpr int MAP_WIDTH = 21;
constexpr int MAP_HEIGHT = 20;
constexpr int WIDTH = 90;
constexpr int HEIGHT = 50;

struct Position
{
	int x; int y;
	// 연산자 오버로딩
	bool operator==(const Position& other) const
	{
		return x == other.x && y == other.y;
	}
};

struct Player
{
	Position pos = { 0, 0 };
	bool isAlive = true;
	int moveInterval = 50;
	ULONGLONG lastMoveTime = 0;
	bool isTrans = false;
	ULONGLONG lastDashTime = 0;
};
struct GameState
{
	Scene prevScene = Scene::NONE;
	Scene curScene = Scene::INGAME;
	Menu curMenu = Menu::START;
	bool isRunning = true;
	Block map[MAP_HEIGHT][MAP_WIDTH] = {};
	Player player;
	ULONGLONG curTime;
};

extern GameState gameState;