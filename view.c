#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <assert.h>

#include "view.h"
#include "model.h"
#include "controller.h"

#define BOARD_LENGTH 8

struct View_t{
	Model* mod;
	GtkWidget*** imageBoardButton;
	GtkWidget* labelMessage;
};

View* build_view(Model* mod){
	assert(mod != NULL);

	View* view = malloc(sizeof(View));
	if(view == NULL)
		return NULL;

	view->imageBoardButton = malloc(BOARD_LENGTH * sizeof(GtkWidget**));
	if(view->imageBoardButton == NULL){
		free(view);
		return NULL;
	}

	unsigned int i, j;

	for(i = 0; i < BOARD_LENGTH; i++){
		view->imageBoardButton[i] = malloc(BOARD_LENGTH * sizeof(GtkWidget*));
		if(view->imageBoardButton[i] == NULL){
			for(j = 0; j < i; j++){
				free(view->imageBoardButton[j]);
			}
			free(view->imageBoardButton);
			free(view);
			return NULL;
		}
	}

	//initialisation of fields
	for(i = 0; i < BOARD_LENGTH; i++){
		for(j = 0; j < BOARD_LENGTH; j++){
			view->imageBoardButton[i][j] =
			   gtk_image_new_from_file("icon/white.png");
		}
	}

	view->labelMessage = gtk_label_new("");
	view->mod = mod;

	return view;
}

void destroy_view(View* view){
	assert(view != NULL);
	destroy_model(view->mod);
}

//accessors - getters
GtkWidget* get_imageBoardButton(View* view, unsigned int i, unsigned int j){
	assert(view != NULL);
	return view->imageBoardButton[i][j];
}

GtkWidget* get_labelMessage(View* view){
	assert(view != NULL);
	return view->labelMessage;
}

//accessors - setters
void set_labelMessage(View* view, char* message){
	assert(view != NULL);
	gtk_label_set_text(GTK_LABEL(view->labelMessage), message);
}

//functions
void set_imageBoardButton(View* view){
	assert(view != NULL);

	unsigned int i, j;
	for(i = 0; i < BOARD_LENGTH; i++){
		for(j = 0; j < BOARD_LENGTH; j++){

			switch(get_piece(view->mod, i, j)){
				case empty :
					if(get_colorCase(view->mod, i, j) == blue)
						gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(view,
						   i, j)), "icon/blue.png");

					else if(get_colorCase(view->mod, i, j) == green)
						gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(view,
						   i, j)), "icon/green.png");

					else
						gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(view,
						   i, j)), "icon/white.png");

					break;

				case pawn :
					if(get_colorCase(view->mod, i, j) == blue){
						if(get_colorPiece(view->mod, i, j) == white)
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/bw_pawn.png");
						else
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/bb_pawn.png");

					}

					else if(get_colorCase(view->mod, i, j) == green){
						if(get_colorPiece(view->mod, i, j) == white)
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/gw_pawn.png");
						else
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/gb_pawn.png");
               }

					else{
						if(get_colorPiece(view->mod, i, j) == white)
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/ww_pawn.png");
						else
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/wb_pawn.png");
					}

					break;

				case bishow :
					if(get_colorCase(view->mod, i, j) == blue){
						if(get_colorPiece(view->mod, i, j) == white)
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/bw_bishow.png");
						else
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/bb_bishow.png");
					}

					else if(get_colorCase(view->mod, i, j) == green){
						if(get_colorPiece(view->mod, i, j) == white)
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/gw_bishow.png");
						else
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/gb_bishow.png");
					}

					else{
						if(get_colorPiece(view->mod, i, j) == white)
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/ww_bishow.png");
						else
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/wb_bishow.png");
					}

					break;

				case knight :
					if(get_colorCase(view->mod, i, j) == blue){
						if(get_colorPiece(view->mod, i, j) == white)
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/bw_knight.png");
						else
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/bb_knight.png");

					}

					else if(get_colorCase(view->mod, i, j) == green){
						if(get_colorPiece(view->mod, i, j) == white)
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/gw_knight.png");
						else
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/gb_knight.png");
               }

					else{
						if(get_colorPiece(view->mod, i, j) == white)
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/ww_knight.png");
						else
							gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
								view, i, j)), "icon/wb_knight.png");
					}

					break;

				case tower :
				   if(get_colorCase(view->mod, i, j) == blue){
					   if(get_colorPiece(view->mod, i, j) == white)
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/bw_tower.png");
					   else
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/bb_tower.png");

				   }

				   else if(get_colorCase(view->mod, i, j) == green){
					   if(get_colorPiece(view->mod, i, j) == white)
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/gw_tower.png");
					   else
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/gb_tower.png");
				   }

				   else{
					   if(get_colorPiece(view->mod, i, j) == white)
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/ww_tower.png");
					   else
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/wb_tower.png");
				   }

				break;

				   case queen :
				   if(get_colorCase(view->mod, i, j) == blue){
					   if(get_colorPiece(view->mod, i, j) == white)
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/bw_queen.png");
					   else
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/bb_queen.png");

				   }

				   else if(get_colorCase(view->mod, i, j) == green){
					   if(get_colorPiece(view->mod, i, j) == white)
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/gw_queen.png");
					   else
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/gb_queen.png");
				   }

				   else{
					   if(get_colorPiece(view->mod, i, j) == white)
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/ww_queen.png");
					   else
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/wb_queen.png");
				   }

				   break;

				case king :
				   if(get_colorCase(view->mod, i, j) == blue){
					   if(get_colorPiece(view->mod, i, j) == white)
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/bw_king.png");
					   else
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/bb_king.png");

				   }

				   else if(get_colorCase(view->mod, i, j) == green){
					   if(get_colorPiece(view->mod, i, j) == white)
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/gw_king.png");
					   else
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/gb_king.png");
				   }

				   else{
					   if(get_colorPiece(view->mod, i, j) == white)
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/ww_king.png");
					   else
						   gtk_image_set_from_file(GTK_IMAGE(get_imageBoardButton(
							   view, i, j)), "icon/wb_king.png");
				   }

				   break;

				   default :
					   return;
			}
		}
	}
}

