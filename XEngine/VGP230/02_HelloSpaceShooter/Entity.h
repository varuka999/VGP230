#pragma once
#include <XEngine.h>

class Entity
{
public:
	Entity() {};
	virtual ~Entity() {}; // Must have virtual deconstructor for abstract entity

	// Pure Abstract
	virtual void Load() = 0; // Replace = 0 with override {} in derived class
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Unload() = 0;
};