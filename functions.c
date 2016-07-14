#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "model.h"
#include "position.h"
#include "functions.h"

#define BOARD_LENGTH 8

/*******************************************************************************
********************  initialisation chessboard functions **********************
*******************************************************************************/

static void initialisation_piece(Model* mod){
	assert(mod != NULL);

	//pawns
	unsigned int i;
	for(i = 0; i < BOARD_LENGTH; i++){
		set_piece(mod, 1, i, pawn);
	}
	for(i = 0; i < BOARD_LENGTH; i++){
		set_piece(mod, 6, i, pawn);
	}

	//bishows
	set_piece(mod, 0, 2, bishow);
	set_piece(mod, 0, 5, bishow);
	set_piece(mod, 7, 2, bishow);
	set_piece(mod, 7, 5, bishow);

	//knights
	set_piece(mod, 0, 1, knight);
	set_piece(mod, 0, 6, knight);
	set_piece(mod, 7, 1, knight);
	set_piece(mod, 7, 6, knight);

	//towers
	set_piece(mod, 0, 0, tower);
	set_piece(mod, 0, 7, tower);
	set_piece(mod, 7, 0, tower);
	set_piece(mod, 7, 7, tower);

	//queens
	set_piece(mod, 0, 3, queen);
	set_piece(mod, 7, 3, queen);

	//kings
	set_piece(mod, 0, 4, king);
	set_piece(mod, 7, 4, king);

	//empty
	unsigned int j;
	for(i = 2; i < 6; i++){
		for(j = 0; j < BOARD_LENGTH; j++){
			set_piece(mod, i, j, empty);
		}
	}
}

static void initialisation_colorCase(Model* mod){
	assert(mod != NULL);
	unsigned int i;
	unsigned int j;

	for(i = 0; i < BOARD_LENGTH; i++){
		for(j = 0; j < BOARD_LENGTH; j++){
			if((!(i % 2) && !(j % 2)) || ((i % 2) && (j % 2)))
				set_colorCase(mod, i, j, white);
			else
				set_colorCase(mod, i, j, blue);
		}
	}
}

static void initialisation_colorPiece(Model* mod){
	assert(mod != NULL);
	unsigned int i;
	unsigned int j;

	for(i = 0; i < BOARD_LENGTH; i++){
		for(j = 0; j < BOARD_LENGTH; j++){
			if(i < 2)
				set_colorPiece(mod, i, j, black);                      
			else if(i < 6)
				set_colorPiece(mod, i, j, none);
			else
				set_colorPiece(mod, i, j, white);
		}
	}
}

void initialisation_chessboard(Model* mod){
	assert(mod != NULL);

	//initialisation of elements of the model
	set_whiteLeft(mod, 16);
	set_blackLeft(mod, 16);
	set_list(mod, NULL);
	set_stalemate(mod, false);
	set_colorRound(mod, white);
	set_click(mod, false);
	set_white_castle_indicator(mod, false);
	set_white_castle_kingCheck(mod, false);
	set_white_castle_leftTowerCheck(mod, false);
	set_white_castle_rightTowerCheck(mod, false);
	set_black_castle_indicator(mod, false);
	set_black_castle_kingCheck(mod, false);
	set_black_castle_leftTowerCheck(mod, false);
	set_black_castle_rightTowerCheck(mod, false);

	initialisation_colorPiece(mod);
	initialisation_piece(mod);
	initialisation_colorCase(mod);
}

Color get_initial_colorCase(unsigned int i, unsigned int j){
	if((!(i % 2) && !(j % 2)) || ((i % 2) && (j % 2)))
		return white;
	else
		return blue;
}





/*******************************************************************************
*************************  pieces moves functions  *****************************
*******************************************************************************/

static Boolean check_position(int i, int j){
	if((i >= 0 && i <= 7) && (j >= 0 && j <= 7))
		return true;
	else return false;
}

static Boolean check_piece_v1(Model* mod, Color colorPiece, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	if(get_piece(mod, i, j) == empty)
		return true;

	else if(get_colorPiece(mod, i, j) != colorPiece)
		return true;

	else
		return false;
}

static Boolean check_piece_v2(Model* mod, unsigned int i, unsigned int j){
	assert(mod != NULL);

	if(get_piece(mod, i, j) == empty)
		return true;
	else 
		return false;
}

//pawn moves *******************************************************************

static List* move_whitePawn_vertical(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	if(i != 0 && get_piece(mod, i - 1, j) == empty)
			position = push(position, i - 1, j);

	if(i == 6 && get_piece(mod, i - 2, j) == empty)
		position = push(position, i - 2, j);

	return position;
}

