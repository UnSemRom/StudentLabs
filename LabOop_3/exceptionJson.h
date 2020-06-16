#ifndef JSONEXC_H
#define JSONEXC_H

#include "library.h"

using namespace std;


class exceptionJson : exception
{
private:
    string strErr;
    string strWhereErr;
    int whereErr;

public:
    exceptionJson(string str, int where):strErr(str), whereErr(where){}
    exceptionJson(string str, string where):strErr(str), strWhereErr(where){}
    exceptionJson(string str):strErr(str), whereErr(0){}

    ~exceptionJson() throw(){}

    const char* what() const throw()
    {
        return strErr.c_str();
    }
    int where() const throw()
    {
        return whereErr;
    }
    string whereStr() const throw()
    {
        return strWhereErr;
    }
};

#endif // JSONEXC_H
