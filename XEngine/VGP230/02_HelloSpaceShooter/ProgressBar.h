#pragma once
#include "Entity.h"

class ProgressBar : public Entity
{
public:
	ProgressBar();
	~ProgressBar();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void SetBarValue(int current, int max);

private:
	X::TextureId mBackgroundID;
	X::TextureId mBarID;
	X::Math::Rect mBarRect;
	X::Math::Vector2 mPosition;
	float mBarFullWidth;

};