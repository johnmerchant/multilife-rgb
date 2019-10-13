#include <netdb.h>
#include <stdbool.h>
#include "protocol.h"

typedef struct {
    int fd;
    struct addrinfo hints, *servinfo, *p;
} Client;

Client open_socket(char* host, char* service);
void send_status(Client client, bool status);
Message receive_message(Client client);
void close_socket(Client client);