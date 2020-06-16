#include "NormalizationParametrs.h"

NormalizationParametrs::NormalizationParametrs(float min, float max, float stepX, float stepY)
{
    Min = min;
    Max = max;
    DxStep = stepX;
    DyStep = stepY;
}

float NormalizationParametrs::GetMin()
{
    return Min;
}

float NormalizationParametrs::GetMax()
{
    return Max;
}

float NormalizationParametrs::GetStepX()
{
    return DxStep;
}

float NormalizationParametrs::GetStepY()
{
    return DyStep;
}

