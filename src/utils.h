#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>

#ifndef _UTILS_
#define _UTILS_
class Utils
{
public:
    static uint32_t getRandomIntBetweenBounds(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }
    static void setSeed(uint32_t seed)
    {
        srand(seed);
    }
    static void HSVtoRGB(float H, float S, float V, uint8_t * rOut, uint8_t * gOut, uint8_t * bOut)
    {
        if (H > 360 || H < 0 || S > 100 || S < 0 || V > 100 || V < 0)
        {
            return;
        }
        float s = S / 100;
        float v = V / 100;
        float C = s * v;
        float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
        float m = v - C;
        float r, g, b;
        if (H >= 0 && H < 60)
        {
            r = C, g = X, b = 0;
        }
        else if (H >= 60 && H < 120)
        {
            r = X, g = C, b = 0;
        }
        else if (H >= 120 && H < 180)
        {
            r = 0, g = C, b = X;
        }
        else if (H >= 180 && H < 240)
        {
            r = 0, g = X, b = C;
        }
        else if (H >= 240 && H < 300)
        {
            r = X, g = 0, b = C;
        }
        else
        {
            r = C, g = 0, b = X;
        }
        *rOut = (r + m) * 255;
        *gOut = (g + m) * 255;
        *bOut = (b + m) * 255;
    }
};
#endif