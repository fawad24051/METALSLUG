#include <iostream>
#include "raylib.h"
//#include <Windows.h>

using namespace std;
struct pos
{
	int row, col;
};
const int screenwidth = 1200;
const int screenheight = 1000;
enum direction
{
	UP, RIGHT, LEFT, BOTTOM
};
int main()
{
	InitWindow(screenwidth, screenheight, "METAL SLUG GAME");


	bool pic = true;

	Texture2D bgImage = LoadTexture("background.png");
	Texture2D bgImage2 = LoadTexture("background2.png");
	Texture2D player = LoadTexture("player.png");
	Texture2D player_left = LoadTexture("PlayerLeft.png");
	Texture2D player_jump = LoadTexture("PlayerJump.png");
	Texture2D player_shootR = LoadTexture("shootingR.png");
	Texture2D player_shootL = LoadTexture("shootingL.png");
	Texture2D player_shootU = LoadTexture("shootingR.png");
	Texture2D player_bulletR = LoadTexture("bullet.png");



	player.height = screenheight / 8;
	player.width = screenwidth / 8;

	player_bulletR.width = player.width / 6;
	player_bulletR.height = player.height / 2;

	player_shootL.height = player.height, player_shootL.width = player.width;
	player_shootR.height = player.height, player_shootR.width = player.width;
	player_shootU.height = player.height, player_shootU.width = player.width;
	player_left.height = player.height;
	player_left.width = player.width;

	player_jump.height = player.height;
	player_jump.width = player.width;
	pos bullet;

	bgImage.height = screenheight;
	bgImage.width = screenwidth;
	bgImage2.height = screenheight;
	bgImage2.width = screenwidth;
	direction gun_direction=UP;
	int bg1x = 0;
	int bg2x = bgImage2.width;
	SetTargetFPS(60);


	int p1x = screenwidth / 4 - 300;

	int leftcondition = screenwidth / 4 - 300;
	int rightcondition = screenwidth - 150;

	int belowcondition = screenheight / 2 + 150;
	int p1y = screenheight / 2 + 150;
	int temp_p1y = p1y;
	bool right_click = false, left_click = false, up_click = false, isPaused = false;;






	while (!WindowShouldClose())
	{
		bullet.row = p1x;
		bullet.col = temp_p1y;

		int temp_bulletRx = bullet.row +140 ;

		if (!isPaused)
		{
			pic = true;
			ClearBackground(WHITE);
			if (bg1x <= -(screenwidth))
			{
				bg1x = bg1x * -1;
			}
			if (bg2x <= -(screenwidth))
			{
				bg2x = bg2x * -1;
			}
			if (GetKeyPressed() == KEY_ESCAPE)
				break;

			BeginDrawing();
			DrawTexture(bgImage, bg1x, 0, WHITE);
			DrawTexture(bgImage2, bg2x, 0, WHITE);
			right_click = IsKeyDown(KEY_RIGHT);
			left_click = IsKeyDown(KEY_LEFT);
			up_click = IsKeyPressed(KEY_UP);
			if (right_click && p1x != rightcondition)
			{
				p1x += 10;
				gun_direction = RIGHT;
			}
			if (left_click && p1x != leftcondition)
			{
				DrawTexture(player_left, p1x, temp_p1y, WHITE);
				pic = false;
				p1x -= 10;
				gun_direction = LEFT;
			}
			if (up_click && temp_p1y > 300)
			{
				temp_p1y -= 120;
				DrawTexture(player_jump, p1x, temp_p1y, WHITE);
				/*for (int i = 0; i < 15; i++)
				{
					p1y -= i;
				}*/
				pic = false;
				gun_direction = UP;

			}
			if (temp_p1y < p1y)
			{
				int flag = 5;

				temp_p1y += flag;
			}

			if (IsKeyDown(KEY_A))
			{
				switch (gun_direction)
				{
				case RIGHT:
					//DrawCircle(bullet.col/2, bullet.row, 10, RED);

					DrawTexture(player_shootR, p1x, temp_p1y, WHITE);
					DrawTexture(player_bulletR,temp_bulletRx, temp_p1y+20, WHITE);
					while (temp_bulletRx != screenheight)
					{
						temp_bulletRx += 7;
					}
					temp_bulletRx = bullet.row + 140;

					pic = false;
					break;
				case LEFT:
					DrawTexture(player_shootL, p1x, temp_p1y, WHITE);
					pic = false;
					break;
				case UP:
					DrawTexture(player_shootU, p1x, temp_p1y, WHITE);
					pic = false;
					break;

				}
			}
			if (pic)
				DrawTexture(player, p1x, temp_p1y, WHITE);

			bg1x -= 3;
			bg2x -= 3;

			EndDrawing();
		}
		if (IsKeyPressed(KEY_P)) {
			isPaused = true;
			int countdown = 5;

			while (isPaused && countdown >= 0)
			{
				BeginDrawing();
				ClearBackground(BLACK);
				DrawText(TextFormat("Time Remaining: %d", countdown), screenheight/2-150, screenwidth/2-150, 50, WHITE);
				EndDrawing();

				WaitTime(1.0);
				countdown--;

				if (countdown == 0)
				{
					isPaused = false;
					break;
				}
			}
		}
	}
	return 0;
}