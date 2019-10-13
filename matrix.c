#include <stdlib.h>
#include <memory.h>

#include "matrix.h"

struct RGBLedMatrix *init_matrix(int* argc, char*** argv) {
    struct RGBLedMatrixOptions options;
    memset(&options, 0, sizeof(options));
    return led_matrix_create_from_options(&options, &argc, &argv);
}

void render_update(struct RGBLedMatrix* matrix, UpdateMessage* message) {
    struct LedCanvas* canvas = led_matrix_get_canvas(matrix);
    led_canvas_clear(canvas);
    for (uint16_t i = 0; i < message->length; ++i) {
        Cell cell = message->cells[i];
        Color8 color = dither(cell.color);
        led_canvas_set_pixel(canvas, cell.point.x, cell.point.y, color.r, color.g, color.b);
    }
}

void render_set_cell(struct RGBLedMatrix* matrix, SetCellMessage* message) {
    struct LedCanvas* canvas = led_matrix_get_canvas(matrix);
    Cell cell = message->cell;
    Color8 color = dither(cell.color);
    led_canvas_set_pixel(canvas, cell.point.x, cell.point.y, color.r, color.g, color.b);

}

void render_player_count(struct RGBLedMatrix* matrix, PlayerCountMessage* message) {
    if (message->count == 0) {
        struct LedCanvas* canvas = led_matrix_get_canvas(matrix);
        led_canvas_clear(canvas);    
    }
}

void render_draw_cells(struct RGBLedMatrix* matrix, DrawCellsMessage* message) {
    struct LedCanvas* canvas = led_matrix_get_canvas(matrix);
    for (uint16_t i = 0; i < message->length; ++i) {
        Point point = message->points[i];
        Color8 color = dither(message->color);
        led_canvas_set_pixel(canvas, point.x, point.y, color.r, color.g, color.b);
    }
}

void render_message(struct RGBLedMatrix* matrix, Message message) {
    switch (message.type) {
        case MESSAGE_UPDATE:
            render_update(matrix, (UpdateMessage*)message.data);
            break;
        case MESSAGE_SET_CELL:
            render_set_cell(matrix, (SetCellMessage*)message.data);
            break;
        case MESSAGE_PLAYER_COUNT:
            render_player_count(matrix, (PlayerCountMessage*)message.data);
            break;
        case MESSAGE_DRAW_CELLS:
            render_draw_cells(matrix, (DrawCellsMessage*)message.data);
            break;
    }
}

typedef struct {
    uint8_t r, g, b;
} Color8;

Color8 dither(Color color) {
    Color8 rv;
    float dither = drand48() - 0.5f;
    rv.r = (uint8_t)(256.0f * color.r + dither);
    rv.g = (uint8_t)(256.0f * color.g + dither);
    rv.b = (uint8_t)(256.0f * color.b + dither);
    return rv;
}