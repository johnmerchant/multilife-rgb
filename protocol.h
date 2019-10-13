#include <stdint.h>
#include <stdbool.h>

#define MESSAGE_NONE 0
#define MESSAGE_UPDATE 1
#define MESSAGE_SET_CELL 2
#define MESSAGE_PLAYER_COUNT 5
#define MESSAGE_DRAW_CELLS 6

typedef struct {
    uint8_t type;
    void* data;
} Message;

Message read_message(char* buffer);
void free_message(Message message);

typedef struct {
    uint8_t x;
    uint8_t y;
} Point;

typedef struct {
    uint32_t r;
    uint32_t g;
    uint32_t b;
} Color;

typedef struct {
    Point point;
    Color color;
} Cell;

typedef struct {
    uint16_t length;
    Cell* cells;
} UpdateMessage;

typedef struct {
    bool alive;
    Cell cell;
} SetCellMessage;

typedef struct {
    uint32_t count;
} PlayerCountMessage;

typedef struct {
    uint8_t length;
    Color color;
    Point* points;    
} DrawCellsMessage;
