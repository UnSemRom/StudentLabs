#include "calculation.h"


#define IMPOSSIBLE_MINUSES_CNT  3
#define MIN_STEP                1
#define MAX_STEP                19



static int get_nums_cnt(char *range);
static int get_nminuses_cnt(char *range);
static void move_values(double **values, int mfactor);
static double get_max(double **values, int values_cnt);
static double get_min(double **values, int values_cnt);

static void normalize_values(double **values, operation_t &op);
static void copy_values(double** new_values, double** values, int values_cnt);
static void make_xy_values(double** xs, double** ys);
static void rotate_x(double **ys, double **zs, int degree);
static void rotate_y(double **xs, double **zs, int degree);
static void rotate_z(double **xs, double **ys, double degree);

static bool is_range_correct(char* range, int &a, int &b);
static bool is_degrees_correct(operation_t &op);
static bool is_mfactors_correct(operation_t &op);
static bool is_factor_srange_correct(operation_t &op);
static bool is_factors_correct(operation_t &op);
static bool is_factor_correct(char* factor, int &fact);
static bool is_camera_rotate(operation_t &op);
static bool is_camera_move(operation_t &op);
static bool is_drawing_load(operation_t &op);


static int get_nums_cnt(char *range)
{
    int nums_cnt = 0;
    int range_len = strlen(range);

    for (int i = 0; i < range_len; i++)
        if (range[i] >= '0' && range[i] <= '9')
            nums_cnt++;

    return nums_cnt;
}

static int get_nminuses_cnt(char *range)
{
    int minuses_cnt = 0;
    char* comma_pos = strchr(range, ',');

    if (comma_pos != NULL) {
        if(comma_pos[1] == '-')
            minuses_cnt++;
        if(range[1] == '-')
            minuses_cnt++;

         return minuses_cnt;
    }

    return IMPOSSIBLE_MINUSES_CNT;
}

static void move_values(double **values, int mfactor)
{
    for (int i = 0; i < XY_MAX_COUNT; i++)
        for (int j = 0; j < XY_MAX_COUNT; j++)
            values[i][j] = values[i][j] + mfactor;
}

static double get_max(double **values, int values_cnt)
{
    double max = values[0][0];

    for (int i = 0; i < values_cnt; i++)
        for (int j = 0; j < values_cnt; j++)
            if (values[i][j] > max)
                max = values[i][j];

    return max;
}

static double get_min(double **values, int values_cnt)
{
    double min = values[0][0];

    for (int i = 1; i < values_cnt; i++)
        for (int j = 0; j < values_cnt; j++)
            if (values[i][j] < min)
                min = values[i][j];
    return min;
}

static void normalize_values(double **values, operation_t &op)
{
    double min = get_min(values, XY_MAX_COUNT);
    double max = get_max(values, XY_MAX_COUNT);
    for (int i = 0; i < XY_MAX_COUNT; i++)
        for (int j = 0; j < XY_MAX_COUNT; j++)
            values[i][j] = op.a + ((values[i][j] - min)* (op.b - op.a) / (max - min));
}

static void copy_values(double** new_values, double** values, int values_cnt)
{
    for (int i = 0; i < values_cnt; i++)
        for (int j = 0; j < values_cnt; j++)
            new_values[i][j] = values[i][j];
}

static void make_xy_values(double** xs, double** ys)
{
    for (int i = 0; i < XY_MAX_COUNT; i++)
        for (int j = 0; j < XY_MAX_COUNT; j++) {
            xs[i][j] = i;
            ys[i][j] = j;
        }
}

static void rotate_x(double **ys, double **zs, int degree)
{
    double degree_cos = cos(degree * M_PI / 180);
    double degree_sin = sin(degree * M_PI / 180);

    for (int i = 0; i < XY_MAX_COUNT; i++)
        for (int j = 0; j < XY_MAX_COUNT; j++) {
            ys[i][j] = ys[i][j] * degree_cos - zs[i][j] * degree_sin;
            zs[i][j] = ys[i][j] * degree_sin + zs[i][j] * degree_cos;
        }
}

static void rotate_y(double **xs, double **zs, int degree)
{
    double degree_cos = cos(degree * M_PI / 180);
    double degree_sin = sin(degree * M_PI / 180);

    for (int i = 0; i < XY_MAX_COUNT; i++)
        for (int j = 0; j < XY_MAX_COUNT; j++) {
            xs[i][j] = xs[i][j] * degree_cos + zs[i][j] * degree_sin;
            zs[i][j] = -xs[i][j] * degree_sin + zs[i][j] * degree_cos;
        }
}

static void rotate_z(double **xs, double **ys, double degree)
{
    double degree_cos = cos(degree * M_PI / 180);
    double degree_sin = sin(degree * M_PI / 180);

    for (int i = 0; i < XY_MAX_COUNT; i++)
        for (int j = 0; j < XY_MAX_COUNT; j++) {
            xs[i][j] = xs[i][j] * degree_cos - ys[i][j] * degree_sin;
            ys[i][j] = xs[i][j] * degree_sin + ys[i][j] * degree_cos;
        }
}

