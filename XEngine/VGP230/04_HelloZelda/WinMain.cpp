#include <XEngine.h>
#include "TileMap.h"

void GameInit()
{
    TileMap::Get()->Load();
}

void GameRender()
{
    TileMap::Get()->Render();
}

bool GameUpdate(float deltaTime)
{
    TileMap::Get()->Update(deltaTime);
    GameRender();

    return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{

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