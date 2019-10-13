#include "protocol.h"
#include "led-matrix-c.h"

struct RGBLedMatrix* init_matrix(int* argc, char*** argv);
void render_message(struct RGBLedMatrix* matrix, Message message);