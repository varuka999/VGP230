#pragma once
#include "Attacker.h"

class Infantry : public Attacker
{
public:
    void Load() override;
    void SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination) override;
};