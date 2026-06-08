#include "Pickaxe.h"

string pickaxeName = "낡아빠진 곡괭이";
Color pickaxeColor = Color::LIGHT_GRAY;

void InitPickaxe(int x, int y)
{
    SetUnicodeMode();
    SetColor(pickaxeColor);
    vector<wstring> art = {
        L"        ⠀⠀⠀⢀⣀⣀⣀⠀⠀⠀",
        L"        ⠀⠀⠀⠺⠿⠿⢿⣷⣶⡆",
        L"        ⠀⠀⠀⠀⠀⣠⣾⠟⣿⣷",
        L"        ⠀⠀⠀⣠⣾⠟⠁⠀⣿⣿",
        L"        ⠀⣠⣾⠟⠁⠀⠀⠀⠈⠃",
        L"        ⠘⠛⠁⠀              ",
    };
    for (int i = 0; i < (int)art.size(); i++)
    {
        GoToXY(x, y + i);
        wcout << art[i];
    }
    SetColor();
    SetDefaultMode();
   
    GoToXY(0, y - 2);
    for (int i = 0; i < WIDTH - 1; i++)
    {
        cout << "─";
    }
}

void RenderPickaxe()
{
    GoToXY(WIDTH - (int)pickaxeName.size(), HEIGHT - 1);
    SetColor(Color::WHITE);
    cout << pickaxeName;
    SetColor();
}