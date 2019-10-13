#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "loop.h"
#include "matrix.h"

int main(int argc, char **argv) {

    if (argc < 3) {
        printf("multilife requires 2 args: host and port\n");
        return EXIT_FAILURE;
    }
    Client client = open_socket(argv[1], argv[2]);

    if (socket == 0) {
        printf("Failed to connect\n");
        return EXIT_FAILURE;
    }

    struct RGBLedMatrix* matrix = init_matrix(&argc, &argv);
    event_loop(client, matrix);
    close_socket(client);
    led_matrix_delete(matrix);

    return EXIT_SUCCESS;
}