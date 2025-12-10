#pragma once
#include "Entity.h"
#include "functional"
#include "Enum.h"

class Unit : public Entity
{
public:
    Unit();
    virtual ~Unit();

    virtual void Load() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void Unload() override;

    virtual bool IsMoveAvailable() const;
    virtual void Move(float deltaTime);
    virtual void Attack();
    virtual void UpdateHealth(int value);
    virtual void SetAttackZoneWallCallback(std::function<void(int)> callback);

    virtual void SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination, std::string image, int health, int attack, float moveSpeed);
    virtual bool IsActive() const;

protected:
    X::TextureId mImageID;
    X::Math::Vector2 mPosition;
    X::Math::Vector2 mDestination;
    UnitState mState;
    int mHealth;
    int mAttack;
    int mMoveSpeed;
    float mAttackInterval;
    float mAttackTimer;

    std::function<void(int)> mAttackZoneWallCallback;
};