static List* move_blackPawn_vertical(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	if(i != 7 && get_piece(mod, i + 1, j) == empty)
			position = push(position, i + 1, j);

	if(i == 1 && get_piece(mod, i + 2, j) == empty)
		position = push(position, i + 2, j);

	return position;
}

static List* move_whitePawn_diagonal_right(Model* mod, List* position,
	unsigned int i, unsigned int j){
	assert(mod != NULL);

	if(i != 0 && get_piece(mod, i - 1, j + 1) != empty &&
		get_colorPiece(mod, i - 1, j + 1) == black){

		position = push(position, i - 1, j + 1);
	}
	return position;
}

static List* move_whitePawn_diagonal_left(Model* mod, List* position,
	unsigned int i, unsigned int j){
	assert(mod != NULL);

	if(i != 0 && get_piece(mod, i - 1, j - 1) != empty &&
		get_colorPiece(mod, i - 1, j - 1) == black){
		position = push(position, i - 1, j - 1);
	}
	return position;
}

static List* move_whitePawn_diagonal(Model* mod, List* position, unsigned int i,
   unsigned int j){
	assert(mod != NULL);

	if(j == 0)
		position = move_whitePawn_diagonal_right(mod, position, i, j);

	else if(j == 7)
		position = move_whitePawn_diagonal_left(mod, position, i, j);

	else{
		position = move_whitePawn_diagonal_right(mod, position, i, j);
		position = move_whitePawn_diagonal_left(mod, position, i, j);
	}

	return position;
}

static List* move_blackPawn_diagonal_right(Model* mod, List* position,
	unsigned int i, unsigned int j){
	assert(mod != NULL);

	if(i != 7 && get_piece(mod, i + 1, j + 1) != empty &&
		get_colorPiece(mod, i + 1, j + 1) == white){

		position = push(position, i + 1, j + 1);
	}
	return position;
}

static List* move_blackPawn_diagonal_left(Model* mod, List* position,
	unsigned int i, unsigned int j){
	assert(mod != NULL);

	if(i != 7 && get_piece(mod, i + 1, j - 1) != empty &&
		get_colorPiece(mod, i + 1, j - 1) == white){
		position = push(position, i + 1, j - 1);
	}
	return position;
}

static List* move_blackPawn_diagonal(Model* mod, List* position, unsigned int i,
   unsigned int j){
	assert(mod != NULL);

	if(j == 0)
		position = move_blackPawn_diagonal_right(mod, position, i, j);

	else if(j == 7)
		position = move_blackPawn_diagonal_left(mod, position, i, j);

	else{
		position = move_blackPawn_diagonal_right(mod, position, i, j);
		position = move_blackPawn_diagonal_left(mod, position, i, j);
	}

	return position;
}

static List* move_pawn(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	Color colorPiece = get_colorPiece(mod, i, j);

	//move of the pawn depends on the color of the piece
	if(colorPiece == white){
		position = move_whitePawn_vertical(mod, position, i, j);
		position = move_whitePawn_diagonal(mod, position, i, j);
	}

	else{
		position = move_blackPawn_vertical(mod, position, i, j);
		position = move_blackPawn_diagonal(mod, position, i, j);
	}

	return position;
}

//bishow moves *****************************************************************

static List* move_bishow_up_right(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);
	Color colorPiece = get_colorPiece(mod, i, j);

	int k = i;
	//first position
	k--;
	j++;

	while(k >= 0 && j < BOARD_LENGTH){
		if(get_piece(mod, k, j) == empty)
			position = push(position, k, j);

		else if(get_colorPiece(mod, k, j) != colorPiece){
			position = push(position, k, j);
			return position;
		}

		else
			return position;

		k--;
		j++;
	}

	return position;
}

static List* move_bishow_down_right(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);
	Color colorPiece = get_colorPiece(mod, i, j);

	//first position
	i++;
	j++;

	while(i < BOARD_LENGTH && j < BOARD_LENGTH){
		if(get_piece(mod, i, j) == empty)
			position = push(position, i, j);

		else if(get_colorPiece(mod, i, j) != colorPiece){
			position = push(position, i, j);
			return position;
		}

		else
			return position;

		i++;
		j++;
	}

	return position;
}

