#include "render.h"
#include "raylib.h"



void render_tile(struct Tile *tile)
{
    int width = tile->x_to - tile->x_from + 1;
    int height = tile->y_to - tile->y_from + 1;
    //printf("draw: %d, x_from: %d, x_to: %d;    y_from: %d, y_to: %d\n", tile->draw, tile->x_from, tile->x_to, tile->y_from, tile->y_to);
    if (tile->draw) {
        DrawRectangle(tile->x_from, tile->y_from, width, height, BLUE);
        DrawRectangleLines(tile->x_from, tile->y_from, width, height, RED);
    } else {
        DrawRectangleLines(tile->x_from, tile->y_from, width, height, BLACK);

        if (tile->has_children) {
            for (int i=0; i<4; i++) {
                //int xfrom = 0;
                //int xto = 300;
                //int yfrom = 0;
                //int yto = 800;
                //struct Tile *c = tile->child[i];
//if ((c->x_from > xfrom || c->x_to > xfrom) && (c->x_from < xto || c->x_to < xto))
                //if ((c->x_from > xfrom && c->x_to < xto) && (c->x_from < xto || c->x_to < xto))
                    render_tile(tile->child[i]);
            }
        } 
    }
}
void render_qtree(struct QTree qtree)
{
    render_tile(&qtree.root_tile);
}
