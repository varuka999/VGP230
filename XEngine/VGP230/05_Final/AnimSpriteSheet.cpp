#include "AnimSpriteSheet.h"

AnimSpriteSheet::AnimSpriteSheet()
	: Entity(), mSpriteSheetID(0), mSpriteRect(), mPosition(0.0f, 0.0f), mFrameRate(0.0f), mCurrentFrameTime(0.0f), mRows(0), mColumns(0), mMaxFrames(0), mCurrentIndex(0), mIsLooping(false)
{
}

AnimSpriteSheet::~AnimSpriteSheet()
{
}

void AnimSpriteSheet::Load()
{
	mSpriteSheetID = X::LoadTexture("explosion_anim.png");
	mSpriteRect.right = 10.0f;
	mSpriteRect.bottom = 10.0f;
	mMaxFrames = 81;
	mRows = 9;
	mColumns = 9;
	mFrameRate = 1.0f / 60.0f;
	mIsLooping = false;
	mCurrentIndex = -1;
}

void AnimSpriteSheet::Update(float deltaTime)
{
	if (IsActive() == true)
	{
		mCurrentFrameTime += deltaTime;

		while (mCurrentFrameTime > mFrameRate)
		{
			mCurrentFrameTime -= mFrameRate;
			++mCurrentIndex;
		}

		if (mCurrentIndex >= mMaxFrames)
		{
			if (mIsLooping == true)
			{
				mCurrentIndex -= mMaxFrames;
			}
			else
			{
				mCurrentIndex = -1;
			}
		}

		const float rectWidth = 100.0f;
		const float rectHeight = 100.0f;
		mSpriteRect.left = (mCurrentIndex % mColumns) * rectWidth;
		mSpriteRect.top = (mCurrentIndex / mColumns) * rectHeight;
		mSpriteRect.right = mSpriteRect.left + rectWidth;
		mSpriteRect.bottom = mSpriteRect.top + rectHeight;
	}
}

void AnimSpriteSheet::Render()
{
	if (IsActive() == true)
	{
		X::DrawSprite(mSpriteSheetID, mSpriteRect, mPosition, 0.3f);
	}
}

void AnimSpriteSheet::Unload()
{
}

void AnimSpriteSheet::SetActive(const X::Math::Vector2& position, bool loop)
{
	mPosition = position;
	mIsLooping = loop;
	mCurrentIndex = 0;
	mCurrentFrameTime = 0.0f;
}

bool AnimSpriteSheet::IsActive() const
{
	return mIsLooping || mCurrentIndex >= 0;
}
