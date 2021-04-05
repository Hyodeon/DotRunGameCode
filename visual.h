#pragma once
#include "stdh.h"

using namespace std;

void SetConsoleWnd()
{
	system("mode con:cols=100 lines=25");
	system("title Dot Run! by Hyojin");
}

void Cursor(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}

	return 0;
}

void DrawCharacter(COORD ch, STATUS* status)
{
	Cursor(ch.X, ch.Y);

	switch (*status)
	{
	case RUNNING_1:
		cout << "■";
		*status = RUNNING_2;
		break;
	case RUNNING_2:
		cout << "◆";
		*status = RUNNING_1;
		break;
	case JUMPING:
		cout << "●";
		break;
	}
}

int DrawSpike(COORD sp)
{
	static int size_tree = 3;

	srand((unsigned int)time(NULL));

	if (sp.X <= 0)
		size_tree = rand() % 6 + 1;

	if (!(sp.X <= 0))
	{
		for (int i = 0; i < size_tree + 1; i++)
		{
			Cursor(sp.X, sp.Y - (size_tree - i));
			cout << "▲";
		}
	}

	return size_tree;
}

void DrawGround(int Ground)
{
	for (int i = 0; i < 8; i++)
	{
		Cursor(i, Ground + 1);
		cout << "......................................................................................";
	}
}

void DrawBoard(int Score, int Ground)
{
	Cursor(18, Ground + 3);
	printf("[ Score	: %d	]", Score);
	Cursor(0, Ground + 8);
}

int GravityCount(int* gravity, const bool& jump, const bool& ground)
{
	static int Cnt = 0;
	static bool isDown = false;
	int temp;

	if (!ground)
	{
		if (jump)
		{
			if (Cnt == -1)
				Cnt++;

			temp = Cnt;
			Cnt++;

			return (*gravity - temp);
		}
		else if (!jump)
		{
			if (Cnt == *gravity + 1)
				Cnt--;

			temp = Cnt;
			Cnt--;

			return (*gravity - temp);
		}
	}

	return 0;

}

bool Collision(COORD player, COORD opp, int op_size)
{
	if (opp.X >= player.X - 1 && opp.X <= player.X + 1)
	{
		for (int i = 0; i < op_size; i++)
		{
			if (player.Y == opp.Y - i)
				return true;
		}
	}
	
	return false;
}
