#include "workfile.h"


string fileReader::getContent()
{
    ifstream file(filename);
    string result;
    string str;

    if (!(file.is_open()))
    {
        cout << "File not find\n";
        //throw  exception(ERROR_File_Didnt_Open);
    }

    while (getline(file, str))
    {
        result = result + str + "\n";
    }

    return result;
}
