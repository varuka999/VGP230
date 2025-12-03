#pragma once
#include "Enemy.h"

class EnemyManager : public Entity
{
public:
    ~EnemyManager();
    static EnemyManager* Get();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    void SpawnEnemies(int amount);
    bool IsGameOver();

private:
    EnemyManager();
    static EnemyManager* mInstance;

    std::vector<Enemy*> mEnemies;
    int mNextAvailableIndex;
    int mWave;
    float mEnemyWaveTimer;
};