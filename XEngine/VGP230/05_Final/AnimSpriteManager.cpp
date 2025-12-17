#include "AnimSpriteManager.h"

AnimSpriteManager* AnimSpriteManager::mInstance = nullptr;


AnimSpriteManager::AnimSpriteManager()
    : Entity()
{

}

AnimSpriteManager::~AnimSpriteManager()
{
}

AnimSpriteManager* AnimSpriteManager::Get()
{
    if (mInstance == nullptr)
    {
        mInstance = new AnimSpriteManager();
    }

    return mInstance;
}

void AnimSpriteManager::Load()
{

}
void AnimSpriteManager::Update(float deltaTime)
{

}
void AnimSpriteManager::Render()
{

}
void AnimSpriteManager::Unload()
{

}