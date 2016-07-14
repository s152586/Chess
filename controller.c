#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <assert.h>

#include "model.h"
#include "view.h"
#include "controller.h"
#include "functions.h"

#define BOARD_LENGTH 8

// structure definition
struct Controller_t{
	Model* mod;
	View* view;
	GtkWidget*** boardButton;
};

Controller* build_controller(Model* mod, View* view){
	assert(mod != NULL && view != NULL);

	Controller* con = malloc(sizeof(Controller));
	if(con == NULL)
		return NULL;

	con->boardButton = malloc(BOARD_LENGTH * sizeof(GtkWidget**));
	if(con->boardButton == NULL){
		free(con);
		return NULL;
	}

	unsigned int i, j;
	for(i = 0; i < BOARD_LENGTH; i++){
		con->boardButton[i] = malloc(BOARD_LENGTH * sizeof(GtkWidget*));
		if(con->boardButton[i] == NULL){
			for(j = 0; j < i; j++){
				free(con->boardButton[j]);
			}
			free(con->boardButton);
			free(con);
			return NULL;
		}
	}

	//initialisation of fields
	con->mod = mod;
	con->view = view;

	for(i = 0; i < BOARD_LENGTH; i++){
		for(j = 0; j < BOARD_LENGTH; j++){
			con->boardButton[i][j] = gtk_button_new();
			gtk_button_set_relief(GTK_BUTTON(con->boardButton[i][j]),
			   GTK_RELIEF_NORMAL);
			gtk_button_set_image(GTK_BUTTON(con->boardButton[i][j]),
		      get_imageBoardButton(con->view, i, j));
		}
	}

	return con;
}


//accessors - getters
GtkWidget* get_boardButton(Controller* con, unsigned int i, unsigned int j){
	assert(con != NULL);
	return con->boardButton[i][j];
}

//prototype 
static void check_case_stalemate_checkmate(Controller* con);

void click_piece(GtkWidget* button, gpointer data){
	assert(button != NULL && data != NULL);

	Controller* con = (Controller*) data;

	//select a piece ***********************************************************

	if(!(get_click(con->mod))){

		unsigned int i, j;

		//get the position of the piece selected
		for(i = 0; i < BOARD_LENGTH; i++){
			for(j = 0; j < BOARD_LENGTH; j++){
				if(button == con->boardButton[i][j]){
					set_current_row(con->mod, i);
					set_current_col(con->mod, j);
					break;
				}
			}
		}

		//check the color of the piece with the round
		if(get_colorPiece(con->mod, get_current_row(con->mod),
		   get_current_col(con->mod)) != get_colorRound(con->mod)){
				return;
		}

		//stock the possible position in the linked list position 
		List* position = next_positions(con->mod, get_current_row(con->mod),
	      get_current_col(con->mod));

		//check the possible position with stalemate
		position = check_next_positions(con->mod, position);

		//set the case of the possible positions in green
		set_color_next_positions(con->mod, position);

		//in case of the king is selected, we check if we can castle
		if(get_piece(con->mod, get_current_row(con->mod),
		   get_current_col(con->mod)) == king){

			position = check_castle_position(con->mod, position);
			position = check_next_positions(con->mod, position);
			set_color_next_positions(con->mod, position);
		}

		set_list(con->mod, position);

		//refresh the chessboard
		set_imageBoardButton(con->view);

		//next click will be for selecting the position, of the piece selected
		set_click(con->mod, true);
	}

	//select a position *********************************************************

   else{

	   unsigned int i, j;

	   //get the position of the piece selected
	   for(i = 0; i < BOARD_LENGTH; i++){
		   for(j = 0; j < BOARD_LENGTH; j++){
			   if(button == con->boardButton[i][j]){
				   set_next_row(con->mod, i);
				   set_next_col(con->mod, j);
				   //if a piece reach the limit and turn into queen, it checks if 
				   //there is a stalemate/checkamte and if yes, it changes
				   //next->row and next->col. so there is a problem if we click on 
				   //differents button to choose the piece that will replace the 
				   //pawn
				   set_choice_row(con->mod, i);
				   set_choice_col(con->mod, j);
				   break;
			   }
		   }
	   }

	   //click on the piece of the same color ***********************************

	   if(get_colorPiece(con->mod, get_next_row(con->mod), get_next_col(con->mod))
         == get_colorPiece(con->mod, get_current_row(con->mod),
		   get_current_col(con->mod))){

         List* position = get_list(con->mod);

		   retrieve_color_next_positions(con->mod, position);
		   set_imageBoardButton(con->view);

		   destroy_list(position);

		   //the piece selected, will be the piece we want to move next click
			set_current_row(con->mod, get_next_row(con->mod));
			set_current_col(con->mod, get_next_col(con->mod));

		   position = next_positions(con->mod, get_current_row(con->mod),
		      get_current_col(con->mod));

		   position = check_next_positions(con->mod, position);
         set_color_next_positions(con->mod, position);
         
         if(get_piece(con->mod, get_current_row(con->mod),
            get_current_col(con->mod)) == king){

            position = check_castle_position(con->mod, position);
            position = check_next_positions(con->mod, position);
            set_color_next_positions(con->mod, position);
         }

		   set_list(con->mod, position);

		   set_imageBoardButton(con->view);

		   return;
	   }

		//click on an empty piece or an opposing piece ***************************

		else{
			List* position = get_list(con->mod);

			//the position is allowed *********************************************

			//the position is stocked in the linked list of possible position
			if(check_possible_position(con->mod, position)){

				//check if the piece we want to move is tower or a king
				set_castle_indicator(con->mod);

				//move the piece, update the board
				permute_1(con->mod);

				//castle move
				check_castle(con->mod);

				//if a pawn reach the limit
				if(check_pawn_last_line(con->mod)){
					display_choice(con, get_colorRound(con->mod));
					set_imageBoardButton(con->view);
				}

				retrieve_color_next_positions(con->mod, position);
				set_imageBoardButton(con->view);
				destroy_list(position);

				//round change
				set_colorRound(con->mod, !(get_colorRound(con->mod)));

            //check if the piece are in stalemate or checkmate
				check_case_stalemate_checkmate(con);
				set_click(con->mod, false);
			}

			//position not allowed
			else
				return;
		}
   }

}

