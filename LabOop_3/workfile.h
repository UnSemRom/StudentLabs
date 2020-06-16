#ifndef FILEWORK_H
#define FILEWORK_H

#include "library.h"

using namespace std;


class fileReader
{
private:
    string filename;
public:
    fileReader() : filename(nullptr) {};
    fileReader(string f) : filename(f) {};
    void setFilename(string f) {filename=f;};
    string getContent();
};


#endif // FILEWORK_H
