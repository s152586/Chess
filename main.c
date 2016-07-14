#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gtk/gtk.h>

#include "model.h"
#include "view.h"
#include "controller.h"
#include "functions.h"

int main(int argc, char** argv){

	//initialisation of MVC
	Model* mod = build_model();
   initialisation_chessboard(mod);
	View* view = build_view(mod);
	Controller* con = build_controller(mod, view);

	set_imageBoardButton(view);

	//elements of GUI
	GtkWidget* window;

	GtkWidget* menuBar;
	GtkWidget* menuGame;
	GtkWidget* menuHelp;
	GtkWidget* itemGame;
	GtkWidget* itemHelp;
	GtkWidget* itemNewGame;
	GtkWidget* itemAbout;
	GtkWidget* itemQuit;

	GtkWidget* tableBoard;
	GtkWidget* vBox;

	gtk_init(&argc, &argv);

	//creation of window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(window), "Chess");
   gtk_window_set_default_size(GTK_WINDOW(window), 1, 1);
   gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
   gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),
	   NULL);

	//creation of menu
	menuBar = gtk_menu_bar_new();
	menuGame = gtk_menu_new();
	menuHelp = gtk_menu_new();

	itemGame = gtk_menu_item_new_with_label("Game");
	itemHelp = gtk_menu_item_new_with_label("Help");
	itemNewGame = gtk_menu_item_new_with_label("New game");
	itemQuit = gtk_menu_item_new_with_label("Quit");
	itemAbout = gtk_menu_item_new_with_label("About");

	gtk_menu_shell_append(GTK_MENU_SHELL(menuGame), itemNewGame);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuGame), itemQuit);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(itemGame), menuGame);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), itemGame);

	gtk_menu_shell_append(GTK_MENU_SHELL(menuHelp), itemAbout);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(itemHelp), menuHelp);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), itemHelp);

	//signals
	g_signal_connect(G_OBJECT(itemNewGame), "activate",
	   G_CALLBACK(start_new_game), con);

	g_signal_connect(G_OBJECT(itemQuit), "activate",
		G_CALLBACK(quit_game), con);

	g_signal_connect(G_OBJECT(itemAbout), "activate",
		G_CALLBACK(display_about), con);



	//creation of table
	tableBoard = gtk_table_new(8, 8, TRUE);
	unsigned int i, j;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			gtk_table_attach_defaults(GTK_TABLE(tableBoard),
            get_boardButton(con, i, j), j, j+1, i, i+1);
		}
	}

	//signals
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			g_signal_connect(G_OBJECT(get_boardButton(con, i, j)), "clicked",
		      G_CALLBACK(click_piece), con);
		}
	}

	gtk_table_set_row_spacings(GTK_TABLE(tableBoard), 0);
   gtk_table_set_col_spacings(GTK_TABLE(tableBoard), 0);

	//creation of box
	vBox = gtk_vbox_new(FALSE, 0);

	gtk_box_pack_start(GTK_BOX(vBox), menuBar, FALSE, FALSE, 3);
   gtk_box_pack_start(GTK_BOX(vBox), tableBoard, FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(vBox), get_labelMessage(view), TRUE, FALSE, 3);

	gtk_container_add(GTK_CONTAINER(window), vBox);
	gtk_widget_show_all(window);

	gtk_main();

	return EXIT_SUCCESS;
}