void display_popup(void){
	GtkWidget* popup;
   GtkWidget* label;
   label =
   gtk_label_new("(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ Wiwi-chan - 11/07/2016 ✧ﾟ･: *ヽ(◕ヮ◕ヽ)");

   popup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_position(GTK_WINDOW(popup), GTK_WIN_POS_CENTER);
   gtk_window_set_default_size(GTK_WINDOW(popup), 450, 50);

   gtk_container_add(GTK_CONTAINER(popup), label);
	gtk_widget_show_all(popup);
}

void display_choice(Controller* con, Color colorPiece){
	assert(con != NULL);

	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(window), "Choice");
   gtk_window_set_default_size(GTK_WINDOW(window), 1, 1);
   gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
   gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

   GtkWidget* table;
   GtkWidget* button[4];

   //icons
   GtkWidget* b_bishow = gtk_image_new_from_file("icon/b_bishow.png");
   GtkWidget* w_bishow = gtk_image_new_from_file("icon/w_bishow.png");
   GtkWidget* b_knight = gtk_image_new_from_file("icon/b_knight.png");
   GtkWidget* w_knight = gtk_image_new_from_file("icon/w_knight.png");
   GtkWidget* b_tower = gtk_image_new_from_file("icon/b_tower.png");
   GtkWidget* w_tower = gtk_image_new_from_file("icon/w_tower.png");
   GtkWidget* b_queen = gtk_image_new_from_file("icon/b_queen.png");
   GtkWidget* w_queen = gtk_image_new_from_file("icon/w_queen.png");

   //definition of buttons
  if(colorPiece == white){

  		button[0] = gtk_button_new();
   	gtk_button_set_image(GTK_BUTTON(button[0]), w_bishow);
   	g_signal_connect(G_OBJECT(button[0]), "clicked",
      G_CALLBACK(click_choice_bishow), con);

      button[1] = gtk_button_new();
   	gtk_button_set_image(GTK_BUTTON(button[1]), w_knight);
   	g_signal_connect(G_OBJECT(button[1]), "clicked",
      G_CALLBACK(click_choice_knight), con);

      button[2] = gtk_button_new();
   	gtk_button_set_image(GTK_BUTTON(button[2]), w_tower);
   	g_signal_connect(G_OBJECT(button[2]), "clicked",
      G_CALLBACK(click_choice_tower), con);

      button[3] = gtk_button_new();
   	gtk_button_set_image(GTK_BUTTON(button[3]), w_queen);
   	g_signal_connect(G_OBJECT(button[3]), "clicked",
      G_CALLBACK(click_choice_queen), con);
  }

	else{

		button[0] = gtk_button_new();
   	gtk_button_set_image(GTK_BUTTON(button[0]), b_bishow);
   	g_signal_connect(G_OBJECT(button[0]), "clicked",
      G_CALLBACK(click_choice_bishow), con);

      button[1] = gtk_button_new();
   	gtk_button_set_image(GTK_BUTTON(button[1]), b_knight);
   	g_signal_connect(G_OBJECT(button[1]), "clicked",
      G_CALLBACK(click_choice_knight), con);

      button[2] = gtk_button_new();
   	gtk_button_set_image(GTK_BUTTON(button[2]), b_tower);
   	g_signal_connect(G_OBJECT(button[2]), "clicked",
      G_CALLBACK(click_choice_tower), con);

      button[3] = gtk_button_new();
   	gtk_button_set_image(GTK_BUTTON(button[3]), b_queen);
   	g_signal_connect(G_OBJECT(button[3]), "clicked",
      G_CALLBACK(click_choice_queen), con);
	}

	table = gtk_table_new(1, 4, TRUE);
	gtk_table_attach_defaults(GTK_TABLE(table), button[0]
      , 0, 1, 0, 1);
   gtk_table_attach_defaults(GTK_TABLE(table), button[1]
      , 1, 2, 0, 1);
   gtk_table_attach_defaults(GTK_TABLE(table), button[2]
      , 2, 3, 0, 1);
   gtk_table_attach_defaults(GTK_TABLE(table), button[3]
      , 3, 4, 0, 1);

   gtk_container_add(GTK_CONTAINER(window), table);

   gtk_widget_show_all(window);
}
