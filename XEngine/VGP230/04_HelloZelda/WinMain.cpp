#include <XEngine.h>
#include "GameController.h"
#include "EnemyManager.h"

void GameInit()
{
    GameController::Get()->Load();
}

bool GameUpdate(float deltaTime)
{
    GameController::Get()->Update(deltaTime);
    GameController::Get()->Render();

    if (EnemyManager::Get()->IsGameOver())
    {
        return true;
    }

    return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
    GameController::Get()->Unload();
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