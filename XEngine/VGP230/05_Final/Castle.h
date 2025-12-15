#pragma once
#include "Entity.h"
#include "Enum.h"

class Zone;

class Castle : public Entity
{
public:
    ~Castle();
    static Castle* Get();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void UpdateHP(int value);
    UnitEnum GetPrimedAttackerType() const;

    void CastleUI();

private:
    Castle();
    static Castle* mInstance;

    std::vector<Zone*> mZones;
    int mHealth;
    int mTotalZones;
    char mPrimedAttackerKey;

    int mAttackerResource;
    float mAttackerResourceCooldown;
    float mAttackerResourceTimer;

};