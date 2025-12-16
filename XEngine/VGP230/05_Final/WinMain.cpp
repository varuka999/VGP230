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
    ProjectilePool::Get()->Update(deltaTime);
    UnitPool::Get()->Update(deltaTime);
    Castle::Get()->Update(deltaTime);

    ProjectilePool::Get()->Render();
    UnitPool::Get()->Render();
    Castle::Get()->Render();

    return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
    Castle::Get()->Unload();
    UnitPool::Get()->Unload();
    ProjectilePool::Get()->Unload();
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