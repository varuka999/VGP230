#include <XEngine.h>
#include "Castle.h"
#include "UnitPool.h"
#include "ProjectilePool.h"

float gGameTimer = 0.0f;
float gGameDuration = 300.0f;

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

    Castle::Get()->Render();
    UnitPool::Get()->Render();
    ProjectilePool::Get()->Render();

    if (gGameTimer <= gGameDuration)
    {
        gGameTimer += deltaTime;

        std::string text = "Time Remaining: " + std::string(std::to_string((int)(gGameDuration - gGameTimer))) + "s";
        const float textSize = 30.0f;
        float screenX = 10.0f;
        float screenY = 10.0f;
        X::DrawScreenText(text.c_str(), screenX, screenY, textSize, X::Colors::Purple);
    }
    else
    {
        return true; // Lose the game after X minutes
    }

    if (!Castle::Get()->IsActive())
    {
        return true; // Win the game if castle is destroyed
    }

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
