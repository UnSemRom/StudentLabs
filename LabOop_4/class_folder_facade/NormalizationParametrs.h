#ifndef NORMALIZATIONPARAMETRS_H
#define NORMALIZATIONPARAMETRS_H
using namespace std;
class NormalizationParametrs
{
private:
    float Min;
    float Max;
    float DxStep;
    float DyStep;
public:
    NormalizationParametrs(float min, float max, float stepX, float stepY);
    float GetMin();
    float GetMax();
    float GetStepX();
    float GetStepY();
};

#endif // NORMALIZATIONPARAMETRS_H
