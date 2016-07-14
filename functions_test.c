#include <stdio.h>
#include <stdlib.h>

#include "seatest.h"
#include "functions.h"
#include "model.h"
#include "position.h"

static void test_initialisation_chessboard(void){
	Model* mod = build_model();
	initialisation_chessboard(mod);

	unsigned int i, j;
	//pieces
	printf("*** test initialisation chessboard ***\n\n");
	display_piece(mod);
	display_colorPiece(mod);
	display_colorCase(mod);
}

static void test_next_positions_pawn(void){
	printf("*** test next positions pawns ***\n\n");
	Model* mod = build_model();
	initialisation_chessboard(mod);

	//vertical moves
	display_list(next_positions(mod, 1, 0));

	display_list(next_positions(mod, 6, 3));

	set_piece(mod, 3, 1, pawn);
	display_list(next_positions(mod, 1, 1));

	set_piece(mod, 2, 1, pawn);
	display_list(next_positions(mod, 1, 1));

	set_piece(mod, 5, 0, tower);
	set_colorPiece(mod, 5, 0, black);
	set_piece(mod, 5, 2, pawn);
	set_colorPiece(mod, 5, 2, white);
	display_list(next_positions(mod, 6, 1));
}

static void test_next_positions_bishow(void){
	printf("\n*** test next positions bishows ***\n\n");
	Model* mod = build_model();
	initialisation_chessboard(mod);

	//start positions
	display_list(next_positions(mod, 0, 2));
	display_list(next_positions(mod, 7, 5));

	//down, up, right and left movements
	set_piece(mod, 3, 3, bishow);
	set_colorPiece(mod, 3, 3, white);
	display_list(next_positions(mod, 3, 3));

	set_colorPiece(mod, 3, 3, black);
	display_list(next_positions(mod, 3, 3));
}

static void test_next_positions_knight(void){
	printf("\n*** test next positions knights ***\n\n");
	Model* mod = build_model();
	initialisation_chessboard(mod);

	//initial positions
	display_list(next_positions(mod, 0, 1));

	set_piece(mod, 4, 3, knight);
	set_colorPiece(mod, 4, 3, black);
	display_list(next_positions(mod, 4, 3));

	set_colorPiece(mod, 4, 3, white);
	display_list(next_positions(mod, 4, 3));
}

static void test_next_positions_tower(void){
	printf("\n*** test next positions tower ***\n\n");

	Model* mod = build_model();
	initialisation_chessboard(mod);

	//initial position
	display_list(next_positions(mod, 0, 0));

	set_piece(mod, 3, 3, tower);
	set_colorPiece(mod, 3, 3, white);
	display_list(next_positions(mod, 3, 3));
}

static void test_next_positions_queen(void){
	printf("\n*** test next positions queen ***\n\n");

	Model* mod = build_model();
	initialisation_chessboard(mod);

	//initial position
	display_list(next_positions(mod, 0, 3));

	set_piece(mod, 3, 3, queen);
	set_colorPiece(mod, 3, 3, white);
	display_list(next_positions(mod, 3, 3));
}

static void test_next_positions_king(void){
	printf("\n*** test next positions king ***\n\n");
	Model* mod = build_model();
	initialisation_chessboard(mod);

	//initial positions
	display_list(next_positions(mod, 0, 4));

	set_piece(mod, 3, 3, king);
	set_colorPiece(mod, 3, 3, black);
	set_piece(mod, 2, 2, pawn);
	set_colorPiece(mod, 2, 2, black);
	set_piece(mod, 3, 4, knight);
	set_colorPiece(mod, 3, 4, white);
	display_list(next_positions(mod, 3, 3));
}

static void test_check_stalemate_v1(void){
	printf("\n*** test check stalemate_v1 ***\n\n");
	Model* mod = build_model();
	initialisation_chessboard(mod);

	set_piece(mod, 5, 2, king);
	set_colorPiece(mod, 5, 2, black);

	set_piece(mod, 5, 7, tower);
	set_colorPiece(mod, 5, 7, white);

	set_piece(mod, 3, 3, bishow);
	set_colorPiece(mod, 3, 3, white);

	set_piece(mod, 3, 0, queen);
	set_colorPiece(mod, 3, 0, white);

	set_piece(mod, 4, 0, queen);
	set_colorPiece(mod, 4, 0, white);

	display_stalemate_v1(mod, 5, 7);
	display_stalemate_v1(mod, 3, 3);
	display_stalemate_v1(mod, 3, 0);
	display_stalemate_v1(mod, 4, 0);
	display_stalemate_v1(mod, 7, 1);
	display_stalemate_v1(mod, 6, 2);
	display_stalemate_v1(mod, 6, 3);
}

