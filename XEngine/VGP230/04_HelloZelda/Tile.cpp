#include "Tile.h"

Tile::Tile(TileType tileType, const X::Math::Vector2& position)
    : Entity(), mTileType(tileType), mPosition(position), mRect(0, 0, 0, 0), mImageID(0)
{

}

Tile::~Tile()
{

}

void Tile::Load()
{
    switch (mTileType)
    {
    case TT_NONE:
        break;
    case TT_GROUND: mImageID = X::LoadTexture("grass64.png");
        break;
    case TT_WALL:   mImageID = X::LoadTexture("wallrock64.png");
        break;
    case TT_WATER:  mImageID = X::LoadTexture("water64.png");
        break;
    case TT_VINE: mImageID = X::LoadTexture("vine64.png");
        break;
    case TT_MAGMA:  mImageID = X::LoadTexture("magma64.png");
        break;
    default:
        XASSERT(false, "Tile: Invalid Tile Type");
    }

    float halfWidth = X::GetSpriteWidth(mImageID) * 0.5f;
    float halfHeight = X::GetSpriteHeight(mImageID) * 0.5f;
    mRect.left = mPosition.x - halfWidth;
    mRect.right = mPosition.x + halfWidth;
    mRect.top = mPosition.y - halfHeight;
    mRect.bottom = mPosition.y + halfHeight;
}

void Tile::Update(float deltaTime)
{

}

void Tile::Render()
{
    X::DrawSprite(mImageID, mPosition);
}

void Tile::Unload()
{

}

const X::Math::Vector2& Tile::GetPosition() const
{
    return mPosition;
}

bool Tile::IsCollidable() const
{
    return mTileType != TT_GROUND;
}

bool Tile::HasCollision(const X::Math::Rect& objRect) const
{
    return X::Math::Intersect(mRect, objRect);
}

const X::Math::Rect& Tile::GetRect() const
{
    return mRect;
}