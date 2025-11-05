#include "AnimSpriteArray.h"

AnimSpriteArray::AnimSpriteArray()
	: Entity(), mPosition(0.0f, 0.0f), mFrameRate(0.0f), mCurrentFrameTime(0.0f), mCurrentIndex(0), mIsLooping(false)
{

}

AnimSpriteArray::~AnimSpriteArray()
{
}

void AnimSpriteArray::AnimSpriteArray::Load()
{
	mFrameRate = 1.0f / 30.0f;
	mIsLooping = false;
	mCurrentIndex = -1;
}

void AnimSpriteArray::Update(float deltaTime)
{
	if (IsActive() == true && mFrameRate > 0.0f)
	{
		mCurrentFrameTime += deltaTime;

		while (mCurrentFrameTime > mFrameRate)
		{
			mCurrentFrameTime -= mFrameRate;
			++mCurrentIndex;
		}

		int frameCount = GetFrameCount();

		if (mCurrentIndex >= frameCount)
		{
			if (mIsLooping == true)
			{
				while (mCurrentIndex >= frameCount)
				{
					mCurrentIndex -= frameCount;
				}
			}
			else
			{
				mCurrentIndex = -1;
			}
		}
	}
}

void AnimSpriteArray::Render()
{
	if (IsActive() == true)
	{
		X::DrawSprite(mSpriteIDs[mCurrentIndex], mPosition);
	}
}

void AnimSpriteArray::Unload()
{
}

void AnimSpriteArray::LoadSprites(const std::vector<std::string>& sprites)
{
	mSpriteIDs.clear();

	for (const std::string& sprite : sprites)
	{
		mSpriteIDs.push_back(X::LoadTexture(sprite.c_str()));
	}
}

void AnimSpriteArray::SetActive(bool looping)
{
	mIsLooping = looping;
	mCurrentIndex = 0;
	mCurrentFrameTime = 0.0f;
}

void AnimSpriteArray::SetFrameRate(float frameRate)
{
	mFrameRate = frameRate;
}

void AnimSpriteArray::SetPosition(const X::Math::Vector2& position)
{
	mPosition = position;
}
bool AnimSpriteArray::IsActive() const
{
	return mIsLooping == true || mCurrentIndex >= 0;
}

void AnimSpriteArray::SetFrameIndex(int index)
{
	if (index >= 0 && index < mSpriteIDs.size())
	{
		mCurrentIndex = index;
	}
}

int AnimSpriteArray::GetFrameCount() const
{
	return mSpriteIDs.size();
}
