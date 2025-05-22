#include <stdio.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <math.h>

typedef struct costume {
    char* svgcost_path;
} costume;

typedef struct sprite {
    double angle;
    int x;
    int y;
    bool visible;
    struct costume curcost;
    struct costume allcost[10];
} sprite;

typedef struct bkg {
    char* svgbak_path;
} bkg;

typedef struct stage {
    sprite* curspirtes;
    int num_sprites;
    bkg curback;
} stage;

stage main_stage;
GtkWidget* drawing_area;

static void draw_sprite(cairo_t* cr, sprite* sp) {
    if (sp->visible) {
        cairo_save(cr);
        cairo_translate(cr, sp->x, sp->y);
        cairo_rotate(cr, sp->angle * (M_PI / 180.0));
        cairo_rectangle(cr, -25, -25, 50, 50);
        cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
        cairo_fill(cr);
        cairo_restore(cr);
    }
}

static gboolean on_draw(GtkWidget* widget, cairo_t* cr, gpointer data) {
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
    cairo_paint(cr);
    for (int i = 0; i < main_stage.num_sprites; i++) {
        draw_sprite(cr, main_stage.curspirtes + i);
    }
    return FALSE;
}

void set_x(int sprite_index, int x) {
    if (sprite_index >= 0 && sprite_index < main_stage.num_sprites) {
        main_stage.curspirtes[sprite_index].x = x;
        gtk_widget_queue_draw(drawing_area);
    }
}

void set_y(int sprite_index, int y) {
    if (sprite_index >= 0 && sprite_index < main_stage.num_sprites) {
        main_stage.curspirtes[sprite_index].y = y;
        gtk_widget_queue_draw(drawing_area);
    }
}

void move_steps(int sprite_index, int steps) {
    if (sprite_index >= 0 && sprite_index < main_stage.num_sprites) {
        double angle_rad = main_stage.curspirtes[sprite_index].angle * (M_PI / 180.0);
        main_stage.curspirtes[sprite_index].x += (int)(steps * cos(angle_rad));
        main_stage.curspirtes[sprite_index].y -= (int)(steps * sin(angle_rad));
        gtk_widget_queue_draw(drawing_area);
    }
}

void turn_degrees(int sprite_index, double degrees) {
    if (sprite_index >= 0 && sprite_index < main_stage.num_sprites) {
        main_stage.curspirtes[sprite_index].angle += degrees;
        gtk_widget_queue_draw(drawing_area);
    }
}

void show_sprite(int sprite_index) {
    if (sprite_index >= 0 && sprite_index < main_stage.num_sprites) {
        main_stage.curspirtes[sprite_index].visible = true;
        gtk_widget_queue_draw(drawing_area);
    }
}

void hide_sprite(int sprite_index) {
    if (sprite_index >= 0 && sprite_index < main_stage.num_sprites) {
        main_stage.curspirtes[sprite_index].visible = false;
        gtk_widget_queue_draw(drawing_area);
    }
}

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sprite Stage");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw), NULL);

    main_stage.num_sprites = 1;
    main_stage.curspirtes = (sprite*)malloc(sizeof(sprite) * main_stage.num_sprites);

    if (main_stage.curspirtes == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }

    main_stage.curspirtes[0].angle = 0.0;
    main_stage.curspirtes[0].x = 400;
    main_stage.curspirtes[0].y = 300;
    main_stage.curspirtes[0].visible = true;
    main_stage.curspirtes[0].curcost.svgcost_path = "example.svg";

    set_x(0, 100);
    set_y(0, 100);
    turn_degrees(0, 45.0);
    move_steps(0, 50);

    gtk_widget_show_all(window);
    gtk_main();
    free(main_stage.curspirtes);
    return 0;
}
