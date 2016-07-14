#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "position.h"
#include "model.h"

struct List_t{
	unsigned int row;
	unsigned int col;
	Cell* next;
};

//constructor - destructor
List* empty_list(void){
	return NULL;
}

Cell* create_cell(unsigned int row, unsigned int col){
	Cell* c = malloc(sizeof(Cell));
	if(c == NULL){
		return NULL;
	}
	c->row = row;
	c->col = col;
	c->next = NULL;

	return c;
}

void destroy_list(List* position){
	if(position != NULL)
		return;

	List* tmp;
	while(position != NULL){
		tmp = position;
		position = position->next;
		free(tmp);
	}
}

//accessors
unsigned int get_row(List* position){
	assert(position != NULL);
	return position->row;
}

unsigned int get_col(List* position){
	assert(position != NULL);
	return position->col;
}

//functions
List* push(List* position, unsigned int i, unsigned int j){
	Cell* c = create_cell(i, j);
	c->next = position;
	return c;
}

List* get_nextCell(List* position){
	assert(position != NULL);
	return position->next;
}

void display_list(List* position){
	if(position == NULL){
      printf("(  ;  )\n");
	   return;
	}

	while(position != NULL){
		printf("(%u ; %u) ", position->row, position->col);
		position = position->next;
	}
	printf("\n");
}
