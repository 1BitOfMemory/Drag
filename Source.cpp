#include <iostream>
#include <conio.h>
#include "olcEngineConsole.h" 
using namespace std;

class Drag : public olcConsoleGameEngine //olcConsoldeGameEngine: This software is Copyright (C) 2018 Javidx9. See olcEngineConsole.h for details
{
public:
	Drag()
	{
		m_sAppName = L"Drag";
	}

private:
	int c = 0;
	bool isTouchingFloor = true;
	double gravity = 100.0f, xPos = 30, yPos = ScreenHeight() - 15;
	double acceleration = 0.0f;
	double velocity = 0.0f;
protected:
	virtual bool OnUserCreate()
	{
		return true;
	}

	virtual bool OnUserUpdate(float fElaspsedTime)
	{
		//Get A-W-D controls for movement

		//Left/Right movement
		if (GetKeyState('A') & 0x8000)
		{
			xPos -= 0.035;
		}
		if (GetKeyState('D') & 0x8000)
		{
			xPos += 0.035;
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
			DrawString(xPos, yPos + 45, L" ");
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
			DrawString(xPos, yPos + 46, L" |  ");
			DrawString(xPos, yPos + 47, L"/|\\ ");
			DrawString(xPos, yPos + 48, L" |  ");
			DrawString(xPos, yPos + 49, L"/ \\ ");
		}
		return true; //Keep game running
	}
};

int main()
{
	Drag instance;
	instance.ConstructConsole(70, 65, 19, 9);
	instance.Start();
	system("pause");
}