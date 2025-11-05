#include <XEngine.h>
#include "StartState.h"
#include "RunGameState.h"
#include "EndState.h"
//#include "Ship.h"

//Ship mShip;

State gActiveState = State::Start;
GameState* gCurrentState = nullptr;
std::map<State, GameState*> gGameStates;
void GameInit()
{
	//mShip.Load();

	gGameStates[State::Start] = new StartState();
	gGameStates[State::RunGame] = new RunGameState();
	gGameStates[State::End] = new EndState();
	gActiveState = State::Start; // <---------------------------------------------

	//gGameStates[gActiveState]->Update()
	gCurrentState = gGameStates[gActiveState];
	gCurrentState->Load();
}

bool GameLoop(float deltaTime)
{
	//mShip.Update(deltaTime);
	//mShip.Render();

	State newState = gGameStates[gActiveState]->Update(deltaTime);
	gCurrentState->Render();
	if (newState != gActiveState)
	{
		gCurrentState->Unload();
		gCurrentState = gGameStates[newState];
		gCurrentState->Load();
		gActiveState = newState;
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	//mShip.Unload();

	gCurrentState->Unload();

	for (auto& state : gGameStates)
	{
		delete state.second;
	}

	gGameStates.clear();
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