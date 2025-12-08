#pragma once
#include "Entity.h"

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

private:
    Castle();
    static Castle* mInstance;

    std::vector<Zone*> mZones;
    int mHealth;
    int mTotalZones;
};