static List* move_bishow_up_left(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);
	Color colorPiece = get_colorPiece(mod, i, j);

	int k = i;
	int l = j;
	//first position
	k--;
	l--;

	while(k >= 0 && l >= 0){
		if(get_piece(mod, k, l) == empty)
			position = push(position, k, l);

		else if(get_colorPiece(mod, k, l) != colorPiece){
			position = push(position, k, l);
			return position;
		}

		else
			return position;

		k--;
		l--;
	}

	return position;
}

static List* move_bishow_down_left(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);
	Color colorPiece = get_colorPiece(mod, i, j);

	int k = j;
	//first position
	i++;
	k--;

	while(i < BOARD_LENGTH && k >= 0){
		if(get_piece(mod, i, k) == empty)
			position = push(position, i, k);

		else if(get_colorPiece(mod, i, k) != colorPiece){
			position = push(position, i, k);
			return position;
		}

		else
			return position;

		i++;
		k--;
	}

	return position;
}

static List* move_bishow(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	position = move_bishow_up_right(mod, position, i, j);
	position = move_bishow_down_right(mod, position, i, j);
	position = move_bishow_up_left(mod, position, i, j);
	position = move_bishow_down_left(mod, position, i, j);

	return position;
}

//knight moves *****************************************************************


static List* move_knight(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	Color colorPiece = get_colorPiece(mod, i, j);

	int k = i;
	int l = j;

	//8 possible positions
	if(check_position(k - 2, l + 1)){
		if(check_piece_v1(mod, colorPiece, i - 2, j + 1))
			position = push(position, i - 2, j + 1);
	}

	if(check_position(k - 1, l + 2)){
		if(check_piece_v1(mod, colorPiece, i - 1, j + 2))
			position = push(position, i - 1, j + 2);
	}

	if(check_position(k + 1, l + 2)){
		if(check_piece_v1(mod, colorPiece, i + 1, j + 2))
			position = push(position, i + 1, j + 2);
	}

	if(check_position(k + 2, l + 1)){
		if(check_piece_v1(mod, colorPiece, i + 2, j + 1))
			position = push(position, i + 2, j + 1);
	}

	if(check_position(k + 2, l - 1)){
		if(check_piece_v1(mod, colorPiece, i + 2, j - 1))
			position = push(position, i + 2, j - 1);
	}

	if(check_position(k + 1, l - 2)){
		if(check_piece_v1(mod, colorPiece, i + 1, j - 2))
			position = push(position, i + 1, j - 2);
	}

	if(check_position(k - 1, l - 2)){
		if(check_piece_v1(mod, colorPiece, i - 1, j - 2))
			position = push(position, i - 1, j - 2);
	}

	if(check_position(k - 2, l - 1)){
		if(check_piece_v1(mod, colorPiece, i - 2, j - 1))
			position = push(position, i - 2, j - 1);
	}

	return position;
}

// tower moves *****************************************************************

static List* move_tower_up(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	Color colorPiece = get_colorPiece(mod, i, j);
	int k = i;
	k--;

	while(k >= 0){
		if(get_piece(mod, k, j) == empty)
			position = push(position, k, j);

		else if(get_colorPiece(mod, k, j) != colorPiece){
			position = push(position, k, j);
			return position;
		}

		else
			return position;

		k--;
	}

	return position;
}

static List* move_tower_down(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	Color colorPiece = get_colorPiece(mod, i, j);
	i++;

	while(i < BOARD_LENGTH){
		if(get_piece(mod, i, j) == empty)
			position = push(position, i, j);

		else if(get_colorPiece(mod, i, j) != colorPiece){
			position = push(position, i, j);
			return position;
		}

		else
			return position;

		i++;
	}

	return position;
}

static List* move_tower_right(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	Color colorPiece = get_colorPiece(mod, i, j);
	j++;

	while(j < BOARD_LENGTH){
		if(get_piece(mod, i, j) == empty)
			position = push(position, i, j);

		else if(get_colorPiece(mod, i, j) != colorPiece){
			position = push(position, i, j);
			return position;
		}

		else
			return position;

		j++;
	}

	return position;
}

static List* move_tower_left(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	Color colorPiece = get_colorPiece(mod, i, j);
	int k = j;
	k--;

	while(k >= 0){
		if(get_piece(mod, i, k) == empty)
			position = push(position, i, k);

		else if(get_colorPiece(mod, i, k) != colorPiece){
			position = push(position, i, k);
			return position;
		}

		else
			return position;

		k--;
	}

	return position;
}

static List* move_tower(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	position = move_tower_up(mod, position, i, j);
	position = move_tower_down(mod, position, i, j);
	position = move_tower_right(mod, position, i, j);
	position = move_tower_left(mod, position, i, j);

	return position;
}

