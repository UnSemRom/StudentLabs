#ifndef CHART_H
#define CHART_H

#include "exec.h"
#include <QPainter>

#define MAX_X 1000;
#define  MAX_Y 720;
#define  X_0 45;
#define  Y_0 -30;

struct chart_data_t
{
    vector<string> column;
    vector<string> year;
    double max;
    double min;
    double med;
};

QPixmap* chart(chart_data_t chart_data);

void print_OX(int max_x,int max_y, int x_0, int y_0, QPainter* paint);

void print_OY(int max_x,int max_y, int x_0, int y_0, QPainter* paint);

void creating_canvas(int max_x, int max_y, QPainter* paint);

void print_polyline(int max_x, int max_y, int x_0, int y_0, chart_data_t chart_data, QPainter* paint);

void print_metrics(int max_x, int max_y, int x_0, int y_0, chart_data_t chart_data, QPainter* paint);

#endif // CHART_H
