#include "exec.h"
#include "calculation.h"

result_t load_table(operation_t operation)
{
    ifstream file_reg(operation.filename);
    int flag = 0;

    result_t res;

    string year;
    string reg;
    string npg;
    string bir_r;
    string dea_r;
    string gdw;
    string urb;

    if(!file_reg.is_open())
    {
        error(&res.error, &res.error_message, "Документ не открылся");
        return res;
    }


    while(file_reg.good())
    {
        reading_single_line_file(&file_reg, &year, &reg, &npg, &bir_r, &dea_r, &gdw,&urb);

        if (reg == operation.region)
        {
            if (year == "" || npg == "" || bir_r == "" || dea_r == "" || gdw == "" || urb == "")
            {
                res.error = WARNING;
                continue;
            }

            adding_data_in_res(&res, year, reg, npg, bir_r, dea_r, gdw, urb);
            flag++;
        }
    }

    if (flag == 0)
    {
        error(&res.error, &res.error_message, "Нет такого региона");
    }
    return res;
}

void reading_single_line_file(ifstream* file_reg, string* year, string* reg, string* npg, string* bir_r, string* dea_r, string* gdw, string* urb)
{
    getline(*file_reg, *year, ',');
    getline(*file_reg, *reg, ',');
    getline(*file_reg, *npg, ',');
    getline(*file_reg, *bir_r, ',');
    getline(*file_reg, *dea_r, ',');
    getline(*file_reg, *gdw, ',');
    getline(*file_reg, *urb, '\n');
}

void adding_data_in_res(result_t* res, string year, string reg, string npg, string bir_r, string dea_r, string gdw, string urb)
{
    res->table.year.push_back(year);
    res->table.reg.push_back(reg);
    res->table.npg.push_back(npg);
    res->table.bir_r.push_back(bir_r);
    res->table.dea_r.push_back(dea_r);
    res->table.gdw.push_back(gdw);
    res->table.urb.push_back(urb);
}

int misappropriation_colm( vector<string>* stat, operation_t* operation)
{
    switch(operation->column_number)
    {
    case 3:

        *stat = operation->table.npg;
        break;

    case 4:
        *stat = operation->table.bir_r;
        break;

    case 5:
        *stat = operation->table.dea_r;
        break;

    case 6:
        *stat = operation->table.gdw;
        break;

    case 7:
        *stat = operation->table.urb;
        break;
    default:
        return 0;
    }
}

result_t calculate_metrix(operation_t operation)
{
    vector<string> stat;
    result_t res;

    if (misappropriation_colm(&stat, &operation) == 0)
    {
        error(&res.error, &res.error_message, "Введен некоректный номер столбца");
        return res;
    }
    res = math_metric(stat);
    return res;
}



void error(error_type* error, string* error_message, string str)
{
    *error = TRUE;
    *error_message = str;
}

result_t execure_operation(operation_t operation)
{
    result_t res;

    switch (operation.type)
    {
    case LOAD:
        res = load_table(operation);
        break;
    case CALC_CHART:
        res = calculate_metrix(operation);
        break;
    default:
        break;
    }
    return res;
}

