#pragma once
#include "Entity.h";
#include "functional"

class Unit : public Entity
{
public:
    Unit();
    virtual ~Unit();

    virtual void Load() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void Unload() override;

    virtual void Action();
    virtual void Move();
    virtual void Attack();
    virtual void TakeDamage(int value);
    virtual void SetAttackCastleCallback(std::function<void(int)> callback);

    virtual void SetActive(const X::Math::Vector2 position, int health);
    virtual bool IsActive();

protected:
    X::TextureId mImageID;
    X::Math::Vector2 mPosition;
    int mHealth;
    int mAttack;
    int mMoveSpeed;
    float mAttackInterval;
    float mAttackTimer;

    std::function<void(int)> mAttackCastle;
};