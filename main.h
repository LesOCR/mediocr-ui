#ifndef MAIN_H
#define MAIN_H

#define _BSD_SOURCE
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//-------

struct in_out {
  FILE *fp;
  char path[1035];
};

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

  struct in_out *fio;
};

//-------------- FUNCTION HEADERS --------------------

void openFileWindow (GtkWidget *widget, gpointer fileChooser);
int loadFile(struct main_window *mW, char *path);
void showAbout (GtkWidget *widget, gpointer data);
void closeAbout (GtkWidget *widget, gpointer data);
int onResize(GtkWidget *widget, gpointer data);
void process_file(GtkWidget *widget, gpointer data);
void previewFromPix(struct main_window* mW, GdkPixbuf* pixbuf);
int setText(struct main_window *mW, char* text);
int gtk_quit(struct main_window *mW);


#endif
