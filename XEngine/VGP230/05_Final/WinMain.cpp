#include <XEngine.h>
#include "Castle.h"

void GameInit()
{
    Castle::Get()->Load();
}

bool GameUpdate(float deltaTime)
{
    Castle::Get()->Update(deltaTime);

    return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
    Castle::Get()->Unload();
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    X::Start("xconfig.json");
    GameInit();

    X::Run(GameUpdate);

    GameCleanup();
    X::Stop();

    return 0;
}