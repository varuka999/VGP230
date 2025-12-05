#pragma once
#include "Entity.h";

class Unit : public Entity
{
public:
    Unit();
    virtual ~Unit();

    virtual void Load() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void Unload() override;

    virtual void TakeDamage(int value);
    virtual bool IsActive();

protected:
    X::TextureId mImageID;
    X::Math::Vector2 mPosition;
    int mHealth;
    int mAttack;
    int mMoveSpeed;
    float mAttackInterval;
    float mAttackTimer;
};