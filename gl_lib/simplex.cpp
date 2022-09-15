/*
 *  I got all of this code from:
 *       https://github.com/SRombauts/SimplexNoiseCImg
 *       https://github.com/SRombauts/SimplexNoise
 *
 *   ALl the implementation of the simplex noise was done by:
 *       Sebastien Rombauts (sebastien.rombauts@gmail.com)
 */

#include "simplex.h"

SimplexNoise::SimplexNoise(float f, float a, float l, float p)
{
    mFrequency = f;
    mAmplitude = a;
    mLacunarity = l;
    mPersistence = p;
}

int SimplexNoise::fastFloor(float v)
{
    int i = (int) v;
    return (v < i) ? (i - 1) : i;
}

uint8_t SimplexNoise::hash(int32_t i) {
    return perm[static_cast<uint8_t>(i)];
}

float SimplexNoise::grad(int32_t hash, float x, float y) {
    int32_t h = hash & 0x3F;  // Convert low 3 bits of hash code
    float u = h < 4 ? x : y;  // into 8 simple gradient directions,
    float v = h < 4 ? y : x;  // and compute the dot product with (x,y).
    return ((h & 1) ? -u : u) + ((h & 2) ? -2.0f*v : 2.0f*v);
}

float SimplexNoise::noise(float x, float y)
{
    float n0, n1, n2;

    const float F2 = 0.5 * (sqrt(3.0) - 1.0);
    double s = (x + y) * F2;
    int i = fastFloor(x + s);
    int j = fastFloor(y + s);

    const float G2 = (3.0 - sqrt(3.0))/ 6.0;
    float t = (i + j) * G2;
    float X0 = i - t;
    float Y0 = j - t;
    float x0 = x - X0;
    float y0 = y - Y0;

    int i1, j1;
    if (x0 > y0) 
    {
        i1 = 1;
        j1 = 0;
    }
    else
    {
        i1 = 0;
        j1 = 1;
    }

    float x1 = x0 - i1 + G2;
    float y1 = y0 - j1 + G2;    
    float x2 = x0 - 1.0 + 2.0 * G2;
    float y2 = y0 - 1.0 + 2.0 * G2;

    // Calculate the contribution from the first corner
    float t0 = 0.5f - x0*x0 - y0*y0;
    if (t0 < 0.0f) {
        n0 = 0.0f;
    } else {
        t0 *= t0;
        n0 = t0 * t0 * grad(hash(i + hash(j)), x0, y0);
    }

    // Calculate the contribution from the second corner
    float t1 = 0.5f - x1*x1 - y1*y1;
    if (t1 < 0.0f) {
        n1 = 0.0f;
    } else {
        t1 *= t1;
        n1 = t1 * t1 * grad(hash(i + i1 + hash(j + j1)), x1, y1);
    }

    // Calculate the contribution from the third corner
    float t2 = 0.5f - x2*x2 - y2*y2;
    if (t2 < 0.0f) {
        n2 = 0.0f;
    } else {
        t2 *= t2;
        n2 = t2 * t2 * grad(hash(i + 1 + hash(j + 1)), x2, y2);
    }

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 45.23065f * (n0 + n1 + n2);
}

float SimplexNoise::fractal(size_t octaves, float x, float y)
{
    float output = 0.f;
    float frequency = mFrequency;
    float amplitude = mAmplitude;

    for (size_t i = 0; i < octaves; i++) {
        output += (amplitude * noise(x * frequency, y * frequency));

        frequency *= mLacunarity;
        amplitude *= mPersistence;
    }

    return output;
}
