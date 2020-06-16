#ifndef BASEFILEREADER_H
#define BASEFILEREADER_H

#include "Scene.h"
#include "NormalizationParametrs.h"

#include "library.h"

using namespace std;

class BaseFileReader
{
public:
    BaseFileReader(){};
    virtual Scene ReadScene(string &path, NormalizationParametrs &parametrs) = 0;
};

#endif // BASEFILEREADER_H
