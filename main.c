#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <gtk/gtk.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

int main( int   argc,
		char *argv[] )
{
	GtkWidget *window;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_show  (window);

	gtk_main ();

	return 0;
}
