#include "errorcheckclassChildrenSet.h"



void objectJsonSet::search(vector<string> macInMac)
{
    const char searchChar = '"';

    size_t i = 0;
    bool flag = 0;
    bool wrong = 0;
    int end_i = findEndStr(macInMac[0], '"' ,1);
    if (end_i < 0)
        wrong = 1;
    while(i<text.length() && !flag && !wrong)
    {
        if(macInMac[0][i] == searchChar && macInMac[0][end_i] == searchChar)
        {
            objectJsonString jstring(macInMac[0]);
            jstring.correctString();
            flag = 1;
        }
        if(isgraph(macInMac[0][i]) && !flag) {
            wrong = 1;
        }
        i++;
    }

    if(!flag) {
        throw exceptionJson(ERROR_STRING, &macInMac[0][i]);
    }

    string s = macInMac[1];
    string a = "'";

    flag = 0;
    i = 0;

    while(i<s.length() && !flag)
    {
        if(s[i] == '{')
        {
            objectJsonSet jobjset(s);
            jobjset.corrUncorr();
            flag = 1;
        }
        else if(s[i] == '[')
        {
            objectJsonMass jobjmas(s);
            jobjmas.corrUncorr();
            flag = 1;
        }
        else if(s[i] == '"' || s[i] == a[0])
        {
            objectJsonString jobjstring(s);
            jobjstring.correctString();
            flag = 1;
        }
        i++;
    }

    if(!flag)
    {
        objectJsonText jobjcont(s);

        jobjcont.corrUncorr();
    }
}

void objectJsonSet::punctuationMarks()
{
    char separator1 = ',';
    char separator2 = ':';
    vector<string> mac;
    vector<string> macInMac;


    textEdit = createString(textEdit, '{', '}');
    curPos++;

    mac = splitStr(textEdit, separator1);

    baseEmptinessMassive(mac);
    size_t j = 0;
    while( j<mac.size())
    {

        macInMac = splitStr(mac[j], separator2);
        baseEmptinessMassive(macInMac);
        if(macInMac.size() == 2)
        {
            search(macInMac);
        }
        else
        {
            if (macInMac.size()<1)
                throw exceptionJson(ERROR_EMPTY_STRING, mac[j]);
            else
                throw exceptionJson(ERROR_LOT_SEPARATORS, macInMac[0]);

        }
        curPos += mac[j].length() + 1;
        j++;
    }
}

void objectJsonSet::corrUncorr()
{
    textEdit = deleteAllnt(text);
    baseCheck(text);
    punctuationMarks();
}

