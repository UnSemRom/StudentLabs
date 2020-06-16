#ifndef ERRORCHECKCLASSCHILDRENMASS_H
#define ERRORCHECKCLASSCHILDRENMASS_H


#include "errorcheckclassBase.h"
#include "errorcheckclassChildrenSet.h"
#include "errorcheckclassChildrenStr.h"
#include "errorcheckclassChildrenText.h"


class objectJsonMass : public baseObjectJson
{
public:
    string textEdit;
    string text;
    int lng;
    bool answer;

    objectJsonMass(){ text = ""; }
    ~objectJsonMass(){ text = ""; lng = 0;}
    objectJsonMass(string text){ this->text = text; lng = text.length(); }

    void corrUncorr();

private:
    void search(string s);

    void distriction();
};
#endif // ERRORCHECKCLASSCHILDRENMASS_H
