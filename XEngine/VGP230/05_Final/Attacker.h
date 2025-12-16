#pragma once
#include "Entity.h"
#include "Unit.h"

class Attacker : public Unit
{
public:
    Attacker();
    ~Attacker();

    void Update(float deltaTime) override;
    void Load() override;
    void Unload() override;
    virtual void SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination) override;
    virtual void Attack() override;

    void UpdateHealth(int value) override;
    float ReturnDistanceToDestination() const;
    void SetInRangeCallBack(std::function<void(Attacker*)> callback);
    void SetOutOfRangeCallBack(std::function<void(Attacker*)> callback);

protected:
    std::function<void(Attacker*)> mAttackRangeCallback;
    std::function<void(Attacker*)> mOutOfRangeCallback;
    bool mInAttackRange;
};