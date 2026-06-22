#pragma once
#include "Console.h"
#include "GameState.h"

static vector<int> pickaxeWidthCache;   

struct PickaxeData
{
    string name;
    Color color;
    vector<wstring> art;
};

static vector<PickaxeData> pickaxeTable =
{
    {
        "낡아빠진 곡괭이", Color::GRAY,
        {
            L"   ⠀⢀⣀⣀⣀⣀⠀⠀⠀⠀",
            L"⠀⠀⠀⣾⣭⣭⣭⡍⣶⣶⡆⠀",
            L"⠀⠀⠀⠈⠋⠉⣩⣾⣀⠿⣇⠀",
            L"⠀⠀⠀⠀⣠⣾⣿⠟⢹⡿⣿⡀",
            L"⠀⠀⣠⣾⣿⠏⠁⠀⠸⢟⡿⠄",
            L"⢀⣸⣿⡧⠛⠀⠀⠀⠀⠘⠃⠀",
            L"⠘⠿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        }
    },
    {
        "중국산 곡괭이", Color::WHITE,
        {
            L"⠀⠀⠀⠐⢆⡀⠀⠀⠀⠀⠀",
            L"⠀⠀⠀⠀⠀⠙⢦⡀⠀⠀⠀",
            L"⠀⠀⠀⠀⠀⢀⡾⣷⢆⠀⠀",
            L"⠀⠀⠀⠀⣠⣿⠏⠀⠀⠓⠄",
            L"⠀⠀⢀⣴⡟⠁⠀⠀⠀⠀⠈",
            L"⠀⣠⣿⠋⠀⠀⠀⠀⠀⠀⠀",
            L"⠌⡽⠁⠀⠀⠀⠀⠀⠀⠀⠀",
        }
    },
    {
        "그냥 곡괭이", Color::GREEN,
        {
            L"⠀⠀⠀⠐⢆⡀⠀⠀⠀⠀⠀",
            L"⠀⠀⠀⠀⠀⠙⢦⡀⠀⠀⠀",
            L"⠀⠀⠀⠀⠀⢀⡾⣷⢆⠀⠀",
            L"⠀⠀⠀⠀⣠⣿⠏⠀⠀⠓⠄",
            L"⠀⠀⢀⣴⡟⠁⠀⠀⠀⠀⠈",
            L"⠀⣠⣿⠋⠀⠀⠀⠀⠀⠀⠀",
            L"⠌⡽⠁⠀⠀⠀⠀⠀⠀⠀⠀",
        }
    },
    {
        "간지나는 곡괭이", Color::CYAN,
        {
            L"⠀⠀⠀⠀⢰⣶⣴⣆⡰⠀⠀⠀",
            L"⠀⠀⠀⠀⠀⠉⠛⣿⣿⣶⡆⠀",
            L"⠀⠀⠀⠀⠀⠀⢠⣾⣿⣯⣤⠀",
            L"⠀⠀⠀⠀⠀⣠⠟⠁⠙⠿⠻⢇",
            L"⠀⠀⠀⢠⠞⠁⠀⠀⠀⠀⠀⠀",
            L"⠀⠀⡠⠃⠀⠀⠀⠀⠀⠀⠀⠀",
            L"⠐⠚⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
        }
    },
    {
        "개쩌는 곡괭이", Color::YELLOW,
        {
            L"⠀⠀⢀⡠⠠⠀⠀⠀",
            L"⠀⠀⠐⣾⣧⡄⠀⠀",
            L"⠀⠀⠀⣻⣿⠿⣦⠀",
            L"⠀⠀⢺⠟⠀⠀⠈⠄",
            L"⠀⠀⠊⠀⠀⠀⠀⠀",
            L"⠀⡘⠀⠀⠀⠀⠀⠀",
            L"⠐⠃⠀⠀⠀⠀⠀⠀",
        }
    },
    {
        "네.더.라.이.트. 곡괭이", Color::VIOLET,
        {
            L"⠀⠀⢀⣀⣀⠀⠀⠀⠀⠀⠀",
            L"⠀⠀⠈⠈⠛⣯⣀⠀⠀⠀⠀",
            L"⠀⠀⠀⠀⢐⢫⡿⠛⢿⡆⠀",
            L"⠀⠀⠀⠀⣸⠇⠁⠀⠀⠿⡆",
            L"⠀⠀⠀⡸⠁⠀⠀⠀⠀⠀⠡",
            L"⠀⢀⠞⠀⠀⠀⠀⠀⠀⠀⠀",
            L"⢠⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        }
    }
};

void ClearPickaxe(int x, int y);
void RenderPickaxe(int x, int y);
void RenderPickaxeName();
void InitPickaxeCache();