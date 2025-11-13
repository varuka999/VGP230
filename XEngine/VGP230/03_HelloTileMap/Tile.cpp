#include "Tile.h"

Tile::Tile(TileType tileType, const X::Math::Vector2& position)
	: mTileType(tileType), mPosition(position), mImageID(0)
{
}

Tile::~Tile()
{
}


void Tile::Load()
{
	switch (mTileType)
	{
	case Grass: mImageID = X::LoadTexture("grass.png");
		break;
	case GrassFlower: mImageID = X::LoadTexture("flower.png");
		break;
	case Dirt: mImageID = X::LoadTexture("grass_2.png");
		break;
	case DirtFLower: mImageID = X::LoadTexture("flower_2.png");
		break;
	case GrassTree1: mImageID = X::LoadTexture("tree0.png");
		break;
	case GrassTree2: mImageID = X::LoadTexture("tree1.png");
		break;
	case GrassTree3: mImageID = X::LoadTexture("tree2.png");
		break;
	case GrassTree4: mImageID = X::LoadTexture("tree3.png");
		break;
	case DirtTree1: mImageID = X::LoadTexture("tree0_2.png");
		break;
	case DirtTree2: mImageID = X::LoadTexture("tree1_2.png");
		break;
	case DirtTree3: mImageID = X::LoadTexture("tree2_2.png");
		break;
	case DirtTree4: mImageID = X::LoadTexture("tree3_2.png");
		break;
	default:
		break;
	}
}
void Tile::Update(float deltaTime)
{

}
void Tile::Render()
{
	X::DrawSprite(mImageID, mPosition, X::Pivot::TopLeft);
}

void Tile::Unload()
{

}