#include "errorcheckclassChildrenStr.h"


void objectJsonString::correctString()
{
    bool answer = 0;
    string a = "'";

    answer = closeOpen();

    if(answer)
    {
        size_t i = 0;
        bool flag = 0;
        bool wrong = 0;
        while(i < text.length() && !flag && !wrong)
        {
            if(text[i] == '"' || text[i] == a[0])
            {
                searchProblems();
                flag = 1;
            }
            if(text[i] != ' ' && text[i] != '\t' && text[i] != '\n' && !flag) {
                throw exceptionJson(ERROR_STRING);
            }
            i++;
        }

    }
    else {
        throw exceptionJson(ERROR_STRING);
    }
}

bool objectJsonString::closeOpen()
{
    bool answer = 0;
    bool wrong = 0;
    size_t i = 0;

    int endI = findEndStr(text, '"', 1);

    while(i<text.length() && !answer && !wrong)
    {
        if(text[i] == text[endI])
            answer = 1;

        if(text[i] != ' ' && text[i] != '\t' && text[i] != '\n' && !answer)
            wrong = 1;

        i++;
    }

    return answer;
}

void objectJsonString::searchProblems()
{
    size_t count = 0;
    for(size_t i = 0; i<text.length(); i++)
    {
        if(text[i] == '"')
            if (i == 0 || text[i-1] != '\\')
                count++;
    }

    if(count>2)
        throw exceptionJson(ERROR_LOT_QUOTATION_MARKS_WORD, text);

}
