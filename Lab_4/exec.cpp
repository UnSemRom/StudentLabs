#include "calculation.h"

result_figure_t execute_operation(operation_t op)
{
    result_figure_t result;

    FILE* file = fopen(op.path, "r");

    if (file != NULL) {
        double **values = malloc_values(VALUES_MAX_COUNT);
        get_values(file, values);
        fclose(file);

        result = drawing_load(op, values);
        delete values;
        if (!result.error) {
            op.type = get_op_type(op);

            switch (op.type) {
            case OP_LOAD_DRAWING:
                break;
            case OP_CAMERA_MOVE:
                camera_move(op, result.xs, result.ys, result.zs);
                break;
            case OP_CAMERA_ROTATE:
                camera_rotate(op, result.xs, result.ys, result.zs);
                break;
            case OP_CAMERA_MOVE_ROTATE:
                camera_move(op, result.xs, result.ys, result.zs);
                camera_rotate(op, result.xs, result.ys, result.zs);
                break;
            }
        }
    } else {
        perror("Ошибка открытия файла");
        result.error = true;
    }
    return result;
}
