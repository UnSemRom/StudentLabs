#ifndef CALCULATION_H
#define CALCULATION_H
#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "structures_data.h"

op_type_t get_op_type(operation_t &op);
result_figure_t drawing_load(operation_t &op, double** values);
void string_copy(char *str_to, char* str_from, int n);
double** malloc_values(int count);
void get_values(FILE* text, double** values);
void camera_move(operation_t &op, double** xs, double** ys, double** zs);
void camera_rotate(operation_t &op, double** xs, double** ys, double** zs);

#endif // CALCULATION_H
