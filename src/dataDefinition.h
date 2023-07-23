//dataDefinition.h
#define VALID 1
#define INVALID 0

#define ACTIVE 1
#define INACTIVE 0

typedef struct data {
    char date[9];
    char amount[14];
    char to[31];
    char comment[101];
} Record;

typedef struct recordList {
    Record rec;
    struct recordList *next;
} List;

