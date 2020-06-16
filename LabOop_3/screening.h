#ifndef SHIELDING_H
#define SHIELDING_H

#include "library.h"

using namespace std;

class stringFormatter
{
private:
    string str;
public:
    stringFormatter() : str(nullptr) {};
    stringFormatter(string f) : str(f) {};
    void setString(string f) {str=f;};
    string getContent();
    string prepare();
private:
    void replaceableSize(int i, int& search, bool& flag, string& strPrint, string& upperSingleBracket);
    void copyWithoutSpSign(int i, int search, string& newStr, string& strPrint);
    void replacementValue(int i, int search, string& strPrint, string& replacement);
    string checkPrint(string s_for_out);
    string removeStr(string s, string p);



};


#endif // SHIELDING_H
