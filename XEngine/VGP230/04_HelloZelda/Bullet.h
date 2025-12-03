#pragma once
#include "Entity.h"
#include "Collidable.h"

class Bullet : public Entity, public Collidable
{
public:
	Bullet();
	~Bullet() override;

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void SetActive(const X::Math::Vector2& pos, float rotation, float lifeTime = 0.5f);
	void SetEntityType(EntityType entityType);
	bool IsActive() const;

	int GetType() const override;
	const X::Math::Vector2& GetPosition() const override;
	void OnCollision(Collidable* collidable) override;

private:
	X::TextureId mImageID;
	X::Math::Vector2 mPosition;
	X::Math::Rect mBulletRect;
	float mRotation;
	float mLifeTime;
	EntityType mBulletType;
	bool mRemoveCollider;
};