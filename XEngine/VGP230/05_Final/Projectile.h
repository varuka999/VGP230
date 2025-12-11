#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
    Projectile();
    ~Projectile() override;

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void SetActive(const X::Math::Vector2& pos, float rotation, float lifeTime = 0.5f);
    bool IsActive() const;
};