// queen moves *****************************************************************

static List* move_queen(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	position = move_tower(mod, position, i, j);
	position = move_bishow(mod, position, i, j);

	return position;
}

//king moves *******************************************************************

List* check_castle_position(Model* mod, List* position){
	assert(mod != NULL);

	Color colorPiece = get_colorRound(mod);

	if(get_stalemate(mod))
			return position;

	if(colorPiece == white){

		//castle aready done
		if(get_white_castle_indicator(mod))
			return position;

		if(!(get_white_castle_kingCheck(mod))){
			//castle right
			if(!(get_white_castle_rightTowerCheck(mod)) &&
			   (get_colorCase(mod, 7, 5) == green) && check_piece_v2(mod, 7, 6)){
				position = push(position, 7, 6);
				return position;
			}

			if(!(get_white_castle_leftTowerCheck(mod)) &&
			   (get_colorCase(mod, 7, 3) == green) && check_piece_v2(mod, 7, 2)){
				position = push(position, 7, 2);
				return position;
			}
		}

		return position;
	}

	else{
		if(get_black_castle_indicator(mod))
			return position;

		if(!(get_black_castle_kingCheck(mod))){
			//castle right
			if(!(get_black_castle_rightTowerCheck(mod)) &&
			   (get_colorCase(mod, 0, 5)) == green && check_piece_v2(mod, 0, 6)){
				position = push(position, 0, 6);
				return position;
			}

			if(!(get_black_castle_leftTowerCheck(mod)) &&
			   (get_colorCase(mod, 0, 3) == green) && check_piece_v2(mod, 0, 2)){
				position = push(position, 0, 2);
				return position;
			}
		}

		return position;
	}	
}

static List* move_king(Model* mod, List* position, unsigned int i,
	unsigned int j){
	assert(mod != NULL);

	// 8 possible positions
	Color colorPiece = get_colorPiece(mod, i, j);

	int k = i;
	int l = j;

	//8 possible positions
	if(check_position(k - 1, l)){
		if(check_piece_v1(mod, colorPiece, i - 1, j))
			position = push(position, i - 1, j);
	}

	if(check_position(k - 1, l + 1)){
		if(check_piece_v1(mod, colorPiece, i - 1, j + 1))
			position = push(position, i - 1, j + 1);
	}

	if(check_position(k, l + 1)){
		if(check_piece_v1(mod, colorPiece, i, j + 1))
			position = push(position, i, j + 1);
	}

	if(check_position(k + 1, l + 1)){
		if(check_piece_v1(mod, colorPiece, i + 1, j + 1))
			position = push(position, i + 1, j + 1);
	}

	if(check_position(k + 1, l)){
		if(check_piece_v1(mod, colorPiece, i + 1, j))
			position = push(position, i + 1, j);
	}

	if(check_position(k + 1, l - 1)){
		if(check_piece_v1(mod, colorPiece, i + 1, j - 1))
			position = push(position, i + 1, j - 1);
	}

	if(check_position(k, l - 1)){
		if(check_piece_v1(mod, colorPiece, i, j - 1))
			position = push(position, i, j - 1);
	}

	if(check_position(k - 1, l - 1)){
		if(check_piece_v1(mod, colorPiece, i - 1, j - 1))
			position = push(position, i - 1, j - 1);
	}

	return position;
}

List* next_positions(Model* mod, unsigned int i, unsigned int j){
	assert(mod != NULL);

	List* position = empty_list();

	switch(get_piece(mod, i, j)){
		case pawn :
			position = move_pawn(mod, position, i, j);
			break;
		case bishow :
			position = move_bishow(mod, position, i, j);
			break;
		case knight :
			position = move_knight(mod, position, i, j);
			break;
		case tower :
			position = move_tower(mod, position, i, j);
			break;
		case queen :
			position = move_queen(mod, position, i, j);
			break;
		case king :
			position = move_king(mod, position, i, j);
			break;
		default :
			position = empty_list();
	}

	return position;
}

Boolean check_stalemate_v1(Model* mod, unsigned int i, unsigned int j){
   assert(mod != NULL);

	List* position = next_positions(mod, i, j);
	List* tmp = position;
	Color colorPiece = get_colorPiece(mod, i, j);

	while(tmp != NULL){
		if((get_piece(mod, get_row(tmp), get_col(tmp)) == king) &&
		   get_colorPiece(mod, get_row(tmp), get_col(tmp)) != colorPiece)
			return true;

		tmp = get_nextCell(tmp);
	}

	destroy_list(position);
	return false;
}

