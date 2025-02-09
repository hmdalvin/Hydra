#ifndef CONVERTER_H
#define CONVERTER_H

#include <gtk/gtk.h>

extern gchar *selected_file;  // External declaration for the selected_file variable

void convert_video_to_audio(const gchar *input_path);
void choose_file(GtkButton *button, gpointer data);
void convert(GtkButton *button, gpointer data);
void on_file_selected(GObject *source, GAsyncResult *result, gpointer data); // Declaration of on_file_selected

#endif /* CONVERTER_H */
