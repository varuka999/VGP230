#pragma once
#include "Entity.h"
#include "Collidable.h"

class PowerUp : public Entity, public Collidable 
{
public:
	PowerUp();
	~PowerUp() override;

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void SetActive(const X::Math::Vector2& pos);
	void SetEntityType();
	bool IsActive() const;

	int GetType() const override;
	const X::Math::Vector2& GetPosition() const override;
	void OnCollision(Collidable* collidable) override;

private:
	X::TextureId mImageID;
	X::Math::Vector2 mPosition;
	EntityType mPowerUpType;
	bool mIsActive;
};