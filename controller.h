#ifndef __CONTROLLER__
#define __CONTROLLER__

#include <gtk/gtk.h>

#include "view.h"
#include "model.h"


//structure definition
typedef struct Controller_t Controller;

//constructor
Controller* build_controller(Model* mod, View* view);

//accessors - getters
GtkWidget* get_boardButton(Controller* con, unsigned int i, unsigned int j);

//callbacks
void click_piece(GtkWidget* button, gpointer data);
void start_new_game(GtkWidget* item, gpointer data);
void quit_game(GtkWidget* item, gpointer data);
void display_about(GtkWidget* item, gpointer data);
void click_choice_bishow(GtkWidget* button, gpointer data);
void click_choice_knight(GtkWidget* button, gpointer data);
void click_choice_tower(GtkWidget* button, gpointer data);
void click_choice_queen(GtkWidget* button, gpointer data);

#endif
