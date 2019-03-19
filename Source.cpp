#include <iostream>
#include <conio.h>
#include "olcEngineConsole.h" 
using namespace std;

class Drag : public olcConsoleGameEngine //olcConsoldeGameEngine: This software is Copyright (C) 2018 Javidx9. See olcEngineConsole.h for details
{
public:
	int winner; 

	Drag()
	{
		m_sAppName = L"Drag";
	}

private:
	bool bResetGame = true;
	
	//Player 1
	bool isTouchingFloor = true, shotFired = false, canFire = true;
	double gravity = 100.0f, xPos = 15, yPos = ScreenHeight()-15, bulletX = -2, currentX, currentY;
	double acceleration = 0.0f;
	double velocity = 0.0f;

	//Player 2
	bool isTouchingFloor2 = true, shotFired2 = false, canFire2 = true;
	double xPos2 = 60, yPos2 = ScreenHeight() - 15, bulletX2 = 2, currentX2, currentY2;
	double acceleration2 = 0.0f;
	double velocity2 = 0.0f;

protected:
	virtual bool OnUserCreate()
	{
		bResetGame = true;
		return true;
	}

	virtual bool OnUserUpdate(float fElaspsedTime)
	{
		if (bResetGame)
		{
			isTouchingFloor = true; 
			shotFired = false; 
			canFire = true;
			gravity = 100.0f;
			acceleration = 0.0f;
			velocity = 0.0f;
			xPos = 15; 
			yPos = ScreenHeight() - 50;
			bulletX = -2;

			isTouchingFloor2 = true; 
			shotFired2 = false;
			canFire2 = true;
			xPos2 = 60; 
			yPos2 = ScreenHeight() - 50;
			bulletX2 = 2;
			acceleration2 = 0.0f;
			velocity2 = 0.0f;
			
			currentX = xPos;
			currentY = yPos;
			currentX2 = xPos2;
			currentY2 = yPos2;

			bResetGame = false;
		}
		
		else
		{
			if ((((bulletX + currentX) > xPos2) && (bulletX + currentX) < (xPos2 + 5)) && (((currentY) > ((yPos2 - 2)) && (currentY < yPos2 + 3))))
			{
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t    Winner: Player 1";
				//DrawString(xPos, yPos, L"Winner: Player 1");
				// Do nothing until user releases space
				while (true) {
					if (GetAsyncKeyState(VK_SPACE) & 0x80000000)
					{
						bResetGame = true;
						break;
					}
				}
			}

			else if ((((bulletX2 + currentX2) < xPos + 2) && (bulletX2 + currentX2) > (xPos)) && (((currentY2) > ((yPos - 2)) && (currentY2 < yPos + 3))))
			{
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t    Winner: Player 2";
				
				// Do nothing until user releases space
				while (true) {
					if (GetAsyncKeyState(VK_SPACE) & 0x80000000)
					{
						bResetGame = true;
						break;
					}
				}
			}
			//Get A-W-D controls for movement
			//Left/Right movement
			else
			{
				if (GetKeyState('A') & 0x8000)
				{
					if (xPos > ScreenWidth() - 70)
					{
						xPos -= 0.03;
					}
				}
				if (GetKeyState('D') & 0x8000)
				{
					if (xPos < (ScreenWidth() / 2) - 5)
						xPos += 0.03;
				}

				if (yPos > ScreenHeight() - 15)
					yPos == ScreenHeight() - 15;

				if (GetKeyState('S') & 0x8000)
				{
					if (canFire == true)
					{
						shotFired = true;
						currentX = xPos;
						currentY = yPos;
					}
				}
				//If the player is on the floor, they can jump by pressing W. They cannot jump while jumping
				if ((GetKeyState('W') & 0x8000) && isTouchingFloor == true)
				{
					isTouchingFloor = false;
					acceleration = 0.0f;
					velocity = -gravity / 4.0f;
				}
				else if (yPos < 50)
					acceleration += gravity * fElaspsedTime;

				if (acceleration >= gravity)
					acceleration = gravity;

				velocity += acceleration * fElaspsedTime;
				yPos += velocity * fElaspsedTime;

				if (yPos + 50 > ScreenHeight())
				{
					acceleration = 0.0f;
					velocity = 0.0f;
					isTouchingFloor = true;
				}

				//Clear screen
				Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

				//Draw jumper; if they player is jumping, the arms are up
				if (isTouchingFloor == false)
				{
					DrawString(xPos, yPos + 43, L" _");
					DrawString(xPos, yPos + 44, L"(_) ");
					DrawString(xPos, yPos + 45, L"   O");
					if (shotFired == true)
					{
						canFire = false;
						Draw(currentX + bulletX, currentY + 45, PIXEL_SOLID, 0x0002);
						bulletX += 0.08;
						if (currentX + bulletX > ScreenWidth() - 5)
						{
							bulletX = 2;
							shotFired = false;
							canFire = true;
						}
					}

					DrawString(xPos, yPos + 46, L"\\|/  ");
					DrawString(xPos, yPos + 47, L" | ");
					DrawString(xPos, yPos + 48, L" |  ");
					DrawString(xPos, yPos + 49, L"/ \\ ");
				}
				else
				{
					DrawString(xPos, yPos + 43, L" _");
					DrawString(xPos, yPos + 44, L"(_) ");
					DrawString(xPos, yPos + 45, L" ");
					DrawString(xPos, yPos + 46, L" |_O  ");
					if (shotFired == true)
					{
						canFire = false;
						Draw(currentX + bulletX, currentY + 45, PIXEL_SOLID, 0x0002);
						bulletX += 0.08;
						if (currentX + bulletX > ScreenWidth() - 5)
						{
							bulletX = 2;
							shotFired = false;
							canFire = true;
						}
					}
					DrawString(xPos, yPos + 47, L"/| ");
					DrawString(xPos, yPos + 48, L" |  ");
					DrawString(xPos, yPos + 49, L"/ \\ ");
				}

				//END PLAYER 1

				//Get I-J-L controls for movement

			//Left/Right movement
				if (GetKeyState('J') & 0x8000)
				{
					if (xPos2 > (ScreenWidth() / 2) + 5)
					{
						xPos2 -= 0.03;
					}
				}
				if (GetKeyState('L') & 0x8000)
				{
					if (xPos2 < ScreenWidth() - 5)
						xPos2 += 0.03;
				}

				if (yPos2 > ScreenHeight() - 15)
					yPos2 == ScreenHeight() - 15;

				if (GetKeyState('K') & 0x8000)
				{
					if (canFire2 == true)
					{
						shotFired2 = true;
						currentX2 = xPos2;
						currentY2 = yPos2;
					}
				}
				//If the player is on the floor, they can jump by pressing W. They cannot jump while jumping
				if ((GetKeyState('I') & 0x8000) && isTouchingFloor2 == true)
				{
					isTouchingFloor2 = false;
					acceleration2 = 0.0f;
					velocity2 = -gravity / 4.0f;
				}
				else if (yPos2 < 50)
					acceleration2 += gravity * fElaspsedTime;

				if (acceleration2 >= gravity)
					acceleration2 = gravity;

				velocity2 += acceleration2 * fElaspsedTime;
				yPos2 += velocity2 * fElaspsedTime;

				if (yPos2 + 50 > ScreenHeight())
				{
					acceleration2 = 0.0f;
					velocity2 = 0.0f;
					isTouchingFloor2 = true;
				}


				if (isTouchingFloor2 == false)
				{
					DrawString(xPos2, yPos2 + 43, L"  _");
					DrawString(xPos2, yPos2 + 44, L" (_) ");
					DrawString(xPos2, yPos2 + 45, L"O");
					if (shotFired2 == true)
					{
						canFire2 = false;
						Draw(currentX2 + bulletX2, currentY2 + 45, PIXEL_SOLID, 0x0002);
						bulletX2 -= 0.08;
						if (currentX2 + bulletX2 < ScreenWidth() - 71)
						{
							bulletX2 = -2;
							shotFired2 = false;
							canFire2 = true;
						}
					}

					DrawString(xPos2, yPos2 + 46, L" \\|/  ");
					DrawString(xPos2, yPos2 + 47, L"  | ");
					DrawString(xPos2, yPos2 + 48, L"  |  ");
					DrawString(xPos2, yPos2 + 49, L" / \\ ");
				}
				else
				{
					DrawString(xPos2, yPos2 + 43, L"  _");
					DrawString(xPos2, yPos2 + 44, L" (_) ");
					DrawString(xPos2, yPos2 + 45, L"  ");
					DrawString(xPos2, yPos2 + 46, L"O-| ");
					if (shotFired2 == true)
					{
						canFire2 = false;
						Draw(currentX2 + bulletX2, currentY2 + 45, PIXEL_SOLID, 0x0002);
						bulletX2 -= 0.08;
						if (currentX2 + bulletX2 < ScreenWidth() - 71)
						{
							bulletX2 = -2;
							shotFired2 = false;
							canFire2 = true;
						}
					}
					DrawString(xPos2, yPos2 + 47, L"  |\\ ");
					DrawString(xPos2, yPos2 + 48, L"  |  ");
					DrawString(xPos2, yPos2 + 49, L" / \\ ");
				}
			}
		}
			return true; //Keep game running
	}
};

int main()
{
	Drag instance;
	instance.ConstructConsole(71, 75, 19, 9);
	instance.Start();
	cin.get();
	return 0;
}
