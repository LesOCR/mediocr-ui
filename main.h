#ifndef MAIN_H
#define MAIN_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

//-------------- STRUCTURES -----------------------

struct main_window  {
  GtkBuilder *builder;
  GObject *window;
  //Buttons
  GObject *button_open, *button_quit, *button_about;
  //Window areas
  GObject *aboutDialog, *fileChooser, *textArea;
  GtkImage *imageArea;
  GtkWidget *image;

  //Image Buffers
  GdkPixbuf *processPixbuf, *originalPixbuf, *previewPixbuf;
  //Path
  char path[200];
  //Detected text
  GtkTextBuffer *text;

  int** binarizedArray;
};

//-------------- FUNCTION HEADERS --------------------

void openFileWindow (GtkWidget *widget, gpointer fileChooser);
int loadFile(struct main_window *mW, char *path);
void showAbout (GtkWidget *widget, gpointer data);
void closeAbout (GtkWidget *widget, gpointer data);
int onResize(GtkWidget *widget, gpointer data);
void previewFromPix(struct main_window* mW, GdkPixbuf* pixbuf);
int setText(struct main_window *mW, char* text);
int gtk_quit(struct main_window *mW);


#endif
