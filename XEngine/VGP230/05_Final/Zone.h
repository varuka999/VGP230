#pragma once
#include "Entity.h"
#include "Unit.h"

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

private:
    std::vector<Unit*> mAttackers;
    std::vector<Unit*> mDefenders;
};