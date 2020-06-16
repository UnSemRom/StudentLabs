#ifndef ERRORCHECKCLASSCHILDRENTEXT_H
#define ERRORCHECKCLASSCHILDRENTEXT_H

#include "errorcheckclassBase.h"
#include "errorcheckclassChildrenMass.h"
#include "errorcheckclassChildrenSet.h"
#include "errorcheckclassChildrenStr.h"

class objectJsonText : public baseObjectJson
{
public:
    objectJsonText(string text){ this->text = text; }

    void corrUncorr();

private:
    string text;

    void objType();

    void checkInt();

};


#endif // ERRORCHECKCLASSCHILDRENTEXT_H
