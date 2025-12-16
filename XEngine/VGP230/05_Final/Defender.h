#pragma once
#include "Entity.h"
#include "Unit.h"

class Defender : public Unit
{
public:
    Defender();
    ~Defender();

    void Load() override;
    void Unload() override;
    void Attack() override;

    void SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination) override;
    void SetAttackCallback(std::function<void(int, X::Math::Vector2)> callback);

private:
    std::function<void(int, X::Math::Vector2)> mAttackCallback;
};