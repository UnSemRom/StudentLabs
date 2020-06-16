#ifndef STRUCTURES_DATA_H
#define STRUCTURES_DATA_H

#define CHARS_MAX_COUNT        255
#define VALUES_MAX_COUNT      900
#define XY_MAX_COUNT          20

typedef enum op_type {
    OP_LOAD_DRAWING,
    OP_CAMERA_MOVE,
    OP_CAMERA_ROTATE,
    OP_CAMERA_MOVE_ROTATE
} op_type_t;

typedef struct operation {
    int step;
    op_type_t type;
    char* range;
    char* path;
    char* degree_str_x;
    char* degree_str_y;
    char* degree_str_z;
    char* mfactor_str_x;
    char* mfactor_str_y;
    char* mfactor_str_z;
    int degree_x;
    int degree_y;
    int degree_z;
    int mfactor_x;
    int mfactor_y;
    int mfactor_z;
    int a;
    int b;
    bool moved_x;
    bool moved_y;
    bool moved_z;
    bool rotated_x;
    bool rotated_y;
    bool rotated_z;
} operation_t;

typedef struct result_figure {
    double** zs;
    double** ys;
    double** xs;
    bool error = false;
} result_figure_t;

#endif // STRUCTURES_DATA_H
