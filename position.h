#ifndef __POSITION__
#define __POSITION__

typedef struct List_t List;
typedef List Cell;

//costructor - destructor
List* empty_list(void);
Cell* create_cell(unsigned int row, unsigned int col);
void destroy_list(List* position);

//accessors : getters
unsigned int get_row(List* position);
unsigned int get_col(List* position);

//functions
List* push(List* position, unsigned int row, unsigned int col);
List* get_nextCell(List* position);

//for tests
void display_list(List* position);

#endif
