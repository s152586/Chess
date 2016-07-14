#ifndef __VIEW__
#define __VIEW__

#include <gtk/gtk.h>

#include "model.h"

//structure definition
typedef struct View_t View;
typedef struct Controller_t Controller_s;

//constructor
View* build_view(Model* mod);
void destroy_view(View* view);

//accessors - getters
GtkWidget* get_imageBoardButton(View* view, unsigned int i, unsigned int j);
GtkWidget* get_labelMessage(View* view);

//functions
void set_imageBoardButton(View* view);
void set_labelMessage(View* view, char* message);
void display_popup(void);
void display_choice(Controller_s* con, Color colorPiece);

#endif
