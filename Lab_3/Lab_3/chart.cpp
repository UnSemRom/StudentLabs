#include "chart.h"


void print_OX(int max_x, int max_y, int x_0, int y_0, QPainter* paint)
{
    QPen pen(Qt::gray, 3);
    paint->setPen(pen);
    paint->drawLine(x_0, y_0, max_x-20, y_0);

    QPolygon tri;
    tri << QPoint(max_x, y_0) << QPoint(max_x-20,y_0-10) << QPoint(max_x-20,y_0+10);
    paint->setBrush(Qt::gray);
    paint->drawPolygon(tri);

    paint->drawText(max_x-70, -5, "Yers");
}

void print_OY(int max_x, int max_y, int x_0, int y_0, QPainter* paint)
{
    QPen pen(Qt::gray, 3);
    paint->setPen(pen);
    paint->drawLine(x_0, y_0, x_0, -1*(max_y-20));

    QPolygon tri;
    tri << QPoint(x_0, -1*(max_y)) << QPoint(x_0+10,-1*(max_y-20)) << QPoint(x_0-10,-1*(max_y-20));
    paint->setBrush(Qt::gray);
    paint->drawPolygon(tri);

    paint->drawText(6, -1*(max_y-55), "Metric");
}

void creating_canvas(int max_x, int max_y, QPainter* paint)
{
    paint->fillRect(0, 0, max_x, max_y, QBrush(QColor(Qt::GlobalColor::white)));
    paint->translate(0, max_y);
}

void print_polyline(int max_x, int max_y, int x_0, int y_0, chart_data_t chart_data, QPainter* paint)
{
    QPen pen(Qt::blue, 3);
    paint->setPen(pen);

    int x = x_0;
    float step_y = (max_y-25+y_0)/(chart_data.max-chart_data.min);
    float step_x = (max_x-20-x_0)/chart_data.column.size();

    for (int i = 0; i < chart_data.column.size()-1; i++)
    {
        int y_1p = -(atof(chart_data.column[i].c_str()))*step_y+y_0+chart_data.min*step_y;
        int y_2p = -(atof(chart_data.column[i+1].c_str()))*step_y+y_0+chart_data.min*step_y;

        paint->drawLine(x, y_1p, x+step_x, y_2p);
        x += step_x;
    }
}

void print_name_OY(int max_x, int max_y, int x_0, int y_0, chart_data_t chart_data, QPainter* paint)
{
    QPen pen(Qt::gray, 1);
    paint->setPen(pen);

    float step_y = -1*(max_y - 20 + y_0)/10;
    float start_y = y_0;
    double min = chart_data.min;
    double step_num = (chart_data.max - chart_data.min)/10;

    for (int i = 0; i < 10; i++)
    {

        QString qstr = QString::number(min);
        paint->drawText(x_0-35, start_y, qstr);

        paint->drawLine(x_0, start_y, max_x, start_y);

        start_y = start_y + step_y;
        min += step_num;
    }
}

void print_name_OX(int max_x, int max_y, int x_0, int y_0, chart_data_t chart_data, QPainter* paint)
{

    QPen pen(Qt::gray, 1);
    paint->setPen(pen);

    int flag = 0;
    int start_x = x_0;
    float step_x = (max_x-20-x_0)/chart_data.column.size();

    for (int i = 0; i < chart_data.column.size(); i++)
    {
        if (flag%2 ==0)
        {
            QString qstr = QString::fromStdString(chart_data.year[i]);
            paint->drawText(start_x,y_0+15, qstr);

            paint->drawLine(start_x, y_0, start_x, -1*(max_y));
        }
        start_x += step_x;
        flag = flag + 1;
    }
}

void print_point(int max_x, int max_y, int x_0, int y_0, chart_data_t chart_data, QPainter* paint)
{
    QPen pen(Qt::black, 10);
    paint->setPen(pen);

    int x = x_0;
    float step_y = (max_y-25+y_0)/(chart_data.max-chart_data.min);
    float step_x = (max_x-20-x_0)/chart_data.column.size();

    for (int i = 0; i < chart_data.column.size(); i++)
    {
        int y = -(atof(chart_data.column[i].c_str()))*step_y+y_0+chart_data.min*step_y;

        paint->drawPoint(x, y);
        x += step_x;
    }
}

QPixmap* chart(chart_data_t chart_data)
{
    int max_x = MAX_X;
    int max_y = MAX_Y;
    int x_0 = X_0;
    int y_0 = Y_0;

    QPixmap *pix = new QPixmap(max_x, max_y);
    QPainter paint(pix);

    creating_canvas(max_x, max_y, &paint);

    print_OX(max_x, max_y, x_0, y_0, &paint);
    print_OY(max_x, max_y, x_0, y_0, &paint);

    print_point(max_x, max_y, x_0, y_0, chart_data, &paint);
    print_polyline(max_x, max_y, x_0, y_0, chart_data, &paint);

    print_metrics(max_x, max_y, x_0, y_0, chart_data, &paint);

    print_name_OY(max_x, max_y, x_0, y_0, chart_data, &paint);
    print_name_OX(max_x, max_y, x_0, y_0, chart_data, &paint);

    return pix;
}

void print_metrics(int max_x, int max_y, int x_0, int y_0, chart_data_t chart_data, QPainter* paint)
{
    QPen pen(Qt::red, 3);
    pen.setStyle(Qt::DashDotDotLine);
    paint->setPen(pen);
    int x = x_0;

    float step_y = (max_y-25+y_0)/(chart_data.max-chart_data.min);
    float step_x = (max_x-20-x_0)/chart_data.column.size();
    paint->drawLine(x_0, -1*chart_data.med*step_y+y_0+chart_data.min*step_y, max_x, -1*chart_data.med*step_y+y_0+chart_data.min*step_y);

    pen.setWidth(10);
    paint->setPen(pen);
    for (int i = 0; i < chart_data.column.size(); i++)
    {
        double num = atof(chart_data.column[i].c_str());
        if (num == chart_data.max || num == chart_data.min || num == chart_data.med)
        {
        int y = -num*step_y+y_0+chart_data.min*step_y;
        paint->drawPoint(x, y);
        }
        x += step_x;
    }
}

