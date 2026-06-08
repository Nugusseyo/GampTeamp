#include "Player.h"

void UpdatePlayer()
{
    ULONGLONG now = GetTickCount64();
    if (now - gameState.player.lastMoveTime >= gameState.player.moveInterval)
    {
        Position& pos = gameState.player.pos;
        Position before = pos;
        if (GetKey(VK_UP) || GetKey('W')) pos.y--;
        if (GetKey(VK_DOWN) || GetKey('S')) pos.y++;
        if (GetKey(VK_LEFT) || GetKey('A')) pos.x--;
        if (GetKey(VK_RIGHT) || GetKey('D')) pos.x++;
        pos.x = max(0, min(WIDTH - 1, pos.x));
        pos.y = max(0, min(HEIGHT - 9, pos.y));
        if (!(before == pos))
            gameState.player.lastMoveTime = now;
    }
}

void RenderPlayer()
{
    static Position prevPos = gameState.player.pos;
    Position& pos = gameState.player.pos;
    GoToXY(prevPos.x, prevPos.y);
    cout << ' ';
    GoToXY(pos.x, pos.y);
    SetColor(Color::CYAN);
    cout << '@';
    SetColor();
    prevPos = pos;
}