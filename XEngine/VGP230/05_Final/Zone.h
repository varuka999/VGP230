#pragma once
#include "Entity.h"
#include "Unit.h"

class Attacker;

class Zone : public Entity
{
public:
    Zone();
    ~Zone();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void SpawnDefenders();
    void SpawnAttackers();

    void SetActive();

private:
    X::TextureId mImageID;
    X::Math::Vector2 mPosition;
    std::vector<Attacker*> mAttackers;
    std::vector<Unit*> mDefenders;
    //int mHealth; (FUTURE: Zone takes damage, then castle takes damage from the zone. If zone is 'destroyed', castle takes double damage from this zone)

    static int mTotalZones;
    int mZoneID;
};