#pragma once
#include "Entity.h"
#include "Unit.h"

class Zone;

class RangedDefender : public Entity, public Unit
{
public:
    RangedDefender();
    ~RangedDefender();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void TakeDamage(int value) override;
    bool IsActive() override;

private:
    Zone* mZone;
};