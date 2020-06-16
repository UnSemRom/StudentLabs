#ifndef ERRORCHECKCLASSCHILDRENSET_H
#define ERRORCHECKCLASSCHILDRENSET_H

#include "errorcheckclassBase.h"
#include "errorcheckclassChildrenMass.h"
#include "errorcheckclassChildrenStr.h"
#include "errorcheckclassChildrenText.h"

class objectJsonSet : public baseObjectJson
{
public:
    bool answer;
    string text;
    string textEdit;
    size_t lng;

    objectJsonSet(string text){this->text = text; lng = text.length(); }
    objectJsonSet(){this->text = ""; lng = 0;}

    void corrUncorr();

private:
    void search(vector<string> mac_in_mac);

    void punctuationMarks();

};

#endif // ERRORCHECKCLASSCHILDRENSET_H
