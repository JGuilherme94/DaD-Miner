#include <gtk/gtk.h>
static cairo_surface_t *surface = NULL;
cairo_surface_t *image;

static gboolean on_expose_event (GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
  cairo_t *cr;
  surface = gdk_window_create_similar_surface(gtk_widget_get_window (widget), CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width (widget), gtk_widget_get_allocated_height (widget));
  cr = gdk_cairo_create(gtk_widget_get_window (widget));

  gfloat screen_width;
  gfloat screen_height;
  gfloat image_width;
  gfloat image_height;
  gfloat x_scaling;
  gfloat y_scaling;

  /* Display screen dimension in console  */
  screen_width = gdk_screen_get_width (gdk_screen_get_default ());
  screen_height = gdk_screen_get_height (gdk_screen_get_default ());
  g_message ("Screen width %f", screen_width);
  g_message ("Screen height %f", screen_height);

  /* Scale the loaded image to occupy the entire screen  */
  image_width = cairo_image_surface_get_width (image);
  image_height = cairo_image_surface_get_height (image);

  g_message ("Image width %f", image_width);
  g_message ("Image height %f", image_height);

  x_scaling = screen_width / image_width;
  y_scaling = screen_height / image_height;

  g_message ("x_scaling %f", x_scaling);
  g_message ("y_scaling %f", y_scaling);

  cairo_scale (cr, x_scaling, y_scaling);

  cairo_set_source_surface (cr, image, 0, 0);
  cairo_paint(cr);
  cairo_destroy(cr);
  //return TRUE;
  return FALSE;
}

 int main(int argc, char *argv[])
{
GtkWidget *window;
gtk_init(&argc, &argv);

window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
image = cairo_image_surface_create_from_png("show-me.png"); //Supply your own image here
g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
gtk_widget_set_app_paintable(window, FALSE);
gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
gtk_window_set_default_size (GTK_WINDOW(window), 800, 480);

GtkWidget *ebox = gtk_event_box_new ();
//GtkWidget *button;
//button = gtk_button_new_with_label("QUIT");
//gtk_widget_set_halign (GTK_WIDGET(button),GTK_ALIGN_CENTER);
//gtk_widget_set_valign (GTK_WIDGET(button),GTK_ALIGN_CENTER);
//gtk_container_add (GTK_CONTAINER(ebox), button);
//g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

gtk_container_add (GTK_CONTAINER(window), ebox);
g_signal_connect(ebox,"draw", G_CALLBACK (on_expose_event),NULL);

gtk_widget_show_all (window);

gtk_main();
cairo_surface_destroy (image);
return 0;
}