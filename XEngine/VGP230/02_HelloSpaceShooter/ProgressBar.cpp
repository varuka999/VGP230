#include "ProgressBar.h"

ProgressBar::ProgressBar()
	: mBackgroundID(0), mBarID(0), mBarRect(), mPosition(0.0f), mBarFullWidth(0.0f)
{

}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::Load()
{
	mBackgroundID = X::LoadTexture("bar_empty.png");
	mBarID = X::LoadTexture("bar_red.png");
	mBarRect.right = X::GetSpriteWidth(mBarID);
	mBarRect.bottom = X::GetSpriteHeight(mBarID);
	mBarFullWidth = mBarRect.right;
	mPosition.x = (X::GetScreenWidth() - mBarFullWidth) * 0.5f;
	mPosition.y = 20.0f;
}

void ProgressBar::Update(float deltaTime)
{

}

void ProgressBar::Render()
{
	X::DrawSprite(mBackgroundID, mPosition, X::Pivot::Left);
	X::DrawSprite(mBarID, mBarRect, mPosition, 1.0f, X::Pivot::Left);
}

void ProgressBar::Unload()
{
}

void ProgressBar::SetBarValue(int current, int max)
{
	mBarRect.right = X::Math::Clamp((float)current / (float)max, 0.0f, 1.0f) * mBarFullWidth;
}
