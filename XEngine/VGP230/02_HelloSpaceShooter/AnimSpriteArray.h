#pragma once
#include "Entity.h"

class AnimSpriteArray : public Entity
{
public:
	AnimSpriteArray();
	~AnimSpriteArray() override;

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void LoadSprites(const std::vector<std::string>& sprites);
	void SetActive(bool looping = false);
	void SetFrameRate(float frameRate);
	void SetPosition(const X::Math::Vector2& position);
	bool IsActive() const;

	void SetFrameIndex(int index);
	int GetFrameCount() const;

private:
	std::vector<X::TextureId> mSpriteIDs;
	X::Math::Vector2 mPosition;
	float mFrameRate;
	float mCurrentFrameTime;
	int mCurrentIndex;
	bool mIsLooping;
};