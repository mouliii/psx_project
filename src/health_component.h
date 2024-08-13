#pragma once
#include <stdint.h>
#include "stats_component.h"

class HealthComponent
{
public:
    HealthComponent(StatsComponent* sc); 
    ~HealthComponent() = default;
    void Damage(int16_t amount);
    void Heal(int16_t amount);
    
private:
    StatsComponent* sc;
};