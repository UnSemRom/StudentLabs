#ifndef POINT_H
#define POINT_H
using namespace std;
class Point
{
private:
    float X;
    float Y;
    float Z;
public:
    Point(){};
    Point(float x, float y, float z): X(x), Y(y), Z(z) {};
    void SetPointX(float x);
    void SetPointY(float y);
    void SetPointZ(float z);
    float GetPointX();
    float GetPointY();
    float GetPointZ();
};

#endif // POINT_H
