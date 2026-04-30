#include "Random.h"

std::mt19937& Random::GetRng()
{
    static std::mt19937 rng(std::random_device{}());
    return rng;
}

float Random::Clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

int Random::Range(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(GetRng());
}

float Random::Range(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(GetRng());
}

bool Random::Chance(float p)
{
    p = Clamp(p, 0.0f, 1.0f);
    return Range(0.0f, 1.0f) < p;
}