#ifndef BUG_HUNTER_H
#define BUG_HUNTER_H

#include "library.h"
#include <vector>

using namespace std;


class baseObjectJson
{
public:
    baseObjectJson(){curPos=0;};
protected:
    int curPos;
    void baseEmptinessMassive(vector<string> mac);

    void baseCheck(string text);

    void startEnd(string long_text, int lng, const char key1_1, const char key2_1);

    int findEndStr(string text, char k2, bool str_or_not);

    size_t recurentFSet(string str, int i);

    size_t recurentFMass(string str, int i);

    string createObjString(string text);

    string createString(string long_text, char separator1, char separator2);

    string deleteAllnt(string text);

    string trim(string& str);

    vector<string> splitStr(string &str, const char sep);
};



#endif // BUG_HUNTER_H
