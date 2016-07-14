#ifndef __MODEL__
#define __MODEL__

#include "position.h"

typedef enum{white, black, blue, green, none} Color;
typedef enum{empty, pawn, bishow, knight, tower, queen, king} ChessPiece;
typedef enum{false, true} Boolean;

typedef struct Model_t Model;
typedef struct Piece_t Piece;
typedef struct Element_t Element;
typedef struct Castle_t Castle;

//prototypes
Model* build_model(void);
void destroy_model(Model* mod);

//accessors : getters
Color get_colorCase(Model* mod, unsigned int i, unsigned int j);
Color get_colorPiece(Model* mod, unsigned int i, unsigned int j);
ChessPiece get_piece(Model* mod, unsigned int i, unsigned int j);
List* get_list(Model* mod);
unsigned int get_whiteLeft(Model* mod);
unsigned int get_blackLeft(Model* mod);
char* get_message(Model* mod);
unsigned int get_current_row(Model* mod);
unsigned int get_current_col(Model* mod);
unsigned int get_next_row(Model* mod);
unsigned int get_next_col(Model* mod);
unsigned int get_choice_row(Model* mod);
unsigned int get_choice_col(Model* mod);
ChessPiece get_permutation_piece(Model* mod);
Color get_permutation_colorPiece(Model* mod);
Boolean get_stalemate(Model* mod);
Color get_colorRound(Model* mod);
Boolean get_click(Model* mod);
Boolean get_white_castle_indicator(Model* mod);
Boolean get_white_castle_kingCheck(Model* mod);
Boolean get_white_castle_leftTowerCheck(Model* mod);
Boolean get_white_castle_rightTowerCheck(Model* mod);
Boolean get_black_castle_indicator(Model* mod);
Boolean get_black_castle_kingCheck(Model* mod);
Boolean get_black_castle_leftTowerCheck(Model* mod);
Boolean get_black_castle_rightTowerCheck(Model* mod);

//accessors : setters
void set_colorCase(Model* mod, unsigned int i, unsigned int j, Color colorCase);
void set_colorPiece(Model* mod, unsigned int i, unsigned int j,
	 Color colorPiece);
void set_piece(Model* mod, unsigned int i, unsigned int j, ChessPiece piece);
void set_list(Model* mod, List* position);
void set_whiteLeft(Model* mod, unsigned int whiteLeft);
void set_blackLeft(Model* mod, unsigned int blackLeft);
void set_message(Model* mod, char* message);
void set_current_row(Model* mod, unsigned int row);
void set_current_col(Model* mod, unsigned int col);
void set_next_row(Model* mod, unsigned int row);
void set_next_col(Model* mod, unsigned int col);
void set_choice_row(Model* mod, unsigned int row);
void set_choice_col(Model* mod, unsigned int col);
void set_permutation_piece(Model* mod, ChessPiece piece);
void set_permutation_colorPiece(Model* mod, Color colorPiece);
void set_stalemate(Model* mod, Boolean stalemate);
void set_colorRound(Model* mod, Color colorRound);
void set_click(Model* mod, Boolean click);
void set_white_castle_indicator(Model* mod, Boolean indicator);
void set_white_castle_kingCheck(Model* mod, Boolean indicator);
void set_white_castle_leftTowerCheck(Model* mod, Boolean indicator);
void set_white_castle_rightTowerCheck(Model* mod, Boolean indicator);
void set_black_castle_indicator(Model* mod, Boolean indicator);
void set_black_castle_kingCheck(Model* mod, Boolean indicator);
void set_black_castle_leftTowerCheck(Model* mod, Boolean indicator);
void set_black_castle_rightTowerCheck(Model* mod, Boolean indicator);


#endif
