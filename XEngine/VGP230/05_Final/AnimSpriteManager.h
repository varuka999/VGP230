#pragma once
#include "Entity.h"

class AnimSpriteManager : Entity
{
public:
    ~AnimSpriteManager();
    static AnimSpriteManager* Get();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

private:
    AnimSpriteManager();
    static AnimSpriteManager* mInstance;
};