#pragma once

class Random 
{
public:

    static int Range(int min, int max);
    static float Range(float min, float max);
    static bool Chance(float p);

private:
    
    static std::mt19937& GetRng();
    static float Clamp(float value, float min, float max);
};
