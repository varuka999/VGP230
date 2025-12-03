#include "EnemyManager.h"
#include "TileMap.h"

EnemyManager* EnemyManager::mInstance = nullptr;

EnemyManager::EnemyManager()
    : Entity(), mNextAvailableIndex(0), mWave(0), mEnemyWaveTimer(0.0f)
{

}

EnemyManager::~EnemyManager()
{

}

EnemyManager* EnemyManager::Get()
{
	if (mInstance == nullptr)
	{
		mInstance = new EnemyManager();
	}

	return mInstance;
}

void EnemyManager::Load()
{
	const int maxEnemies = 100;

	for (int i = 0; i < maxEnemies; ++i)
	{
		Enemy* newEnemy = new Enemy(); 
		newEnemy->Load();
		mEnemies.push_back(newEnemy);
	}

	mNextAvailableIndex = 0;
    mWave = 0;
    mEnemyWaveTimer = 1.0f;
}

void EnemyManager::Update(float deltaTime)
{
    mEnemyWaveTimer -= deltaTime;
    if (mEnemyWaveTimer <= 0.0f && mWave < 4)
    {
        ++mWave;
        SpawnEnemies(3 * mWave);

        mEnemyWaveTimer = 3 * mWave;
    }
	//if (X::IsKeyPressed(X::Keys::RCONTROL))
	//{
	//	SpawnEnemies(3);
	//}

	for (Enemy* enemy : mEnemies)
	{
		enemy->Update(deltaTime);
	}
}

void EnemyManager::Render()
{
    int enemiesDefeated = mEnemies[0]->GetEnemiesDefeated();
    int enemiesRemaining = 15 - enemiesDefeated;

    std::string text = std::string("Enemies Remaining: ") + std::to_string(enemiesRemaining);

    X::TextureId dummyTile = X::LoadTexture("white.jpg");
    const float tileWidth = X::GetSpriteWidth(dummyTile);
    const float tileHeight = X::GetSpriteHeight(dummyTile);
    //X::Math::Vector2 offset = { tileWidth * 0.5f, tileHeight * 0.5f };


    const float textSize = 30.0f;
    float textWidth = X::GetTextWidth(text.c_str(), textSize);
    X::Math::Vector2 offset = { -textWidth * 0.5f, tileHeight * 0.5f };
    float screenX = tileWidth * (TileMap::Get()->GetWidth() / 2) + offset.x;
    //float screenX = (X::GetScreenWidth()) * 0.5f;
    float screenY = 20.0f;
    X::DrawScreenText(text.c_str(), screenX, screenY, textSize, X::Colors::Orange);

	for (Enemy* enemy : mEnemies)
	{
		enemy->Render();
	}
}

void EnemyManager::Unload()
{
	for (Enemy* enemy : mEnemies)
	{
		enemy->Unload();
		delete enemy;
		enemy = nullptr;
	}

	mEnemies.clear();
}

void EnemyManager::SpawnEnemies(int amount)
{
    std::vector<Tile*> walkableTiles;
    TileMap::Get()->ObtainAllWalkableTiles(walkableTiles);

    // Remove occupied tiles
    for (Enemy* enemy : mEnemies)
    {
        if (enemy->IsActive())
        {
            for (int i = 0; i < walkableTiles.size(); ++i)
            {
                if (walkableTiles[i]->HasCollision(enemy->GetRect()))
                {
                    if (i < walkableTiles.size() - 1)
                    {
                        Tile* temp = walkableTiles[walkableTiles.size() - 1];
                        walkableTiles[walkableTiles.size() - 1] = walkableTiles[i];
                        walkableTiles[i] = temp;
                    }

                    walkableTiles.pop_back();
                    break;
                }
            }
        }
    }

    int prevUsedIndex = 0;

    for (int i = 0; i < amount; ++i)
    {
        prevUsedIndex = mNextAvailableIndex - 1;

        if (prevUsedIndex < 0)
        {
            prevUsedIndex = mEnemies.size() - 1;
        }

        while (mNextAvailableIndex != prevUsedIndex)
        {
            Enemy* enemy = mEnemies[mNextAvailableIndex];
            mNextAvailableIndex = (mNextAvailableIndex + 1) % mEnemies.size();

            if (!enemy->IsActive())
            {
                int randomIndex = X::Random(0, walkableTiles.size() - 1);
                Tile* randomTile = walkableTiles[randomIndex];
                enemy->SetActive(randomTile->GetPosition(), 10); // Set Enemy Health Here

                if (randomIndex < walkableTiles.size() - 1)
                {
                    Tile* temp = walkableTiles[walkableTiles.size() - 1];
                    walkableTiles[walkableTiles.size() - 1] = walkableTiles[randomIndex];
                    walkableTiles[randomIndex] = temp;
                }

                walkableTiles.pop_back();
                break;
            }
        }
    }
}

bool EnemyManager::IsGameOver()
{
    return mEnemies[0]->GetEnemiesDefeated() >= 15;
}
