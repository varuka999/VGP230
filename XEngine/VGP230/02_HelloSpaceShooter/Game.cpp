#include "Game.h"
#include "Ship.h"
#include "BulletPool.h"
#include "Bullet.h"

Game::Game()
    : Entity(), mPlayer(nullptr), mBulletPool(nullptr)
{

}

Game::~Game()
{
    XASSERT(mPlayer == nullptr, "Game: Unload was not called");
}

void Game::Load()
{
    mPlayer == new Ship();
    mBulletPool = new BulletPool();

    mPlayer->Load();
    mPlayer->SetBulletPool(mBulletPool);
    AddCollidable(mPlayer);

    mBulletPool->Load();
    std::vector<Bullet*>& bullets = mBulletPool->GetBulletsPool();
    for (Bullet* bullet : bullets)
    {
        AddCollidable(bullet);
    }
}

void Game::Update(float deltaTime)
{
    mPlayer->Update(deltaTime);

    mBulletPool->Update(deltaTime);

    int numCollidables = mCollidables.size();
    for (int i = 0; i < numCollidables; ++i)
    {
        for (int n = i + 1; n < numCollidables; n++)
        {
            if (mCollidables[i]->DidCollide(mCollidables[n]))
            {
                mCollidables[i]->OnCollision(mCollidables[n]);
                mCollidables[n]->OnCollision(mCollidables[i]);
            }
        }
    }
}

void Game::Render()
{
    mPlayer->Render();
    mBulletPool->Render();
}

void Game::Unload()
{
    mBulletPool->Unload();
    delete mBulletPool;
    mBulletPool = nullptr;
    mPlayer->Unload();
    delete mPlayer;
    mPlayer == nullptr;
}

void Game::AddCollidable(Collidable* collidable)
{
    mCollidables.push_back(collidable);
}

bool Game::IsGameOver()
{
    return false;
}
