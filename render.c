#include "render.h"
#include "raylib.h"
#include <stdio.h>


// returns number of drawn tiles
int render_tile(struct Tile *tile, Vector2 top_left, Vector2 bottom_right)
{
    int num_drawn = 0;
    int width = tile->x_to - tile->x_from + 1;
    int height = tile->y_to - tile->y_from + 1;
    //printf("draw: %d, x_from: %d, x_to: %d;    y_from: %d, y_to: %d\n", tile->draw, tile->x_from, tile->x_to, tile->y_from, tile->y_to);
    if (tile->draw) {
        DrawRectangle(tile->x_from, tile->y_from, width, height, BLUE);
        DrawRectangleLines(tile->x_from, tile->y_from, width, height, RED);
        num_drawn++;
    } else {
        DrawRectangleLines(tile->x_from, tile->y_from, width, height, BLACK);

        if (tile->has_children) {
            for (int i=0; i<4; i++) {
                struct Tile *c = tile->child[i];
                if (((c->x_from <= bottom_right.x && c->x_to >= top_left.x) && 
                    (c->y_from <= bottom_right.y && c->y_to >= top_left.y)))
                    num_drawn += render_tile(tile->child[i], top_left, bottom_right);
            }
        } 
    }
    return num_drawn;
}
// returns number of drawn tiles
int render_qtree(struct QTree qtree, Camera2D camera)
{
    Vector2 top_left = GetScreenToWorld2D((Vector2){0,0}, camera);
    Vector2 bottom_right = GetScreenToWorld2D((Vector2){GetScreenWidth(), GetScreenHeight()}, camera);
    return render_tile(&qtree.root_tile, top_left, bottom_right);
}


void render_num_top_right(int number, char* prefix_text) 
{
    char text[30];
    sprintf(text, "%s %d", prefix_text, number);
    int text_width = MeasureText(text, 20);
    DrawText(text, GetScreenWidth() - text_width - 10, 10, 20, BLACK);
}
