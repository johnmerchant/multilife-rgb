#include "stddef.h"
#include "protocol.h"

Message read_message(char* buffer) {
    Message message;
    switch (message.type = buffer[0]) {
        case MESSAGE_UPDATE:
        case MESSAGE_SET_CELL:
        case MESSAGE_PLAYER_COUNT:
        case MESSAGE_DRAW_CELLS:
            message.data = buffer + 1;
            break;
        default:
            message.type = MESSAGE_NONE;
            message.data = NULL;
            break;
    }
    return message;
}