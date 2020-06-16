#include "FacadeOperationResult.h"

string FacadeOperationResult::GetErrorMessage()
{
    return errorMessage;
}

bool FacadeOperationResult::IsSuccess()
{
    return isSuccess;
}

FacadeOperationResult::FacadeOperationResult(string errorMessage)
{
    this->errorMessage = errorMessage;
    isSuccess = false;
}

FacadeOperationResult::FacadeOperationResult()
{
    errorMessage = "";
    isSuccess = true;
}

FacadeOperationResult FacadeOperationResult::GetOkResult()
{
    FacadeOperationResult res;
    return res;
}
