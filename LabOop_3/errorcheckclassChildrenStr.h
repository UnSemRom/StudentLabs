#ifndef ERRORCHECKCLASSCHILDRENSTR_H
#define ERRORCHECKCLASSCHILDRENSTR_H

#include "errorcheckclassBase.h"
#include "errorcheckclassChildrenMass.h"
#include "errorcheckclassChildrenSet.h"
#include "errorcheckclassChildrenText.h"

class objectJsonString : public baseObjectJson
{
public:
    string text;

    objectJsonString(){ text = ""; }
    ~objectJsonString(){ text = ""; }
    objectJsonString(string text){ this->text = text; }

    void correctString();

private:
    bool closeOpen();
    void searchProblems();

};

#endif // ERRORCHECKCLASSCHILDRENSTR_H
