#include "EndingScene.h"

string titleText = "플레이해주셔서감사합니다조이고";
string btn1Text = "이어하기";
string btn2Text = "나가기";

bool continueSelected = true;

void UpdateEnding()
{
	if (gameState.curScene != Scene::ENDING) return;

	if (GetKeyDown('W') || GetKeyDown('w'))
	{
		continueSelected = true;
	}
	else if (GetKeyDown('S') || GetKeyDown('s'))
	{
		continueSelected = false;
	}
}

void RenderEnding()
{
	if (gameState.curScene != Scene::ENDING) return;

	GoToXY(WIDTH / 2 - titleText.length() / 2, HEIGHT / 3);
	cout << titleText;

	GoToXY(WIDTH / 2 - btn1Text.length() / 2, HEIGHT - HEIGHT / 3);
	cout << btn1Text;

	GoToXY(WIDTH / 2 - btn2Text.length() / 2, HEIGHT - HEIGHT / 3 + 1);
	cout << btn2Text;

	if (continueSelected)
	{
		GoToXY(WIDTH / 2 - btn2Text.length() / 2 - 3, HEIGHT - HEIGHT / 3 + 1);
		cout << "  ";
		GoToXY(WIDTH / 2 - btn1Text.length() / 2 - 3, HEIGHT - HEIGHT / 3);
	}
	else
	{
		GoToXY(WIDTH / 2 - btn2Text.length() / 2 - 3, HEIGHT - HEIGHT / 3);
		cout << "  ";
		GoToXY(WIDTH / 2 - btn1Text.length() / 2 - 3, HEIGHT - HEIGHT / 3 + 1);
	}

	cout << "▶";
}
