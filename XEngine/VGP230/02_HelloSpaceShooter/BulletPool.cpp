#include "BulletPool.h"
#include "Bullet.h"

BulletPool::BulletPool()
	: Entity(), mNextAvailableIndex(0)
{
}

BulletPool::~BulletPool()
{
	XASSERT(mBulletsPool.empty(), "BulletPool: Unload must be called");
}

void BulletPool::Load()
{
	const int maxBullets = 50;
	for (int i = 0; i < maxBullets; ++i)
	{
		Bullet* newBullet = new Bullet();
		newBullet->Load();
		mBulletsPool.push_back(newBullet);
	}
}

void BulletPool::Update(float deltaTime)
{
	for (int i = 0; i < mBulletsPool.size(); i++)
	{
		mBulletsPool[i]->Update(deltaTime);
	}
}

void BulletPool::Render()
{
	for (int i = 0; i < mBulletsPool.size(); i++)
	{
		mBulletsPool[i]->Render();
	}
}

void BulletPool::Unload()
{
	for (int i = 0; i < mBulletsPool.size(); i++)
	{
		mBulletsPool[i]->Unload();
		delete mBulletsPool[i];
		mBulletsPool[i] = nullptr;
	}

	mBulletsPool.clear();
}

Bullet* BulletPool::GetBullet()
{
	Bullet* bullet = mBulletsPool[mNextAvailableIndex];
	mNextAvailableIndex = (mNextAvailableIndex + 1) % mBulletsPool.size();

	return bullet;
}

std::vector<Bullet*>& BulletPool::GetBulletsPool()
{
	return mBulletsPool;
}
