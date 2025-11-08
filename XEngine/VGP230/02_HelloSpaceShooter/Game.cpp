#include "Game.h"
#include "Ship.h"
#include "BulletPool.h"
#include "PowerUpPool.h"
#include "Bullet.h"
#include "PowerUp.h"
#include "Enemy.h"
#include "ProgressBar.h"

Game::Game()
	: Entity(), mPlayer(nullptr), mBulletPool(nullptr), mPowerUpPool(nullptr), mHealthBar(nullptr), mWaveEnemies(1), mWaveCounter(0)
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
	mPowerUpPool = new PowerUpPool();
	mHealthBar = new ProgressBar();

	mPlayer->Load();
	mPlayer->SetBulletPool(mBulletPool);
	AddCollidable(mPlayer);

	mHealthBar->Load();

	SpawnNextWave();

	mBulletPool->Load();
	std::vector<Bullet*>& bullets = mBulletPool->GetBulletsPool();
	for (Bullet* bullet : bullets)
	{
		AddCollidable(bullet);
	}

	mPowerUpPool->Load();
	std::vector<PowerUp*>& powerUps = mPowerUpPool->GetPowerUpPool();
	for (PowerUp* powerUp : powerUps)
	{
		AddCollidable(powerUp);
	}
}

void Game::Update(float deltaTime)
{
	mPlayer->Update(deltaTime);
	for (Enemy* enemy : mEnemies)
	{
		enemy->Update(deltaTime);
	}

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

	//If all enemies are dead
	if (AreAllEnemiesDead() == true)
	{
		SpawnNextWave();
	}

	mHealthBar->SetBarValue(mPlayer->GetHealth(), mPlayer->GetMaxHealth());
}

bool Game::AreAllEnemiesDead()
{
	for (Enemy* enemy : mEnemies)
	{
		if (enemy->IsAlive() == true)
		{
			return false;
		}
	}

	return true;
}

void Game::Render()
{
	for (Enemy* enemy : mEnemies)
	{
		enemy->Render();
	}
	mBulletPool->Render();
	mPlayer->Render();
	mHealthBar->Render();
}

void Game::Unload()
{
	mBulletPool->Unload();
	delete mBulletPool;
	mBulletPool = nullptr;

	mPowerUpPool->Unload();
	delete mPowerUpPool;
	mPowerUpPool = nullptr;

	mHealthBar->Unload();
	delete mHealthBar;
	mHealthBar = nullptr;

	mPlayer->Unload();
	delete mPlayer;
	mPlayer = nullptr;

	for (Enemy* enemy : mEnemies)
	{
		enemy->Unload();
		delete enemy;
		enemy = nullptr;
	}

	mEnemies.clear();
}

void Game::AddCollidable(Collidable* collidable)
{
	mCollidables.push_back(collidable);
}

void Game::SpawnNextWave()
{
	mWaveEnemies += 2;

	X::Math::Vector2 spawnPosition = X::Math::Vector2::Zero();
	X::Math::Vector2 spawnDirection = X::Math::Vector2::Zero();
	X::Math::Vector2 center = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
	const float minOffset = 100.0f;
	const float maxOffset = center.y;

	for (int i = 0; i < mWaveEnemies; ++i)
	{
		spawnDirection = X::RandomUnitCircle();
		spawnPosition = center + (spawnDirection * X::RandomFloat(minOffset, maxOffset));

		Enemy* newEnemy = new Enemy();
		newEnemy = new Enemy();
		newEnemy->Load();
		newEnemy->SetBulletPool(mBulletPool);
		newEnemy->SetPowerUpPool(mPowerUpPool);
		newEnemy->SetShip(mPlayer);
		newEnemy->SetPosition(spawnPosition);
		newEnemy->SetRotation(X::RandomFloat() * X::Math::kTwoPi);
		AddCollidable(newEnemy);
		mEnemies.push_back(newEnemy);
	}

	++mWaveCounter;
}

bool Game::IsGameOver()
{
	return mPlayer->IsAlive() == false || mWaveCounter >= 4;
}
