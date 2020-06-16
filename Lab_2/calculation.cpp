#include "calculation.h"

result_t math_metric(vector<string> stat)
{

    result_t res;
    vector<double>temp_stat;
    temp_stat = from_str_to_double(stat, temp_stat);

    res.min = min_calculation(temp_stat);
    res.max = max_calculation(temp_stat);
    res.med = med_calculation(temp_stat);
    return res;
}

double min_calculation(vector<double>stat)
{
    double min = stat[0];
    for (int i = 0; i < stat.size(); i++)
    {
        double temp = stat[i];
        if (min > temp)
        {
            min = temp;
        }
    }
    return min;
}

double max_calculation(vector<double>stat)
{
    double max = stat[0];
    for (int i = 0; i < stat.size(); i++)
    {
        double temp = stat[i];
        if (max < temp)
        {
            max = temp;
        }
    }
    return max;
}


vector<double> from_str_to_double(vector<string> stat, vector<double> temp_stat)
{
    for(int i = 0; i < stat.size(); i++)
    {
        double temp = atof(stat[i].c_str());
        temp_stat.push_back(temp);
    }
    return temp_stat;
}

double med_calculation(vector<double>stat)
{

    double med;
    sort(stat.begin(),stat.end());

    if (stat.size()%2 != 0)
    {
        med = stat[stat.size()/2];
    }
    else
    {
        med = (stat[stat.size()/2]+stat[stat.size()/2-1])/2.0;
    }
    return med;
}
