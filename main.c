#include <gtk/gtk.h>

static gchar *selected_file = NULL;

void convert_video_to_audio(const gchar *input_path) {
  if (input_path == NULL) {
    g_print("No File Selected");
    return;
  }

  gchar *output_path = g_strdup_printf("%s.mp3", input_path);
  gchar *command = g_strdup_printf("ffmpeg -y -i \"%s\" -b:a 128k -vn \"%s\"", input_path, output_path);
  int status = system(command);
  g_free(command);
  if (status == -1) {
    g_print("error: shell");
  } else if (status >> 8) {
    g_print("Error: ffmpeg eeror to running");
  } else {
    g_print("Success");
  }
}


static void on_file_selected(GObject *source, GAsyncResult *result, gpointer data) {
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
    g_print("File selected : %s\n", selected_file);
    g_object_unref(file);
  }
} 

static void choose_file(GtkButton *button, gpointer data) {
  GtkWindow *parent_window = GTK_WINDOW(data);
  GtkFileDialog *dialog = gtk_file_dialog_new();
  GtkFileFilter *filter = gtk_file_filter_new();

  gtk_file_filter_set_name(filter, "File Video");

  gtk_file_filter_add_mime_type(filter, "video/mp4");
  gtk_file_filter_add_mime_type(filter, "video/x-matroska");
  gtk_file_filter_add_mime_type(filter, "video/x-msvideo");

  GListStore *filters = g_list_store_new(GTK_TYPE_FILE_FILTER);
  g_list_store_append(filters, filter);
  gtk_file_dialog_set_filters(dialog, G_LIST_MODEL(filters));

  gtk_file_dialog_open(dialog, GTK_WINDOW(data), NULL, on_file_selected, NULL);

  g_object_unref(filter);
  g_object_unref(filters);
}

static void convert(GtkButton *button, gpointer data) {
  if (selected_file) {
    convert_video_to_audio(selected_file);
    g_free(selected_file);
    selected_file = NULL;
  } else {
    g_print("Please select file!");
  }
}

static void activate (GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *button_file_choose;
  GtkWidget *button;
  GtkWidget *box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Hydra - Video to Audio Converter");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 200);

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (box, GTK_ALIGN_CENTER);

  gtk_window_set_child (GTK_WINDOW (window), box);

  button_file_choose = gtk_button_new_with_label ("Select File");
  g_signal_connect (button_file_choose, "clicked", G_CALLBACK (choose_file), window);

  button = gtk_button_new_with_label ("Convert");
  g_signal_connect (button, "clicked", G_CALLBACK (convert), NULL);

  gtk_box_append (GTK_BOX (box), button_file_choose);
  gtk_box_append (GTK_BOX (box), button);

  gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}