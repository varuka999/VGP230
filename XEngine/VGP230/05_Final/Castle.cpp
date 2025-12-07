#include "Castle.h"
#include "Zone.h"

Castle* Castle::mInstance = nullptr;

Castle::Castle()
	: Entity(), mHealth(0)
{
	
}

Castle::~Castle()
{
}

Castle* Castle::Get()
{
	if (mInstance == nullptr)
	{
		mInstance = new Castle();
	}

	return mInstance;
}

void Castle::Load()
{
	mHealth = 1000;

	Zone* newZone = new Zone();
	newZone->Load();
	mZones.push_back(newZone);
}

void Castle::Update(float deltaTime)
{
	for (Zone* zone : mZones)
	{
		zone->Update(deltaTime);
	}
}

void Castle::Render()
{
}

void Castle::Unload()
{
}

void Castle::UpdateHP(int value)
{
	mHealth += value;
}
