#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "socket.h"
#include "protocol.h"

Client open_socket(char* host, char* service) {
    
    Client client;

    memset(&client.hints, 0, sizeof client.hints);
    client.hints.ai_family = AF_UNSPEC;
    client.hints.ai_socktype = SOCK_DGRAM;

    int rv;

    if ((rv = getaddrinfo(host, service, &client.hints, &client.servinfo)) != 0) {
        perror("getaddrinfo");
        exit(1);
    }

    for (client.p = client.servinfo; client.p != NULL; client.p = client.p->ai_next) {
        if ((client.fd = socket(client.p->ai_family, client.p->ai_socktype, client.p->ai_protocol)) == -1) {
            perror("socket()");
            continue;
        }
        break;
    }

    if (client.p == NULL) {
        fprintf(stderr, "failed to open socket\n");
        exit(1);
    }

    return client;
}

void send_status(Client client, bool status) {
    uint8_t val = status;
    if (sendto(client.fd, &val, sizeof(val), 0, client.p->ai_addr, client.p->ai_addrlen) == -1) {
        perror("sendto()");
    }
}

static char BUFFER[4096];

Message receive_message(Client client) {
    
    ssize_t rv;
    
    if ((rv = recvfrom(client.fd, BUFFER, sizeof(BUFFER) - 1, 0, NULL, NULL)) == -1) {
        perror("recvfrom()");
        Message msg;
        msg.type = MESSAGE_NONE;
        msg.data = NULL;
        return msg;
    }
    
    return read_message(BUFFER);
}

void close_socket(Client client) {
    freeaddrinfo(client.servinfo);
    shutdown(client.fd, SHUT_RDWR);
    close(client.fd);
}
