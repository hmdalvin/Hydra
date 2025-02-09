#include <gtk/gtk.h>

static void on_file_selected(GObject *source, GAsyncResult *result, gpointer data) {
  GtkFileDialog *dialog;
  dialog = GTK_FILE_DIALOG(source);
  GFile *file;
  file = gtk_file_dialog_open_finish(dialog, result, NULL);
  char *file_path;
  file_path = g_file_get_path(file);

  char *current_dir = g_get_current_dir();
  g_print(file_path);

  char *output_path = g_build_filename(current_dir, "audio.mp3", NULL);

  if (g_file_test(file_path, G_FILE_TEST_EXISTS)){
    g_print("file found : ", file_path);
  } else {
    g_print("file not found");
  }

  char *command[] = {
    "D:\\ffmpeg\\bin\\ffmpeg.exe",
    "-i", file_path,
    "-vn",
    "-acodec",
    "libmp3lame",
    "-ab", "192k",
    output_path,
    NULL
  };

  GError *error = NULL;
  GPid child_pid;
  gboolean success = g_spawn_async(NULL, command, NULL, G_SPAWN_DO_NOT_REAP_CHILD, NULL, NULL, &child_pid, &error);

  if (!success) {
    g_print("Error: %s\n", error->message);
  } else {
    g_print("Convert Success");
  }

  g_free(file_path);
  g_object_unref(file);
} 

static void choose_file(GtkWidget *widget, gpointer data) {
  GtkFileDialog *dialog;
  GListStore *filter_store;
  GtkFileFilter *filter;

  dialog = gtk_file_dialog_new();
  filter_store = g_list_store_new(GTK_TYPE_FILE_FILTER);

  if (!filter_store) {
    g_print("Error: filter store error init");
    return;
  }

  filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "File Video");
  gtk_file_filter_add_mime_type(filter, "video/mp4");
  g_list_store_append(filter_store, filter);

  if (g_list_model_get_n_items(G_LIST_MODEL(filter_store)) > 0) {
    gtk_file_dialog_set_filters(dialog, G_LIST_MODEL(filter_store));
  } else {
    g_print("Error: no filter in the array");
  }

  gtk_file_dialog_open(dialog, GTK_WINDOW(data), NULL, on_file_selected, NULL);
}

static void convert(GtkApplication *app, gpointer user_data) {
  g_print ("Test Convert");
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