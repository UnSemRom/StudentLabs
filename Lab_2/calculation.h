#ifndef CALCULATION_H
#define CALCULATION_H

#include "exec.h"

#include <algorithm>

result_t math_metric(vector<string> stat);

double min_calculation(vector<double>stat);

double max_calculation(vector<double>stat);

vector<double> from_str_to_double(vector<string> stat, vector<double> temp_stat);

double med_calculation(vector<double>stat);

#endif // CALCULATION_H
