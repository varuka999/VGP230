#pragma once
#include "Entity.h"
#include "Enum.h"

class Zone;

class Castle : public Entity
{
public:
    ~Castle();
    static Castle* Get();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void UpdateHP(int value);
    void SetBarValue(int current, int max);
    void UpdateAttackerResource(int value);
    UnitEnum GetPrimedAttackerType();
    bool HasEnoughResourceForAttacker(UnitEnum unitType) const;
    bool IsActive() const;

    void CastleUI();

private:
    Castle();
    static Castle* mInstance;

    std::vector<Zone*> mZones;
    X::TextureId mImageID;
    int mHealth;
    int mTotalZones;
    char mPrimedAttackerKey;

    int mAttackerResource;
    float mAttackerResourceCooldown;
    float mAttackerResourceTimer;

    // Progress Bar
    X::TextureId mBackgroundID;
    X::TextureId mBarID;
    X::Math::Rect mBarRect;
    X::Math::Vector2 mPosition;
    float mBarFullWidth;

    X::SoundId mBGMusic;
};