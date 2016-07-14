#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "model.h"
#include "position.h"

#define BOARD_LENGTH 8
#define MESSAGE_LENGTH 150

// represent a chess piece
struct Piece_t{
	Color colorCase;
	Color colorPiece;
	ChessPiece piece;
};

// represent a position
struct Element_t{
	unsigned int row; // row of a piece
	unsigned int col; // column of a piece
};

// represent Castle
struct Castle_t{
	Boolean indicator; // indicate if a castle has been already done 
	Boolean kingCheck; // indicate if the king has already moved
	Boolean leftTowerCheck; // indicate if the left tower has already moved
	Boolean rightTowerCheck; // indicate if the right tower has already moved
};

// Model
struct Model_t{
	Piece** board; // the board (matrix of pieces)
	List* position; // list of the possible position of a piece
	unsigned int whiteLeft; // number of white pieces left
	unsigned int blackLeft; // number of black pieces left
	Element current; // current position of the select piece
	Element next; // next position of the select piece
	Element choice; //next position for choice of a piece if pawn reach limit
	Piece permutation; // for storing a piece in memory (permute_1/2)
	Boolean stalemate; // indicate a stalemate from the opposing player
	Castle white_castle; // white castle
	Castle black_castle; // black castle
	Color colorRound; // indicate round of the game (white / black play)
	Boolean click; //0 -> select piece, 1 -> select position
	char* message; //short message that indicate stalemate
};

//constructor - destructor
Model* build_model(void){
	Model* mod = malloc(sizeof(Model));
	if(mod == NULL)
		return NULL;

	//allocation of the chessboard
	mod->board = malloc(BOARD_LENGTH * sizeof(Piece*));
	if(mod->board == NULL){
		free(mod);
		return NULL;
	}

	unsigned int i;
	for(i = 0; i < BOARD_LENGTH; i++){
		mod->board[i] = malloc(BOARD_LENGTH * sizeof(Piece));
		if(mod->board[i] == NULL){
			unsigned int j;
			for(j = 0; j < i; j++){
				free(mod->board[j]);
			}
			free(mod->board);
			free(mod);
			return NULL;
		}
	}

	//allocation of the message
	mod->message = malloc(MESSAGE_LENGTH * sizeof(char));
	if(mod->message == NULL){
		for(i = 0; i < BOARD_LENGTH; i++){
			if(mod->board[i] != NULL)
				free(mod->board[i]);
			free(mod->board);
			free(mod);
			return NULL;
		}
	}

	return mod;
}

void destroy_model(Model* mod){
	assert(mod != NULL);

	unsigned int i;
	for(i = 0; i < BOARD_LENGTH; i++){
		if(mod->board[i] != NULL)
			free(mod->board[i]);
	}
	free(mod->board);
	free(mod->message);
	destroy_list(mod->position);
}

//accessors : getters
Color get_colorCase(Model* mod, unsigned int i, unsigned int j){
	assert(mod != NULL);
	return mod->board[i][j].colorCase;
}

Color get_colorPiece(Model* mod, unsigned int i, unsigned int j){
	assert(mod != NULL);
	return mod->board[i][j].colorPiece;
}

ChessPiece get_piece(Model* mod, unsigned int i, unsigned int j){
	assert(mod != NULL);
	return mod->board[i][j].piece;
}

List* get_list(Model* mod){
	assert(mod != NULL);
	return mod->position;
}

unsigned int get_whiteLeft(Model* mod){
	assert(mod != NULL);
	return mod->whiteLeft;
}

unsigned int get_blackLeft(Model* mod){
	assert(mod != NULL);
	return mod->blackLeft;
}

char* get_message(Model* mod){
	assert(mod != NULL);
	return mod->message;
}

unsigned int get_current_row(Model* mod){
	assert(mod != NULL);
	return mod->current.row;
}

unsigned int get_current_col(Model* mod){
	assert(mod != NULL);
	return mod->current.col;
}

unsigned int get_next_row(Model* mod){
	assert(mod != NULL);
	return mod->next.row;
}

unsigned int get_next_col(Model* mod){
	assert(mod != NULL);
	return mod->next.col;
}

unsigned int get_choice_row(Model* mod){
	assert(mod != NULL);
	return mod->choice.row;
}

unsigned int get_choice_col(Model* mod){
	assert(mod != NULL);
	return mod->choice.col;
}

ChessPiece get_permutation_piece(Model* mod){
	assert(mod != NULL);
	return mod->permutation.piece;
}

Color get_permutation_colorPiece(Model* mod){
  assert(mod != NULL);
  return mod->permutation.colorPiece;
}

Boolean get_stalemate(Model* mod){
	assert(mod != NULL);
	return mod->stalemate;
}

Color get_colorRound(Model* mod){
	assert(mod != NULL);
	return mod->colorRound;
}

Boolean get_click(Model* mod){
	assert(mod != NULL);
	return mod->click;
}

