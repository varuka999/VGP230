#pragma once
#include "Attacker.h"
#include "Enum.h"

class Archer : public Attacker
{
public:
    Archer();

    void Load() override;
    void Update(float deltaTime) override;

    bool IsMoveAvailable() const override;

    void Attack() override;
    void SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination) override;

private:
    UnitState mState;
    float mAttackWindupInterval;
    float mAttackWindupTimer;
};