#ifndef FACADEOPERATIONRESULT_H
#define FACADEOPERATIONRESULT_H

#include "library.h"

using namespace std;

class FacadeOperationResult
{
private:
    string errorMessage;
    bool isSuccess;
    FacadeOperationResult();
public:
    FacadeOperationResult(string errorMessage);
    static FacadeOperationResult GetOkResult();
    string GetErrorMessage();
    bool IsSuccess();
};

#endif // FACADEOPERATIONRESULT_H
