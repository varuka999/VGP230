#include <XEngine.h>

void GameInit()
{

}

bool GameUpdate(float deltaTime)
{
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