static void check_case_stalemate_checkmate(Controller* con){
	if(check_stalemate_v1(con->mod, get_next_row(con->mod),
		get_next_col(con->mod))){

		set_stalemate(con->mod, true);

		if(check_checkmate(con->mod)){
			if(get_colorRound(con->mod) == black)
				set_labelMessage(con->view, "checkmate - white win");
			else
				set_labelMessage(con->view, "checkmate - black win");
		}
		else
			set_labelMessage(con->view, "stalemate");
	}

	else{
		set_labelMessage(con->view, "");
		set_stalemate(con->mod, false);

	}
}

void start_new_game(GtkWidget* item, gpointer data){
	assert(item != NULL && data != NULL);
	Controller* con = (Controller*) data;
	initialisation_chessboard(con->mod);

	set_imageBoardButton(con->view);
	set_labelMessage(con->view, "");
}

void quit_game(GtkWidget* item, gpointer data){
	assert(item != NULL && data != NULL);
	gtk_main_quit();
}

void display_about(GtkWidget* item, gpointer data){
	assert(item != NULL && data != NULL);
	display_popup();
}

void click_choice_bishow(GtkWidget* button, gpointer data){
	assert(button != NULL && data != NULL);
	Controller* con = (Controller*) data;

	set_piece(con->mod, get_choice_row(con->mod), get_choice_col(con->mod), 
		bishow);
	set_imageBoardButton(con->view); 

	check_case_stalemate_checkmate(con);
}

void click_choice_knight(GtkWidget* button, gpointer data){
	assert(button != NULL && data != NULL);
	Controller* con = (Controller*) data;

	set_piece(con->mod, get_choice_row(con->mod), get_choice_col(con->mod), 
		knight);
   set_imageBoardButton(con->view);

   check_case_stalemate_checkmate(con);
}

void click_choice_tower(GtkWidget* button, gpointer data){
	assert(button != NULL && data != NULL);
	Controller* con = (Controller*) data;

	set_piece(con->mod, get_choice_row(con->mod), get_choice_col(con->mod), 
		tower);
	set_imageBoardButton(con->view);


	check_case_stalemate_checkmate(con);
}

void click_choice_queen(GtkWidget* button, gpointer data){
	assert(button != NULL && data != NULL);
	Controller* con = (Controller*) data;

	set_piece(con->mod, get_choice_row(con->mod), get_choice_col(con->mod), 
		queen);
	set_imageBoardButton(con->view);

	check_case_stalemate_checkmate(con);
}