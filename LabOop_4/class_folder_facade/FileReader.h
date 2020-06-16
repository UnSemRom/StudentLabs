#ifndef FILEREADER_H
#define FILEREADER_H

#include "BaseFileReader.h"
using namespace std;
class FileReader : public BaseFileReader
{
private:
    vector<Figure> figure;
    int QuantityI, QuantityJ;
    vector<vector<float>> LoadData(ifstream &file);
    vector<float> SeparateStrVec(string str);
    vector<string> LoadLine(ifstream &file);
    vector<vector<float>> FileOpen(string &filename);
    Figure setFigure(vector<vector<float>> &matrix, NormalizationParametrs &parametrs);
    float normalize_point(NormalizationParametrs &parametrs, int value, char coordinate, float max, float min);
    float Min(vector<vector<float>> &matrix);
    float Max(vector<vector<float>> &matrix);
    Vertex Normalize(vector<vector<float>> &matrix, NormalizationParametrs &parametrs, float max, float min, int i, int j);
public:
    FileReader(){};
    Scene ReadScene(string &path, NormalizationParametrs &parametrs) override;
};

#endif // FILEREADER_H
