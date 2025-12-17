#pragma once
#include "Entity.h"
#include "AnimSpriteSheet.h"

class Projectile : public Entity
{
public:
    Projectile();
    ~Projectile() override;

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void SetHitCallback(std::function<void(int)> callback);
    void SetActive(std::string imageID, const X::Math::Vector2 & position, const X::Math::Vector2 destination, float rotation, float speed, int damage);
    bool IsActive() const;

private:
    X::TextureId mImageID;
    X::Math::Vector2 mPosition;
    X::Math::Vector2 mDestination;
    float mRotation;
    float mMoveSpeed;
    int mDamage;
    bool mActiveTarget;
    AnimSpriteSheet* mHitEffect;

    std::function<void(int)> mHitCallback;

};