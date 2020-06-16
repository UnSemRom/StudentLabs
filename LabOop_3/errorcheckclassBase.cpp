#include "errorcheckclassBase.h"


void baseObjectJson::baseEmptinessMassive(vector<string> mac)
{
    int is_char = 0;
    for(size_t i =0; i < mac.size(); i++)
    {
        is_char = 0;
        if(mac[i] == "  " || mac[i] == " " || mac[i] == "")//добавил услв
            throw exceptionJson(ERROR_EMPTY_VALUE, curPos);
    }
}

vector<string> baseObjectJson::splitStr(string &str, const char sep)
{
    size_t prev = 0;
    vector<string> arr;
    size_t i = 0;
    string m;
    while(i<str.length())
    {
        while (str[i] != sep && i < str.length())
        {
            if(str[i] == '{') {
                i = recurentFSet(str,i);
            } else if(str[i] == '[')
                i = recurentFMass(str,i);

            i++;
        }
        if (i >= prev) {
            m = str.substr(prev, i - prev);
            m = trim(m);
            if (m.size() > 0) {
                arr.push_back(m);
                prev = i+1;
                i++;
            }
        } else {
            break;
        }
    }
    return arr;
}

size_t baseObjectJson::recurentFSet(string str, int i)
{
    int answer = 0;
    size_t j = i+1;
    while(j<str.length())
    {
        if(str[j] == '{') {
            j = recurentFSet(str, j);
        }

        else if(str[j] == '}')
        {
            answer = j;
            break;
        }
        else if(str[j] == '[')
            j = recurentFMass(str, j);

        j++;
    }
    return answer;
}

size_t baseObjectJson::recurentFMass(string str, int i)
{
    int answer = 0;
    size_t j = i+1;

    while(j<str.length())
    {
        if(str[j] == '[')
            j = recurentFMass(str, j);

        else if(str[j] == ']')
        {
            answer = j;
            break;
        }

        else if(str[j] == '{')
            j = recurentFSet(str, j);

        j++;
    }

    return answer;
}



void baseObjectJson::baseCheck(string text)
{
    size_t countWords = 0;
    size_t countSet1 = 0;
    size_t countSet2 = 0;
    size_t countMass1 = 0;
    size_t countMass2 = 0;
    size_t countChar = 0;

    for(size_t i = 0; i<text.length(); i++)
    {
        string a = "'";
        if(text[i] == '"' && text[i-1] != '\\')
            countWords ++;
        else if(text[i] == '{')
            countSet1 ++;
        else if(text[i] == '}')
            countSet2 ++;
        else if(text[i] == '[')
            countMass1 ++;
        else if(text[i] == ']')
            countMass2 ++;
        else if(text[i] == a[0])
            countChar ++;
    }
    if(countSet1 == countSet2)
    {
        if(countMass1 == countMass2)
        {
            if(countWords%2 == 0)
            {
                if(countChar%2 != 0)
                    throw exceptionJson(ERROR_LOGIC_CLOSING_CHAR, -1);
            }
            else
                throw exceptionJson(ERROR_LOGIC_CLOSING_WORD, -1);
        }
        else
            throw exceptionJson(ERROR_LOGIC_CLOSING_MASS, -1);
    }
    else
        throw exceptionJson(ERROR_LOGIC_CLOSING_SET, -1);
}

int baseObjectJson::findEndStr(string text, char separator2, bool str_or_not)
{
    string a = "'";
    size_t i = 0;
    size_t count = -1;
    bool flag = 0;
    i = text.length();

    if(str_or_not)
    {
        while(!flag && i > 0)
        {
            i--;
            if((text[i] == a[0] && text[i-1] != '\\') || (text[i] == '"' && text[i-1] != '\\'))
            {
                count = i;
                flag = 1;
            }
        }
    }
    else
    {
        while(!flag)
        {
            i--;
            if(text[i] == separator2 && text[i-1] != '\\')
            {
                count = i;
                flag = 1;
            }
        }
    }
    return count;

}

string baseObjectJson::createString(string long_text, char separator1, char separator2)
{
    string Newstr;
    size_t k = 0;
    size_t endI;
    bool flag = 0;

    if(separator1 == separator2)
        endI = findEndStr(long_text, separator2, 1);
    else
        endI = findEndStr(long_text, separator2, 0);

    while(k<endI)
    {
        if(long_text[k] == separator1 && !flag)
        {
            flag = 1;
            curPos += k;

            k++;
        }
        if(!isgraph(long_text[k]) && !flag)
            Newstr = Newstr + long_text[k];

        if(flag)
            Newstr = Newstr + long_text[k];

        if(long_text[k] == separator2 && !flag)
            flag = 1;
        k++;
    }

    return Newstr;
}

string baseObjectJson::deleteAllnt(string text)
{
    string result;

    for(size_t i = 0; i<text.length();i++)
    {
        if(text[i]!='\n' && text[i]!='\t' && text[i]!='\r')
            result += text[i];
    }

    return result;
}

string baseObjectJson::trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}











