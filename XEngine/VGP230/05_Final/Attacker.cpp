#include "Attacker.h"

Attacker::Attacker()
    : Unit(),
    mDestination(0.0f, 0.0f)
{
}

Attacker::~Attacker()
{
}

void Attacker::Load()
{
    mImageID = X::LoadTexture("scv_09.png");
}

void Attacker::Update(float deltaTime)
{
}

void Attacker::Render()
{
    if (IsActive())
    {
        X::DrawSprite(mImageID, mPosition);
    }
}

void Attacker::Unload()
{
}

void Attacker::Action()
{
    // If Move Available
    // Move();
    // Else
    // Attack
}

void Attacker::IsMoveAvailable()
{

}

void Attacker::Move()
{
}

void Attacker::Attack()
{
    mAttackCastle(-1);
}

void Attacker::TakeDamage(int value)
{
}

void Attacker::SetActive(const X::Math::Vector2 position, std::string image, int health)
{
    mPosition = position;
    mImageID = X::LoadTexture("white.jpg");
    mHealth = health;
}

bool Attacker::IsActive()
{
    return true;
}
