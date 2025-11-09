#pragma once
#include "Entity.h"
#include "Collidable.h"

class BulletPool;
class PowerUpPool;
class Ship;
class AnimSpriteSheet;
class AnimSpriteArray;
class PowerUp;

class Enemy : public Entity, public Collidable
{
public:
	Enemy();
	~Enemy() override;

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	int GetType() const override;
	const X::Math::Vector2& GetPosition() const override;
	void OnCollision(Collidable* collidable) override;

	void SetBulletPool(BulletPool* bulletPool);
	void SetPowerUpPool(PowerUpPool* powerUpPool);
	void SetShip(Ship* ship);
	void SetPosition(const X::Math::Vector2& position);
	void SetRotation(float rotation);

	int GetEnemiesDefeated();

	bool IsAlive() const;

private:
	BulletPool* mBulletPool;
	PowerUpPool* mPowerUpPool;
	Ship* mShip;
	AnimSpriteSheet* mExplosion;
	AnimSpriteArray* mImage;
	PowerUp* mPowerUp;

	//X::TextureId mImageID;
	static int mEnemiesDefeated;

	X::Math::Vector2 mPosition;
	float mRotation;
	float mDistanceFromTarget;

	int mHealth;

	X::Math::Vector2 mCenterPoint;
	X::Math::Vector2 mTargetPosition;
	float mTargetPositionUpdate;
	float mFireRate;
};