#pragma once
#include "Entity.h"
#include "Enum.h"

class Unit;
class Attacker;
class Defender;

class Zone : public Entity
{
public:
    Zone();
    ~Zone();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void UpdateHP(int value);
    void AddAttackerInRange(Attacker* attacker);
    void DefenderAttack(int value, X::Math::Vector2 position);
    Attacker* ReturnRandomAttackerInRange() const;

    void SpawnDefenders(int value);
    void SpawnAttacker();

    void SetActive(int castleHP);

    void SetAttackCastleCallback(std::function<void(int)> callback);

private:
    X::TextureId mImageID;
    X::Math::Vector2 mPosition;
    WallState mState;
    std::vector<Unit*> mAttackers;
    std::vector<Unit*> mDefenders;
    std::vector<Attacker*> mAttackersInRange;
    int mHealth;
    int mAttackerInSpawnQueue;
    float mAttackerSpawnTimer;

    static int mTotalZones;
    int mZoneID;

    std::function<void(int)> mAttackCastleCallback;
};