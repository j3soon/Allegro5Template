#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

int main(int argc, char **argv)
{
    al_init();
    al_init_font_addon();
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    ALLEGRO_FONT* font = al_create_builtin_font();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!");
    al_flip_display();
    al_rest(5.0);
    al_destroy_font(font);
    al_destroy_display(display);
    return 0;
}