static bool is_range_correct(char* range, int &a, int &b)
{
    char *temp;
    int not_num_in_range_cnt = 1;
    int range_len, minuses_cnt, num_cnt, not_num_cnt;

    range_len = strlen(range);
    minuses_cnt = get_nminuses_cnt(range);
    num_cnt = get_nums_cnt(range);
    not_num_cnt = range_len - num_cnt - minuses_cnt;

    if (not_num_cnt == not_num_in_range_cnt && (temp = strtok(range, ",")) != NULL) {
        a = atoi(temp);
        temp = strtok(NULL, ",");
        b = atoi(temp);
        return true;
    }

    return false;
}

static bool is_degrees_correct(operation_t &op)
{
    if (is_factor_correct(op.degree_str_x, op.degree_x) &&
       is_factor_correct(op.degree_str_y, op.degree_y) &&
       is_factor_correct(op.degree_str_z, op.degree_z))
        return true;

    return false;
}


static bool is_mfactors_correct(operation_t &op)
{
    if (is_factor_correct(op.mfactor_str_x, op.mfactor_x) &&
       is_factor_correct(op.mfactor_str_y, op.mfactor_y) &&
       is_factor_correct(op.mfactor_str_z, op.mfactor_z))
        return true;

    return false;
}

static bool is_factor_srange_correct(operation_t &op)
{
    if (is_factors_correct(op) && is_range_correct(op.range, op.a, op.b) &&
       op.step >= MIN_STEP && op.step <= MAX_STEP )
        return true;

    return false;
}

static bool is_factors_correct(operation_t &op)
{
    if (is_mfactors_correct(op) && is_degrees_correct(op))
        return true;

    return false;
}

static bool is_factor_correct(char* factor, int &fact)
{
    int nums_cnt  = 0;
    int factor_len = strlen(factor);

    if (factor[0] != '\0') {
        nums_cnt = get_nums_cnt(factor);
        if (factor[0] == '-')
            nums_cnt++;
        fact = atoi(factor);
    } else {
        fact = 0;
    }

    if(nums_cnt == factor_len)
        return true;

    return false;
}

static bool is_camera_rotate(operation_t &op)
{
    if (op.degree_x != 0 && op.mfactor_x == 0 && op.degree_y != 0
                && op.mfactor_y == 0 && op.degree_z != 0 && op.mfactor_z == 0)
        return true;

    return false;
}

static bool is_camera_move(operation_t &op)
{
    if (op.degree_x == 0 && op.mfactor_x != 0 && op.degree_y == 0
                 && op.mfactor_y != 0 && op.degree_z == 0 && op.mfactor_z != 0)
        return true;
    return false;
}

static bool is_drawing_load(operation_t &op)
{
    if (op.degree_x == 0 && op.mfactor_x == 0 && op.degree_y == 0
            && op.mfactor_y == 0 && op.degree_z == 0 && op.mfactor_z == 0)
        return true;
    return false;
}


void string_copy(char *str_to, char* str_from, int n)
{
    for(int i = 0; i < n; i++)
        str_to[i] = str_from[i];
    str_to[n] = '\0';
}

double** malloc_values(int count)
{
    double** mat = new double*[count];
    for (int i = 0; i < count; i++)
        mat[i] = new double [count];

    return mat;
}

void get_values(FILE* text, double** values)
{
    char str[CHARS_MAX_COUNT];
    char *temp;
    int i, j, size;

    i = 0;
    j = 0;

    fseek(text, 0, SEEK_END);
    size = ftell(text);
    fseek(text, 0, SEEK_SET);

    while (size != ftell(text)) {
        j = 0;
        fgets(str, CHARS_MAX_COUNT, text);
        temp = strtok(str, ",");
        if (temp != NULL) {
          values[i][j] = atof(temp);

          while (j < XY_MAX_COUNT && temp != NULL) {
              j++;
              temp = strtok(NULL, ",");
              if (temp == NULL)
                break;
              values[i][j] = atof(temp);
          }
        }
        i++;
    }
}

op_type_t get_op_type(operation_t &op)
{
    if (is_drawing_load(op))
        return OP_LOAD_DRAWING;
    else if (is_camera_rotate(op))
        return OP_CAMERA_ROTATE;
    else if (is_camera_move(op))
        return OP_CAMERA_MOVE;

    return OP_CAMERA_MOVE_ROTATE;
}

result_figure_t drawing_load(operation_t &op, double** values)
{
    result_figure_t res;

    if (is_factor_srange_correct(op)) {
        res.zs = malloc_values(VALUES_MAX_COUNT + 1);
        copy_values(res.zs, values, XY_MAX_COUNT);
        normalize_values(res.zs, op);

        res.xs = malloc_values(VALUES_MAX_COUNT + 1);
        res.ys = malloc_values(VALUES_MAX_COUNT + 1);

        make_xy_values(res.xs, res.ys);

        normalize_values(res.xs, op);
        normalize_values(res.ys, op);
    } else {
        res.error = true;
    }
    return res;
}

void camera_move(operation_t &op, double** xs, double** ys, double** zs)
{
    move_values(xs, op.mfactor_x);
    move_values(ys, op.mfactor_y);
    move_values(zs, op.mfactor_z);
}

void camera_rotate(operation_t &op, double  **xs, double **ys, double **zs)
{
    rotate_x(ys, zs, op.degree_x);
    rotate_y(xs, zs, op.degree_y);
    rotate_z(xs, ys, op.degree_z);
}
