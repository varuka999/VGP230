#pragma once
#include "Entity.h"
#include "Unit.h"

class Attacker : public Unit
{
public:
    Attacker();
    ~Attacker();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void Action() override;
    void IsMoveAvailable();
    void Move() override;
    void Attack() override;
    void TakeDamage(int value) override;

    void SetActive(const X::Math::Vector2 position, std::string image, int health);
    bool IsActive() override;

private:
    X::Math::Vector2 mDestination;
};