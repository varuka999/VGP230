#include "Game.h"
#include "Ship.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "Enemy.h"

Game::Game()
    : Entity(), mPlayer(nullptr), mBulletPool(nullptr), mEnemy(nullptr)
{

}

Game::~Game()
{
    XASSERT(mPlayer == nullptr, "Game: Unload was not called");
}

void Game::Load()
{
    mPlayer = new Ship();
    mBulletPool = new BulletPool();

    mPlayer->Load();
    mPlayer->SetBulletPool(mBulletPool);
    AddCollidable(mPlayer);

    mEnemy = new Enemy();
    mEnemy->Load();
    mEnemy->SetBulletPool(mBulletPool);
    mEnemy->SetShip(mPlayer);
    mEnemy->SetPosition({100.0f, 100.0f});
    AddCollidable(mEnemy);

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
    mEnemy->Update(deltaTime);

    mBulletPool->Update(deltaTime);

    int numCollidables = mCollidables.size();
    for (int i = 0; i < numCollidables; ++i)
    {
        for (int n = i + 1; n < numCollidables; ++n)
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
    mEnemy->Render();
    mBulletPool->Render();
    mPlayer->Render();
}

void Game::Unload()
{
    mBulletPool->Unload();
    delete mBulletPool;
    mBulletPool = nullptr;

    mPlayer->Unload();
    delete mPlayer;
    mPlayer = nullptr;

    mEnemy->Unload();
    delete mEnemy;
    mEnemy = nullptr;
}

void Game::AddCollidable(Collidable* collidable)
{
    mCollidables.push_back(collidable);
}

bool Game::IsGameOver()
{
    return false;
}
