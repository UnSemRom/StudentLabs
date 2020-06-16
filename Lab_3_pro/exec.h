#ifndef EXEC_H
#define EXEC_H

#include <iostream>
#include <vector>
#include <fstream>
#include <QMessageBox>

using namespace std;

enum operation_type
{
    LOAD = 0,
    CALC_CHART = 1,
};

enum error_type
{
    FALSE = 2,
    TRUE = 3,
    WARNING = 4,
};

struct table_t {
    vector<string> year;
    vector<string> reg;
    vector<string> npg;
    vector<string> bir_r;
    vector<string> dea_r;
    vector<string> gdw;
    vector<string> urb;
};

struct operation_t
{
    operation_type type;
    string filename;
    int column_number;
    string region;
    table_t table;
};

struct result_t
{
    table_t table;
    double min;
    double max;
    double med;

    error_type error = FALSE;
    string error_message;
};

result_t execure_operation(operation_t operation);

result_t load_table(operation_t* operation);

result_t calculate_metrix(operation_t* operation);

void adding_data_in_res(result_t* res, string year, string reg, string npg, string bir_r, string dea_r, string gdw, string urb);

void reading_single_line_file(ifstream* file_reg, string* year, string* reg, string* npg, string* bir_r, string* dea_r, string* gdw, string* urb);

void error(error_type* error, string* error_message, string str);

int misappropriation_colm( vector<string>* stat, operation_t* operation);

#endif // EXEC_H
