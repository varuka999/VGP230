#pragma once
#include "Entity.h"
#include "Collidable.h"

class BulletPool;
class AnimSpriteSheet;

class Ship : public Entity, public Collidable
{
public:
	Ship();
	~Ship() override;

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	int GetType() const override;
	const X::Math::Vector2& GetPosition() const override;
	void OnCollision(Collidable* collidable) override;

	void SetBulletPool(BulletPool* bulletPool);

	int GetHealth() const;
	int GetMaxHealth() const;
	int GetDamage() const;
	bool IsAlive() const;

private:
	X::TextureId mImageID;
	X::Math::Vector2 mPosition;
	float mRotation;
	float mScale;
	int mHealth;
	int mMaxHealth;
	int mDamage;
	bool mIsPowerUp;
	float mPowerUpTimer;

	AnimSpriteSheet* mExplosion;
	BulletPool* mBulletPool;
};