void permute_1(Model* mod){
	assert(mod != NULL);

	set_permutation_piece(mod, get_piece(mod, get_next_row(mod),
	   get_next_col(mod)));

	set_permutation_colorPiece(mod, get_colorPiece(mod, get_next_row(mod),
	   get_next_col(mod)));

	set_piece(mod, get_next_row(mod), get_next_col(mod),
	   get_piece(mod, get_current_row(mod), get_current_col(mod)));

	set_colorPiece(mod, get_next_row(mod), get_next_col(mod),
		get_colorPiece(mod, get_current_row(mod), get_current_col(mod)));

	set_piece(mod, get_current_row(mod), get_current_col(mod), empty);
	set_colorPiece(mod, get_current_row(mod), get_current_col(mod), none);

}

void permute_2(Model* mod){
	assert(mod != NULL);

	set_piece(mod, get_current_row(mod), get_current_col(mod),
	   get_piece(mod, get_next_row(mod), get_next_col(mod)));

	set_colorPiece(mod, get_current_row(mod), get_current_col(mod),
		get_colorPiece(mod, get_next_row(mod), get_next_col(mod)));

	set_piece(mod, get_next_row(mod), get_next_col(mod),
	   get_permutation_piece(mod));

	set_colorPiece(mod, get_next_row(mod), get_next_col(mod),
	   get_permutation_colorPiece(mod));
}

Boolean check_stalemate_v2(Model* mod){
	assert(mod != NULL);

	Color colorPiece = get_colorRound(mod);

	unsigned int nbPieces;
	unsigned int i, j, k;

	if(colorPiece == white)
		nbPieces = get_blackLeft(mod);
	else
		nbPieces = get_whiteLeft(mod);

	k = 0;
	for(i = 0; i < BOARD_LENGTH; i++){
		for(j = 0; j < BOARD_LENGTH && k < nbPieces; j++){

			if(get_piece(mod, i, j) != empty &&
			   get_colorPiece(mod, i, j) != colorPiece){

				if(check_stalemate_v1(mod, i, j)){
					return true;
				}
				k++;
			}
		}
	}

	return false;
}

List* check_next_positions(Model* mod, List* position){
	assert(mod != NULL);

	List* p_current = position;
	List* new_position = empty_list();

	while(p_current != NULL){
		set_next_row(mod, get_row(p_current));
		set_next_col(mod, get_col(p_current));

		permute_1(mod);

		if(!(check_stalemate_v2(mod))){
			new_position = push(new_position ,get_row(p_current),
			   get_col(p_current));
		}

		permute_2(mod);

		p_current = get_nextCell(p_current);
	}

	destroy_list(position);
	return new_position;
}

void set_color_next_positions(Model* mod, List* position){
	assert(mod != NULL);

	List* p_current = position;
	unsigned int i, j;

	while(p_current != NULL){
		for(i = 0; i < BOARD_LENGTH; i++){
			for(j = 0; j < BOARD_LENGTH; j++){

				if(get_row(p_current) == i && get_col(p_current) == j){
					set_colorCase(mod, i, j, green);
				}
			}
		}
		p_current = get_nextCell(p_current);
	}
}

void retrieve_color_next_positions(Model* mod, List* position){
	assert(mod != NULL);

	Color colorCase;
	List* p_current = position;

	while(p_current != NULL){
		colorCase = get_initial_colorCase(get_row(p_current), get_col(p_current));
		set_colorCase(mod, get_row(p_current), get_col(p_current), colorCase);
		p_current = get_nextCell(p_current);
	}
}

Boolean check_checkmate(Model* mod){
	assert(mod != NULL);

	Color colorPiece = get_colorRound(mod);

	unsigned int nbPieces;
	unsigned int i, j, k;
	List* position = empty_list();

	if(colorPiece == white)
		nbPieces = get_whiteLeft(mod);
	else
		nbPieces = get_blackLeft(mod);

	for(i = 0; i < BOARD_LENGTH; i++){
		for(j = 0, k = 0; j < BOARD_LENGTH && k < nbPieces; j++){

			if(get_piece(mod, i, j) != empty &&
			   get_colorPiece(mod, i, j) == colorPiece){

				set_current_row(mod, i);
				set_current_col(mod, j);

				position = next_positions(mod, i, j);
				position = check_next_positions(mod, position);

				if(position != NULL){
					destroy_list(position);
					return false;
				}

				k++;
			}
		}
	}

	return true;
}

