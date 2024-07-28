#include <stdio.h>
#include "raylib.h"
#include "stdint.h"
#include "math.h"
#include "quadtree.h"
#include "render.h"

#define NUM_COLORS 22


int main(void)
{
    int windowX = 1600;
    int windowY= 900;
    InitWindow(windowX, windowY, "windowname");
    SetTargetFPS(20);

    struct QTree qtree; 
    //qtree_init(&qtree, 200, 1400, 50, 800, 40);
    qtree_init(&qtree, 0, 5000, 0, 5000, 40);

    for (int i=0; i<1; i++) {
        for (int j=0; j<1; j++) {
        //qtree_add(&qtree, 1200+i, 700-i);
        qtree_add(&qtree, 200+i, 50+j);
        //qtree_add(&qtree, 100+i, 100+j);
        }
    }
    printf("tile count: %d\n", qtree.tile_count);
    printf("qtree size: %d Byte\n", qtree_get_size(&qtree));

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
    qtree_delete(&qtree);

    return 0;
}
