#include <XEngine.h>
#include "Castle.h"
#include "UnitPool.h"
#include "ProjectilePool.h"

void GameInit()
{
    ProjectilePool::Get()->Load();
    UnitPool::Get()->Load();
    Castle::Get()->Load();
}

bool GameUpdate(float deltaTime)
{
    Castle::Get()->Update(deltaTime);
    Castle::Get()->Render();

    return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
    Castle::Get()->Unload();
    UnitPool::Get()->Unload();
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