Boolean check_possible_position(Model* mod, List* position){
	assert(mod != NULL);

	List* p_current = position;
	while(p_current != NULL){
		if(get_next_row(mod) == get_row(p_current) && get_next_col(mod) ==
	      get_col(p_current))
				return true;

		p_current = get_nextCell(p_current);
	}
	return false;
}

Boolean check_pawn_last_line(Model* mod){
	unsigned int i = get_next_row(mod);
	unsigned int j = get_next_col(mod);

	if(get_piece(mod, i, j) == pawn){
		if(get_colorPiece(mod, i, j) == white){
			if(i == 0)
				return true;
		}
		else{
			if(get_colorPiece(mod, i, j) == black)
				if(i == 7)
					return true;
		}
	}

	return false;
}

void set_castle_indicator(Model* mod){
	assert(mod != NULL);

	unsigned int i = get_current_row(mod);
	unsigned int j = get_current_col(mod);
	Color colorPiece = get_colorRound(mod);
	ChessPiece piece = get_piece(mod, i, j);

	if(colorPiece == white){
		if(piece == king){
			set_white_castle_kingCheck(mod, true);
		}

		else if(piece == tower){
			if(j == 0)
				set_white_castle_leftTowerCheck(mod, true);
			else if(j == 7)
				set_white_castle_rightTowerCheck(mod, true);	
		}
	}

	else{
		if(piece == king){
			set_black_castle_kingCheck(mod, true);
		}

		else if(piece == tower){
			if(j == 0)
				set_black_castle_leftTowerCheck(mod, true);
			else if(j == 7)
				set_black_castle_rightTowerCheck(mod, true);	
		}
	}
}

void check_castle(Model* mod){
	assert(mod != NULL);

	unsigned int i = get_next_row(mod);
	unsigned int j = get_next_col(mod);
	Color colorPiece = get_colorRound(mod);
	ChessPiece piece = get_piece(mod, i, j);

	//castle move
	if(colorPiece == white){
		if(piece == king && (i == 7 && j == 6)){
			set_piece(mod, 7, 5, tower);
			set_colorPiece(mod, 7, 5, white);
			set_piece(mod, 7, 7, empty);
			set_colorPiece(mod, 7, 7, none);
			set_white_castle_indicator(mod, true);
		}

		else if(piece == king && (i == 7 && j == 2)){
			set_piece(mod, 7, 3, tower);
			set_colorPiece(mod, 7, 3, white);
			set_piece(mod, 7, 0, empty);
			set_colorPiece(mod, 7, 0, none);
			set_white_castle_indicator(mod, true);
		}
	}

	else{
		if(piece == king && (i == 0 && j == 6)){
			set_piece(mod, 0, 5, tower);
			set_colorPiece(mod, 0, 5, black);
			set_piece(mod, 0, 7, empty);
			set_colorPiece(mod, 0, 7, none);
			set_black_castle_indicator(mod, true);
		}

		else if(piece == king && (i == 0 && j == 2)){
			set_piece(mod, 0, 3, tower);
			set_colorPiece(mod, 0, 3, black);
			set_piece(mod, 0, 0, empty);
			set_colorPiece(mod, 0, 0, none);
			set_black_castle_indicator(mod, true);
		}
	}
}


/*******************************************************************************
****************************  testing functions  *******************************
*******************************************************************************/

void display_piece(Model* mod){
	unsigned int i, j;

	printf("pieces : \n");
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			printf("%u ", get_piece(mod, i, j));
		}
		printf("\n");
	}
	printf("\n");
}

void display_colorPiece(Model* mod){
	unsigned int i, j;

	printf("color pieces : \n");
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			printf("%u ", get_colorPiece(mod, i, j));
		}
		printf("\n");
	}
	printf("\n");
}

void display_colorCase(Model* mod){
	unsigned int i, j;

	printf("color cases : \n");
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			printf("%u ", get_colorCase(mod, i, j));
		}
		printf("\n");
	}
	printf("\n");
}

void display_stalemate_v1(Model* mod, unsigned int i, unsigned int j){
	if(check_stalemate_v1(mod, i, j))
		printf("stalemate\n");
	else
		printf("no stalemate\n");
}

void display_stalemate_v2(Model* mod){
	if(check_stalemate_v2(mod))
		printf("stalemate\n");
	else
		printf("no stalemate\n");
}

void display_checkmate(Model* mod){
	if(check_checkmate(mod))
		printf("checkmate\n");
	else
		printf("no checkmate\n");
}
