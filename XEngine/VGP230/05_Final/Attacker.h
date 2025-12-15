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
    virtual void Attack() override;

    void UpdateHealth(int value) override;
    float ReturnDistanceToDestination() const;
    void SetInRangeCallBack(std::function<void(Attacker*)> callback);
    void SetOutOfRangeCallBack(std::function<void(Attacker*)> callback);

private:
    std::function<void(Attacker*)> mAttackRangeCallback;
    std::function<void(Attacker*)> mOutOfRangeCallback;
    bool mInAttackRange;
};