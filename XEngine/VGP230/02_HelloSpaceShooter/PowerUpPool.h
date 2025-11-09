#pragma once
#include "Entity.h"

class PowerUp; // Forward declare for the Pointer

class PowerUpPool : public Entity
{
public:
	PowerUpPool();
	~PowerUpPool() override;

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	PowerUp* GetPowerUp();
	std::vector<PowerUp*>& GetPowerUpPool();

private:
	int mNextAvailableIndex;
	std::vector<PowerUp*> mPowerUpPool;
};