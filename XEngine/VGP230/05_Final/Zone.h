#pragma once
#include "Entity.h"
#include "Unit.h"

class ZoneLane;
class RangedDefender;

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

    ZoneLane* GetZone() const;

private:
    std::vector<RangedDefender*> mRangedDefenders;
    ZoneLane* mZoneLane;
};