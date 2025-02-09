#include <gtk/gtk.h>
#include "converter.h"  // Include the updated header
#include "ui.h"

void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Hydra - Video to Audio Converter");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_window_set_child(GTK_WINDOW(window), box);

  GtkWidget *file_choose_button = gtk_button_new_with_label("Select File");
  g_signal_connect(file_choose_button, "clicked", G_CALLBACK(choose_file), window);

  

  GtkWidget *convert_button = gtk_button_new_with_label("Convert");
  g_signal_connect(convert_button, "clicked", G_CALLBACK(convert), NULL);

  gtk_box_append(GTK_BOX(box), file_choose_button);
  gtk_box_append(GTK_BOX(box), convert_button);

  gtk_window_present(GTK_WINDOW(window));
}