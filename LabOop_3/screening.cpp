#include "screening.h"


string stringFormatter::prepare()
{
    return checkPrint(str);
}

void stringFormatter::replaceableSize(int i, int& search, bool& flag, string& strPrint, string& upperSingleBracket)
{
    for(size_t j = i + 1; !flag; j++)
    {
        if(strPrint[j] == upperSingleBracket[0])
        {
            search = j;
            flag = 1;
        }
    }
}

void stringFormatter::copyWithoutSpSign(int i, int search, string& newStr, string& strPrint)
{
    for(size_t k = i + 1; k < search; k++)
    {
        newStr += strPrint[k];
    }
}

void stringFormatter::replacementValue(int i, int search, string& strPrint, string& replacement)
{
    for(size_t k = i; k < search + 1; k++)
    {
        replacement += strPrint[k];
    }
}

string stringFormatter::checkPrint(string strPrint)
{
    string upperSingleBracket = "'";
    string upperDoubleBracket = "\"";
    string doubleSticks = "\\";
    string newStr = "";
    string replacement = "";
    int search = 0;
    size_t i = 0;

    while (i<strPrint.length())
    {
        if(strPrint[i] == upperSingleBracket[0])
        {
            bool flag = 0;
            replaceableSize(i, search, flag,  strPrint, upperSingleBracket);
            copyWithoutSpSign( i, search, newStr, strPrint);
            replacementValue(i, search, strPrint, replacement);
            strPrint = removeStr(strPrint, replacement);
            strPrint.insert(i,  upperDoubleBracket + doubleSticks +  upperDoubleBracket + newStr + doubleSticks +  upperDoubleBracket +  upperDoubleBracket);
            i = search + 1;
        }
        i++;
    }
    return strPrint;
}

string stringFormatter::removeStr(string rstr, string replacement)
{
    size_t sizeReplacement  = replacement.length();
    for (size_t i = rstr.find(replacement); i != string::npos; i = rstr.find(replacement))
    {
        rstr.erase(i, sizeReplacement);
        break;
    }
    return rstr;
}

