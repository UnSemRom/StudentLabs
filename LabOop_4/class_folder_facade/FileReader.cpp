#include "FileReader.h"



Scene FileReader::ReadScene(string &path, NormalizationParametrs &parametrs)
{
    vector<vector<float>> matrix = FileOpen(path);
    figure.push_back(setFigure(matrix, parametrs));
    Scene scene(figure);
    return scene;
}

Figure FileReader::setFigure(vector<vector<float>> &matrix, NormalizationParametrs &parametrs)
{
    float max = Max(matrix);
    float min = Min(matrix);
    vector<Vertex> figure_;
    for (int i = 0; i < QuantityI; i++)
    {
        for (int j = 0; j < QuantityJ; j++)
        {
            Vertex vertex = Normalize(matrix, parametrs, max, min, i, j);
            figure_.push_back(vertex);
        }
    }
    Figure figure(figure_, QuantityI, QuantityJ);
    return figure;
}

Vertex FileReader::Normalize(vector<vector<float>> &matrix, NormalizationParametrs &parametrs, float max, float min, int i, int j)
{

    float z = normalize_point(parametrs, matrix[i][j], 'z', max, min)/3;
    Vertex vertex(i, j, z);
    return vertex;
}

float FileReader::normalize_point(NormalizationParametrs &parametrs, int value, char coordinate, float max, float min)
{
    float point = parametrs.GetMin()+(value-min)*(parametrs.GetMax()-parametrs.GetMin())/(max-min);
    return point;
}

float FileReader::Min(vector<vector<float>> &matrix)
{
    float min;
    for(int i = 0; i < QuantityI; i++)
    {
        for(int j = 0; j < QuantityJ; j++)
        {
            if(matrix[i][j] < min)
            {
                min = matrix[i][j];
            }
        }
    }
    return min;
}

float FileReader::Max(vector<vector<float>> &matrix)
{
    float max;
    for(int i = 0; i < QuantityI; i++)
    {
        for(int j = 0; j < QuantityJ; j++)
        {
            if(matrix[i][j] > max)
            {
                max = matrix[i][j];
            }
        }
    }
    return max;
}

vector<vector<float>> FileReader::LoadData(ifstream &file)
{
    vector<string> line;
    vector<vector<float>> buf;
    line = LoadLine(file);
    for(size_t i = 0; i < line.size(); i++)
    {
        buf.push_back(SeparateStrVec(line[i]));
    }
    QuantityI = line.size();
    return buf;
}

vector<float> FileReader::SeparateStrVec(string str)
{
    char comma = ',';
    vector<float> points;
    stringstream line(str);
    string word = "";
    while(getline(line, word, comma))
    {
        points.push_back(stof(word));
    }
    QuantityJ = points.size();
    return points;
}

vector<string> FileReader::LoadLine(ifstream &file)
{
    string row;
    vector<string> line;
    for(size_t i = 0; getline(file, row); i++)
    {
        line.push_back(row);
    }
    return line;
}

vector<vector<float>> FileReader::FileOpen(string &filename)
{
    vector<vector<float>> buf;
    ifstream file(filename);
    bool ok = true;
    if (!file.is_open())
    {
        ok = false;
    }
    else
    {
        buf = LoadData(file);
    }
    file.close();
    return buf;
}
