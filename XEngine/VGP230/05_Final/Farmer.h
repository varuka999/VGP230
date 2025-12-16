#pragma once
#include "Attacker.h"

class Farmer : public Attacker
{
public:
    void Load() override;
    void Update(float deltaTime) override;

    void SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination) override;
    void SetResourceCallback(std::function<void(int)> callback);

private:
    std::function<void(int)> mResourceCallback;
    float mGatherTimer = 0.0f;
};