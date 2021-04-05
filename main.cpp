#include "visual.h"
#include "stdh.h"

using namespace std;

STATUS state = RUNNING_1;

int main()
{
	SetConsoleWnd();
	bool isJumping = false;
	bool isGrounded = true;
	int gravity = 4;
	int gC;
	int Score = 0;
	double tScore = 0;
	time_t t0, t1;

	COORD ch_Pos = { 7, GROUND };
	COORD sp_Pos = { SPK_RESET, GROUND };

	t0 = clock();
	while (true)
	{
		if (GetKeyDown() == 'z' && isGrounded)
		{
			isJumping = true;
			isGrounded = false;
			state = JUMPING;
		}

		gC = GravityCount(&gravity, isJumping, isGrounded);

		if (!isJumping)
		{
			ch_Pos.Y += gC;
		}
		else
		{
			ch_Pos.Y -= gC;
		}

		if (ch_Pos.Y >= GROUND)
		{
			ch_Pos.Y = GROUND;
			isGrounded = true;

			if (state == JUMPING)
			{
				state = RUNNING_1;
			}
		}

		if (sp_Pos.X <= 0)
		{
			sp_Pos.X = SPK_RESET;
			Score += 50;
		}

		sp_Pos.X -= 2;


		if (gC <= 0)
		{
			isJumping = false;
		}

		int col = DrawSpike(sp_Pos);
		DrawCharacter(ch_Pos, &state);
		DrawGround(GROUND);
		DrawBoard(Score, GROUND);

		if (Collision(ch_Pos, sp_Pos, col))
			break;

		Sleep(20);
		system("cls");
	}
	t1 = clock();
	tScore = (double)(t1 - t0) / CLOCKS_PER_SEC;

	system("cls");
	Cursor(21, 10);
	cout << "Game Over!" << endl << endl << endl;
	Cursor(20, 13);
	cout << "Score : " << Score;
	Cursor(20, 14);
	cout << "time : " << tScore << " 초" << endl << endl << endl;;
	system("pause");

	return 0;
}
