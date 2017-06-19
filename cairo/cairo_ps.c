#include <cairo/cairo.h>
#include <cairo/cairo-ps.h>

#define PAGE_WIDTH 595
#define PAGE_HEIGHT 842

#define BORDER 50

void draw (cairo_t *cr, const char *text, int width, int height)
{
    char buf[100];

    cairo_rectangle (cr, BORDER, BORDER, width - 2*BORDER, height - 2*BORDER);
    cairo_set_line_width (cr, 2);
    cairo_stroke (cr);

    cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, 60);
    cairo_move_to (cr, 200, height/3);
    cairo_show_text (cr, text);

    sprintf (buf, "Width: %d points      Height: %d points", width, height);
    cairo_set_font_size (cr, 18);
    cairo_move_to (cr, 120, height*2/3);
    cairo_show_text (cr, buf);
}

int main()
{
    cairo_surface_t *surface;
    cairo_t *cr;
    cairo_matrix_t matrix;

    surface = cairo_ps_surface_create ("output.ps", PAGE_WIDTH, PAGE_HEIGHT);
    cr = cairo_create (surface);

    /* Print portrait page */
    cairo_ps_surface_dsc_begin_page_setup (surface);
    cairo_ps_surface_dsc_comment (surface, "%%PageOrientation: Portrait");
    draw (cr, "Portrait", PAGE_WIDTH, PAGE_HEIGHT);
    cairo_surface_show_page (surface);

    /* Print landscape page */
    cairo_ps_surface_dsc_begin_page_setup (surface);
    cairo_ps_surface_dsc_comment (surface, "%%PageOrientation: Landscape");

    /* Move the origin to landscape origin and rotate counterclockwise
     * 90 degrees.
     *
     * This is equivilent to:
     *    cairo_translate (cr, 0, PAGE_HEIGHT);
     *    cairo_rotate (cr, -M_PI/2);
     */
    cairo_translate (cr, 0, PAGE_HEIGHT);
    cairo_matrix_init (&matrix, 0, -1, 1, 0, 0,  0);
    cairo_transform (cr, &matrix);

    draw (cr, "Landscape", PAGE_HEIGHT, PAGE_WIDTH);
    cairo_surface_show_page (surface);

    cairo_destroy (cr);
    cairo_surface_finish (surface);
    cairo_surface_destroy (surface);

    return 0;
}