Boolean get_white_castle_indicator(Model* mod){
	assert(mod != NULL);
	return mod->white_castle.indicator;
}

Boolean get_white_castle_kingCheck(Model* mod){
	assert(mod != NULL);
	return mod->white_castle.kingCheck;
}

Boolean get_white_castle_rightTowerCheck(Model* mod){
	assert(mod != NULL);
	return mod->white_castle.rightTowerCheck;
}

Boolean get_white_castle_leftTowerCheck(Model* mod){
	assert(mod != NULL);
	return mod->white_castle.leftTowerCheck;
}

Boolean get_black_castle_indicator(Model* mod){
	assert(mod != NULL);
	return mod->black_castle.indicator;
}

Boolean get_black_castle_kingCheck(Model* mod){
	assert(mod != NULL);
	return mod->black_castle.kingCheck;
}

Boolean get_black_castle_rightTowerCheck(Model* mod){
	assert(mod != NULL);
	return mod->black_castle.rightTowerCheck;
}

Boolean get_black_castle_leftTowerCheck(Model* mod){
	assert(mod != NULL);
	return mod->black_castle.leftTowerCheck;
}

//accessors : setters
void set_colorCase(Model* mod, unsigned int i, unsigned int j, Color colorCase){
	assert(mod != NULL);
	mod->board[i][j].colorCase = colorCase;
}

void set_colorPiece(Model* mod, unsigned int i, unsigned int j,
	Color colorPiece){
	assert(mod != NULL);
	mod->board[i][j].colorPiece = colorPiece;
}

void set_piece(Model* mod, unsigned int i, unsigned int j, ChessPiece piece){
	assert(mod != NULL);
	mod->board[i][j].piece = piece;
}

void set_list(Model* mod, List* position){
	assert(mod != NULL);
	mod->position = position;
}

void set_whiteLeft(Model* mod, unsigned int whiteLeft){
	assert(mod != NULL);
	mod->whiteLeft = whiteLeft;
}

void set_blackLeft(Model* mod, unsigned int blackLeft){
	assert(mod != NULL);
	mod->blackLeft = blackLeft;
}

void set_message(Model* mod, char* message){
	assert(mod != NULL);
	mod->message = message;
}

void set_current_row(Model* mod, unsigned int row){
	assert(mod != NULL);
	mod->current.row = row;
}

void set_current_col(Model* mod, unsigned int col){
	assert(mod != NULL);
	mod->current.col = col;
}

void set_next_row(Model* mod, unsigned int row){
	assert(mod != NULL);
	mod->next.row = row;
}

void set_next_col(Model* mod, unsigned int col){
	assert(mod != NULL);
	mod->next.col = col;
}

void set_choice_row(Model* mod, unsigned int row){
	assert(mod != NULL);
	mod->choice.row = row;
}

void set_choice_col(Model* mod, unsigned int col){
	assert(mod != NULL);
	mod->choice.col = col;
}

void set_permutation_piece(Model* mod, ChessPiece piece){
	assert(mod != NULL);
	mod->permutation.piece = piece;
}

void set_permutation_colorPiece(Model* mod, Color colorPiece){
	assert(mod != NULL);
	mod->permutation.colorPiece = colorPiece;
}

void set_stalemate(Model* mod, Boolean stalemate){
	assert(mod != NULL);
	mod->stalemate = stalemate;
}

void set_colorRound(Model* mod, Color colorRound){
	assert(mod != NULL);
	mod->colorRound = colorRound;
}

void set_click(Model* mod, Boolean click){
	assert(mod != NULL);
	mod->click = click;
}

void set_white_castle_indicator(Model* mod, Boolean indicator){
	assert(mod != NULL);
	mod->white_castle.indicator = indicator;
}

void set_white_castle_kingCheck(Model* mod, Boolean indicator){
	assert(mod != NULL);
	mod->white_castle.kingCheck = indicator;
}

void set_white_castle_rightTowerCheck(Model* mod, Boolean indicator){
	assert(mod != NULL);
	mod->white_castle.rightTowerCheck = indicator;
}

void set_white_castle_leftTowerCheck(Model* mod, Boolean indicator){
	assert(mod != NULL);
	mod->white_castle.leftTowerCheck = indicator;
}

void set_black_castle_indicator(Model* mod, Boolean indicator){
	assert(mod != NULL);
	mod->black_castle.indicator = indicator;
}

void set_black_castle_kingCheck(Model* mod, Boolean indicator){
	assert(mod != NULL);
	mod->black_castle.kingCheck = indicator;
}

void set_black_castle_rightTowerCheck(Model* mod, Boolean indicator){
	assert(mod != NULL);
	mod->black_castle.rightTowerCheck = indicator;
}

void set_black_castle_leftTowerCheck(Model* mod, Boolean indicator){
	assert(mod != NULL);
	mod->black_castle.leftTowerCheck = indicator;
}