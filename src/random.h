#pragma once
#include <stdlib.h>
#include <cstdint>

class Random
{
public:
    static Random& Get()
    {
        static Random instance;
        return instance;
    }
    template<typename T> static T GetRandomNum(T max)
    {
        return Get().IGetRandomNum(max);
    }
    static void Seed(std::int32_t seed)
    {
        Get().ISeed(seed);
    }
private:
    template<typename T>T IGetRandomNum(T max)
    {
        T num = rand() % max;
        return num;
    }
    void ISeed(std::int32_t seed)
    {
        srand(seed);
    }
};