#pragma once
#include "enemy.h"
#include "random.h"

//spawn rate up per sec
//per min swap vihu
//+random vihu
//
//minimum vihu määrä; alle spawnrate up
//max vihu
//
//min up per enemy swap
//
//min spwan range 1 screen outwards in a rectangular shape around the player
//
//despawn kaukana olevat

class EnemySpawner
{
public:
    EnemySpawner(){malloc(sizeof(Enemy) * MAX_ENEMIES);}
    ~EnemySpawner(){free(enemyArr);}
    void Update()
    {
        if (++counter >= 60)
        {
            for (int16_t i = 0; i < nEnemiesSpawn; i++)
            {
                SpawnEnemy();
            }
            
            counter = 0;
        }
    }
    void SpawnEnemy();
private:
    static constexpr int32_t MAX_ENEMIES = 1024;
    int32_t counter = 0;
    int16_t nEnemiesSpawn = 10;
    Enemy* enemyArr;
};