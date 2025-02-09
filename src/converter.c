#include "converter.h"

gchar *selected_file = NULL;  // Definition of the global variable selected_file

void convert_video_to_audio(const gchar *input_path) {
  if (input_path == NULL) {
    g_print("No File Selected\n");
    return;
  }

  gchar *output_path = g_strdup_printf("%s.mp3", input_path);
  gchar *command = g_strdup_printf("ffmpeg -y -i \"%s\" -b:a 128k -vn \"%s\"", input_path, output_path);
  int status = system(command);
  g_free(command);
  if (status != 0) {
    g_print("Error: ffmpeg error during execution\n");
  } else {
    g_print("Conversion Successful\n");
  }

  g_free(output_path); // Free the output_path
}

void on_file_selected(GObject *source, GAsyncResult *result, gpointer data) {
  GtkFileDialog *dialog = GTK_FILE_DIALOG(source);
  GError *error = NULL;
  
  GFile *file = gtk_file_dialog_open_finish(dialog, result, &error);

  if (error) {
    g_printerr("Error: %s\n", error->message);
    g_error_free(error);
    return;
  }

  if (file) {
    if (selected_file) {
      g_free(selected_file);
    }

    selected_file = g_file_get_path(file);
    g_print("File selected: %s\n", selected_file);
    g_object_unref(file);
  }
}

void choose_file(GtkButton *button, gpointer data) {
  GtkWindow *parent_window = GTK_WINDOW(data);
  GtkFileDialog *dialog = gtk_file_dialog_new();
  GtkFileFilter *filter = gtk_file_filter_new();

  gtk_file_filter_set_name(filter, "Video File");

  gtk_file_filter_add_mime_type(filter, "video/mp4");
  gtk_file_filter_add_mime_type(filter, "video/x-matroska");
  gtk_file_filter_add_mime_type(filter, "video/x-msvideo");
  gtk_file_filter_add_mime_type(filter, "video/quicktime"); gtk_file_filter_add_mime_type(filter, "video/webm");gtk_file_filter_add_mime_type(filter, "video/x-flv");gtk_file_filter_add_mime_type(filter, "video/mpeg");gtk_file_filter_add_mime_type(filter, "video/ogg");

  GListStore *filters = g_list_store_new(GTK_TYPE_FILE_FILTER);
  g_list_store_append(filters, filter);
  gtk_file_dialog_set_filters(dialog, G_LIST_MODEL(filters));

  gtk_file_dialog_open(dialog, parent_window, NULL, on_file_selected, NULL);

  g_object_unref(filter);
  g_object_unref(filters);
}

void convert(GtkButton *button, gpointer data) {
  if (selected_file) {
    convert_video_to_audio(selected_file);
    g_free(selected_file);
    selected_file = NULL;
  } else {
    g_print("Please select a file!\n");
  }
}
