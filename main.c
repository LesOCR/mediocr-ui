#include "main.h"

int main (int argc, char *argv[] )
{
	GtkWidget *pWindow;
	GtkWidget *pVBox;
	GtkWidget *pMenuBar;
	GtkWidget *pMenu;
	GtkWidget *pMenuItem;
	GtkWidget *bouton_ouvrir;

	gtk_init(&argc, &argv);

	/* Création de la fenêtre */
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pWindow), "OCRelou");
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
	gtk_window_maximize(GTK_WINDOW(pWindow));
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* Création de la GtkVBox */
	pVBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

	/**** Création du menu ****/
	pMenuBar = gtk_menu_bar_new();
	/** Premier sous-menu **/
	pMenu = gtk_menu_new();

	bouton_ouvrir = gtk_menu_item_new_with_label("Ouvrir");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), bouton_ouvrir);
	g_signal_connect(G_OBJECT(bouton_ouvrir), "activate", G_CALLBACK(creer_file_selection), (GtkWidget*) pWindow);

	pMenuItem = gtk_menu_item_new_with_label("Enregistrer");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_label("Quitter");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnQuitter),(GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_label("Fichier");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);

	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/** Second sous-menu **/
	pMenu = gtk_menu_new();

	pMenuItem = gtk_menu_item_new_with_label("A propos de...");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnAbout),(GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_label("?");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);

	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/* Ajout du menu a la fenetre */
	gtk_box_pack_start(GTK_BOX(pVBox), pMenuBar, FALSE, FALSE, 0);

	gtk_widget_show_all(pWindow);

	gtk_main();
	return EXIT_SUCCESS;
}

void quitter(GtkWidget* widget)
{
	// destruction de win et de tout ce qu'il contient
	gtk_widget_destroy(widget);
	gtk_main_quit();
}

void creer_file_selection()
{
	GtkWidget *selection;

	selection = gtk_file_selection_new( g_locale_to_utf8( "Sélectionnez un fichier", -1, NULL, NULL, NULL) );
	gtk_widget_show(selection);

	//On interdit l'utilisation des autres fenêtres.
	gtk_window_set_modal(GTK_WINDOW(selection), TRUE);

	g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(recuperer_chemin), selection);

	g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}

void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection)
{
	const gchar* chemin;
	chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection) );

	GtkWidget *pWindow;
	GtkWidget *pVBox;
	GtkWidget *pImage;
	GtkWidget *pQuitBtn;

	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200); //
	gtk_window_set_title(GTK_WINDOW(pWindow), "Input");
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	pVBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

	/* Chargement d'une image a partir d'un fichier */
	pImage = gtk_image_new_from_file(chemin);
	gtk_box_pack_start(GTK_BOX(pVBox), pImage, FALSE, FALSE, 5);

	pQuitBtn = gtk_button_new();
	gtk_box_pack_start(GTK_BOX(pVBox), pQuitBtn, TRUE, FALSE, 5);
	g_signal_connect(G_OBJECT(pQuitBtn), "clicked", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(pWindow);

	gtk_widget_destroy(file_selection);
}

void OnQuitter(GtkWidget* widget, gpointer data)
{
	GtkWidget *pQuestion;

	pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			"Voulez vous vraiment\n"
			"quitter le programme?");

	switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
	{
		case GTK_RESPONSE_YES:
			gtk_main_quit();
			break;
		case GTK_RESPONSE_NONE:
		case GTK_RESPONSE_NO:
			gtk_widget_destroy(pQuestion);
			break;
	}
}

void OnAbout(GtkWidget* widget, gpointer data)
{
	GtkWidget *pAbout;

	pAbout = gtk_message_dialog_new(GTK_WINDOW(data),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			"Our website\n"
			"here soon");

	gtk_dialog_run(GTK_DIALOG(pAbout));

	gtk_widget_destroy(pAbout);
}
