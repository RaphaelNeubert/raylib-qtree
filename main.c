#include <stdio.h>
#include "raylib.h"
#include "stdint.h"
#include "math.h"
#include "quadtree.h"

#define NUM_COLORS 22

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
                render_tile(tile->child[i]);
            }
        } 
    }
}
void render_qtree(struct QTree qtree)
{
    render_tile(&qtree.root_tile);
}

int main(void)
{
    int windowX = 1600;
    int windowY= 900;
    InitWindow(windowX, windowY, "windowname");
    SetTargetFPS(20);

    struct QTree qtree; 
    //qtree_init(&qtree, 200, 1400, 50, 800, 40, 40);
    qtree_init(&qtree, 200, 800, 50, 650, 40, 40);

    for (int i=0; i<50; i++) {
        for (int j=0; j<50; j++) {
        //qtree_add(&qtree, 1200+i, 700-i);
        qtree_add(&qtree, 200+i, 50+j);
        //qtree_add(&qtree, 100+i, 100+j);
        }
    }
    printf("tile count: %d\n", qtree.tile_count);

    while (!WindowShouldClose())
    {
        float time = GetTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(0,0);
        render_qtree(qtree);
        EndDrawing();
        //break;
    }

    CloseWindow();

    return 0;
}
