#pragma once
#include "Entity.h"
#include <vector>

class Ship;
class BulletPool;
class PowerUpPool;
class Collidable;
class Enemy;
class ProgressBar;

class Game : public Entity
{
public:
	Game();
	~Game() override;

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void AddCollidable(Collidable* collidable);
	
	bool IsGameOver();

private:
	Ship* mPlayer;
	BulletPool* mBulletPool;
	PowerUpPool* mPowerUpPool;
	std::vector<Collidable*> mCollidables;

	//Enemy* mEnemy;
	std::vector<Enemy*> mEnemies;
	ProgressBar* mHealthBar;
};
