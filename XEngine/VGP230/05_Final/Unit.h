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

    virtual void SetDestination(const X::Math::Vector2 destination);
    virtual void SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination);
    virtual bool IsActive() const;

    virtual float GetMoveSpeed() const;
    virtual X::Math::Vector2 GetPosition() const;
    virtual X::Math::Vector2 GetDestination() const;

protected:
    X::TextureId mImageID;
    X::Math::Vector2 mPosition;
    X::Math::Vector2 mDestination;
    int mHealth;
    int mAttack;
    int mMoveSpeed;
    float mAttackInterval;
    float mAttackTimer;

    std::function<void(int)> mAttackZoneWallCallback;
};