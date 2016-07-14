#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include "model.h"
#include "position.h"

/*
 * initialise the board, the pieces are at the start position
 */
void initialisation_chessboard(Model* mod);

/*
 * get the initial colorCase of a position on the board
 */

Color get_initial_colorCase(unsigned int i, unsigned int j);


/*
 * get the possible next positions of the piece at the position (i , j)
 */
List* next_positions(Model* mod, unsigned int i, unsigned int j);

/*
 * check if the piece at the position (i, j) do a stalemate. it checks the next
 * positions of the piece and return true if the position of the opposing king
 * is among the possible next position of the piece.
 */
Boolean check_stalemate_v1(Model* mod, unsigned int i, unsigned int j);

/*
 * move a piece on the board
 */
void permute_1(Model* mod);

/*
 * restore the board at the state just before permute_1
 */
void permute_2(Model* mod);

/*
 * check if one of the opposing pieces can do a stalemate. if yes, return true,
 * else return false.
 */
Boolean check_stalemate_v2(Model* mod);

/*
 * check the possible next positions given by (next_positions()), it removes
 * a position on the list if this one allows the king to be in a stalemate
 * state, so we test each position of the list by doing a (check_stalemate_v2())
 */
List* check_next_positions(Model* mod, List* position);

/*
 * set the color of the initial color of the case set in green
 */
void retrieve_color_next_positions(Model* mod, List* position);

/*
 * change the color of a case that is a possible position or retrieve the
 * initial color
 */
void set_color_next_positions(Model* mod, List* position);

/*
 * check if there is a checkmate from the opposing player. so we check each
 * position of each pieces by applying (check_next_positions()).
 */
Boolean check_checkmate(Model* mod);

/*
 * check if the position selected is correct, is among the list next_positions
 */
Boolean check_possible_position(Model* mod, List* position);

/*
 * check if a pawn is on the last line
 */
Boolean check_pawn_last_line(Model* mod);

/*
 * set the indicator of the piece "king" and "tower" to true if they move
 */
void set_castle_indicator(Model* mod);

/*
 * if the castle is allowed, it pushed the new position possible position
 * of the king to the position alreadu pushed
 */
List* check_castle_position(Model* mod, List* position);

/*
 * checks if the player do the castle
 */
void check_castle(Model* mod);

//for tests
void display_piece(Model* mod);
void display_colorPiece(Model* mod);
void display_colorCase(Model* mod);
void display_stalemate_v1(Model* mod, unsigned int i, unsigned int j);
void display_stalemate_v2(Model* mod);
void display_checkmate(Model* mod);

#endif
