#pragma once
#include "stats.h"

class StatsComponent
{
public:
    StatsComponent() = default; 
    StatsComponent(Stats* stats);
    ~StatsComponent(){ if (stats) {delete stats;}}
    //void LoadStats();
    Stats* GetStats(){return stats;}
private:
    Stats* stats;
};