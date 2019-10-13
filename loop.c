#include <stdio.h>
#include <stdbool.h>
#include <signal.h>

#include "socket.h"
#include "protocol.h"
#include "matrix.h"

volatile bool run_loop = true;

void interrupt_loop(int sig) {
    run_loop = false;
}

void event_loop(Client client, struct RGBLetMatrix* matrix) {
    
    int sigint_handler = signal(SIGINT, interrupt_loop);

    while (run_loop) {
        send_status(client, true);
        render_message(matrix, receive_message(client));
    }

    send_status(client, false);
    signal(SIGINT, sigint_handler);
}