#include <stdlib.h>
#include <gtk/gtk.h>

int start(int argc, char *argv[]);
void OnQuitter(GtkWidget* widget, gpointer data);
void OnAbout(GtkWidget* widget, gpointer data);
void quitter(GtkWidget *widget); void creer_file_selection();
void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection);
