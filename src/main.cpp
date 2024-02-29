#include <stdio.h>
#include <gtk/gtk.h>

#include "crack.h"

static void activate(GtkApplication* app, gpointer user_data);
static void crack_event(GtkWidget *widget, gpointer data);

int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.cracker", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;
}

static void activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Cracker");
    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);

    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER (window), button_box);

    button = gtk_button_new_with_label("Crack!");
    g_signal_connect(button, "clicked", G_CALLBACK (crack_event), NULL);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER (button_box), button);

    gtk_widget_show_all(window);
}

static void crack_event(GtkWidget *widget, gpointer data)
{
    if (cracker("CRACKME.COM"))
    {
        printf("Error in hacking process!\n");
    }

    printf("Programm hacked!\n");
}
