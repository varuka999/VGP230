#include <XEngine.h>
#include "Ship.h"

Ship mShip;

void GameInit()
{
	mShip.Load();
}

bool GameLoop(float deltaTime)
{
	mShip.Update(deltaTime);
	mShip.Render();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	mShip.Unload();
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();

	return 0;
}