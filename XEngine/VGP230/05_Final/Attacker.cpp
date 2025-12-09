#include "Attacker.h"

Attacker::Attacker()
    : Unit()
{
}

Attacker::~Attacker()
{
}

void Attacker::Load()
{
    mImageID = X::LoadTexture("scv_09.png");
}

//void Attacker::Update(float deltaTime)
//{
//
//}

//void Attacker::Render()
//{
//
//}

void Attacker::Unload()
{

}

//void Attacker::Move(float deltaTime)
//{
//
//}

void Attacker::Attack()
{
    mAttackCastle(-1);
}

//void Attacker::UpdateHealth(int value)
//{
//
//}

//void Attacker::SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination, std::string image, int health, int attack, float moveSpeed)
//{
//
//}

//bool Attacker::IsActive() const
//{
//    
//}
