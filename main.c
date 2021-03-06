#include "main.h"



//Creates the main window
int main (int argc, char *argv[]) {

	struct main_window mW;

	mW.fio = malloc(sizeof(struct in_out));

	gtk_init (&argc, &argv);

	//Builds the interface elements
	mW.builder = gtk_builder_new ();
		gtk_builder_add_from_file (mW.builder, "form.glade", NULL);

	mW.window = gtk_builder_get_object (mW.builder, "main_window");
		g_signal_connect (mW.window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	mW.button_open = gtk_builder_get_object (mW.builder, "open_button");
		g_signal_connect (mW.button_open, "activate", G_CALLBACK (openFileWindow),
			&mW);

	mW.textArea = gtk_builder_get_object (mW.builder, "textArea");
		mW.text = gtk_text_buffer_new(NULL);
		gtk_text_view_set_buffer((GtkTextView*) mW.textArea, mW.text);
		setText(&mW, "Empty");

	GdkPixbuf* logo_pixbuf = gdk_pixbuf_new_from_file("data/mediocr.png", NULL);
	gdk_pixbuf_scale_simple(logo_pixbuf, 200, 200, GDK_INTERP_BILINEAR);
	GtkImage* logo_image = (GtkImage*) gtk_builder_get_object (mW.builder, "logo_image");
	GObject *process_button = gtk_builder_get_object (mW.builder, "logo_button");
	g_signal_connect (process_button, "clicked", G_CALLBACK (process_file),
		&mW);
	gtk_image_set_from_pixbuf(logo_image, logo_pixbuf);


	mW.imageArea = (GtkImage*)gtk_builder_get_object (mW.builder, "input");

	//Connects the buttons to their respective functions
	gtk_builder_connect_signals( mW.builder, NULL );

	//Displays the main window
	gtk_widget_show((GtkWidget*) mW.window);

	g_signal_connect(G_OBJECT(mW.window), "configure-event",
        G_CALLBACK(onResize), &mW);


	gtk_main();

	return 0;
}

void process_file(GtkWidget *widget, gpointer data)
{
	struct main_window* mW = (struct main_window*) data;
	if (!mW->path) return;
	chdir("app/");
		 /* Open the command for reading. */
	char command[400];
	strcpy(command, "./main -d data/words/english.txt -f ");
  mW->fio->fp = popen(strcat(command, mW->path), "r");
  if (mW->fio->fp == NULL) {
    printf("Failed to run OCR\n" );
    exit(1);
  }

  /* Read the output a line at a time - output it. */
  // while (fgets(mW->fio->path, sizeof(mW->fio->path)-1, mW->fio->fp) != NULL) {
  //   printf("%s", mW->fio->path);
  // }
	setText(mW, mW->fio->path);
  /* close */
  pclose(mW->fio->fp);
}

//Create the "open-file" window
void  openFileWindow(GtkWidget *widget, gpointer data) {
	struct main_window* mW = (struct main_window*) data;
	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new ("Open Input File",
												GTK_WINDOW (mW->window),
												GTK_FILE_CHOOSER_ACTION_OPEN,
												"_Cancel", GTK_RESPONSE_CANCEL,
												"_Open", GTK_RESPONSE_ACCEPT,
												NULL);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
		char *filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		loadFile(mW, filename);
	}
	gtk_widget_destroy (dialog);
}

//Loads an image and launches the detection process
int loadFile(struct main_window *mW, char *path) {
	//Save path
	strcpy(mW->path, path);

	//Store the buffer in memory and make a copy
	mW->processPixbuf = gdk_pixbuf_new_from_file(mW->path, NULL);
	mW->previewPixbuf = gdk_pixbuf_copy(mW->processPixbuf);

	//Display preview
	previewFromPix(mW, mW->previewPixbuf);
	return 0;
}

//Sets the preview-window from a pixbuffer
void previewFromPix(struct main_window *mW, GdkPixbuf* pixBuf) {

	//Get container size
	int containerWidth = gtk_widget_get_allocated_width((GtkWidget*) mW->imageArea);
	int containerHeight = gtk_widget_get_allocated_height((GtkWidget*) mW->imageArea);

	//Get image size
	int pixWidth = gdk_pixbuf_get_width(pixBuf);
	int pixHeight = gdk_pixbuf_get_height(pixBuf);

	float ratio = (float)pixWidth/(float)pixHeight;

	int previewWidth, previewHeight;

	//Preview size computation
	if (pixWidth > pixHeight) {
		previewWidth = containerWidth;
		previewHeight = (int)((float)containerWidth/ratio);
	} else {
		previewHeight = containerHeight;
		previewWidth = (int)((float)containerHeight*ratio);
	}

	//Set size and apply
	mW->previewPixbuf = gdk_pixbuf_scale_simple(pixBuf, previewWidth, previewHeight, GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(mW->imageArea, mW->previewPixbuf);
}

int onResize(GtkWidget *widget, gpointer data) {
  // struct main_window* mW = (struct main_window*) data;
	// previewFromPix(mW, edgeDetectedPixbuf);
	return 0;
}

int setText(struct main_window *mW, char* text) {
	gtk_text_buffer_set_text(mW->text, text, strlen(text));
	return 0;
}

int gtk_quit(struct main_window *mW) {
	gtk_widget_destroy((GtkWidget*) mW->window);
  gtk_main_quit();
	return 0;
}