static void test_permute_pieces(void){
	printf("\n*** test permute pieces ***\n\n");
	Model* mod = build_model();
	initialisation_chessboard(mod);

	set_current_row(mod, 0);
	set_current_col(mod, 0);
	set_next_row(mod, 7);
	set_next_col(mod, 4);

	permute_1(mod);

	display_piece(mod);
	display_colorPiece(mod);

	permute_2(mod);

	display_piece(mod);
	display_colorPiece(mod);
}

static void test_check_stalemate_v2(void){
	Model* mod = build_model();
	initialisation_chessboard(mod);

	set_piece(mod, 4, 3, king);
	set_colorPiece(mod, 4, 3, black);

	set_piece(mod, 5, 2, tower);
	set_colorPiece(mod, 5, 2, white);
	set_piece(mod, 4, 2, knight);
	set_colorPiece(mod, 4, 2, white);
	set_piece(mod, 2, 4, queen);
	set_colorPiece(mod, 2, 4, white);
	set_piece(mod, 3, 5, bishow);
	set_colorPiece(mod, 3, 5, white);

	set_whiteLeft(mod, 20);
	set_colorRound(mod, black);

	display_stalemate_v2(mod);

	set_piece(mod, 2, 3, tower);
	set_colorPiece(mod, 2, 3, white);
	set_whiteLeft(mod, 21);

	display_stalemate_v2(mod);
}

static void test_check_next_positions(void){
	printf("\n*** test check next positions ***\n\n");
	Model* mod = build_model();
	initialisation_chessboard(mod);

	//first test
	set_piece(mod, 4, 3, king);
	set_colorPiece(mod, 4, 3, black);
	set_current_row(mod, 4);
	set_current_col(mod, 3);

	set_piece(mod, 5, 2, tower);
	set_colorPiece(mod, 5, 2, white);
	set_piece(mod, 4, 2, knight);
	set_colorPiece(mod, 4, 2, white);
	set_piece(mod, 2, 4, queen);
	set_colorPiece(mod, 2, 4, white);
	set_piece(mod, 3, 5, bishow);
	set_colorPiece(mod, 3, 5, white);

	set_whiteLeft(mod, 20);
	set_colorRound(mod, black);

	List* position = next_positions(mod, 4, 3);
	position = check_next_positions(mod, position);
	display_list(position);
	destroy_list(position);

	//second test
	initialisation_chessboard(mod);
	set_colorRound(mod, black);
	set_current_row(mod, 0);
	set_current_col(mod, 4);

	set_piece(mod, 1, 5, queen);
	set_colorPiece(mod, 1, 5, white);

	position = next_positions(mod, 0, 4);
	position = check_next_positions(mod, position);
	display_list(position);

	set_piece(mod, 3, 6, knight);
	set_colorPiece(mod, 3, 6, white);

	position = next_positions(mod, 0, 4);
	position = check_next_positions(mod, position);
	display_list(position);

	//third test
	/*
			*** YOLO ***
	*/

}

static void test_check_checkmate(void){
	printf("\n*** test checkmate ***\n\n");
	Model* mod = build_model();
	initialisation_chessboard(mod);

	//second test
	set_colorRound(mod, black);

	set_piece(mod, 1, 5, queen);
	set_colorPiece(mod, 1, 5, white);

	set_piece(mod, 3, 6, tower);
	set_colorPiece(mod, 3, 6, white);

	display_checkmate(mod);
}



static void test_fixture(){
   test_fixture_start();

   run_test(test_initialisation_chessboard);

	run_test(test_next_positions_pawn);
	run_test(test_next_positions_bishow);
	run_test(test_next_positions_knight);
	run_test(test_next_positions_tower);
	run_test(test_next_positions_queen);
	run_test(test_next_positions_king);

	run_test(test_check_stalemate_v1);
	run_test(test_permute_pieces);
	run_test(test_check_stalemate_v2);
	run_test(test_check_next_positions);
	run_test(test_check_checkmate);

   test_fixture_end();
}

static void all_tests(){
   test_fixture();
}

int main(){
   return run_tests(all_tests);
}
