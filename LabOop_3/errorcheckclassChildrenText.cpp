#include "errorcheckclassChildrenText.h"


void objectJsonText::corrUncorr()
{
    objType();
}

void objectJsonText::objType()
{
    text = trim(text);
    if (text != "true" && text != "false") {
        checkInt();
    }

}

void objectJsonText::checkInt()
{
    size_t countE = 0;
    size_t countPoint = 0;
    size_t j = 0;
    bool flag = 0;

    if(text[0] == '-' || text[0] == ' ')
    {
        j++;
    }
        for(size_t i=j; i<text.length()-1; i++)
        {
            if(!isdigit(text[i]))
            {
                switch (text[i])
                {
                case 'e':
                    countE++;
                    break;
                case 'E':
                    countE++;
                    break;
                case '.':
                    countPoint++;
                    break;
                default:
                    throw exceptionJson(ERROR_BOOL_INT, text);
                    break;
                }
            }
        }
    if(countE > 1)
        throw exceptionJson(ERROR_LOT_E, text);

    if(countPoint > 1)
        throw exceptionJson(ERROR_LOT_POINTS, text);

}
