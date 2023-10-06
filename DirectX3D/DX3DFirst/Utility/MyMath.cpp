#include "framework.h"

float MyMath::Clamp(const float& value, float minValue, float maxValue)
{
    return max(min(maxValue, value), minValue);
}

float MyMath::Saturate(const float& value)
{
    return Clamp(value, 0.0f, 1.0f);
}
