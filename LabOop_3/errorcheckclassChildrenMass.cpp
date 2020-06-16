#include "errorcheckclassChildrenMass.h"

void objectJsonMass::distriction()
{
    const char delitel1 = ',';
    vector<string> mac;

    text = createString(text, '[', ']');

    mac = splitStr(text, delitel1);

    size_t j = 0;
    while(j<mac.size())
    {
        search(mac[j]);
        j++;
    }
}

void objectJsonMass::search(string s)
{
    string a = "'";

    bool flag = 0;
    size_t i = 0;


    while (i<s.length() && !flag)
    {
        if(s[i] == '{')
        {
            objectJsonSet jobj(s);
            jobj.corrUncorr();
            flag = 1;
        }
        else if(s[i] == '[')
        {
            objectJsonMass jobj(s);
            jobj.corrUncorr();
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

void objectJsonMass::corrUncorr()
{
    baseCheck(text);
    distriction();
}
