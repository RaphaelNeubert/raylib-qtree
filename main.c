#include <stdio.h>
#include "raylib.h"
#include "stdint.h"
#include "math.h"
#include "quadtree.h"
#include "render.h"
#include "raymath.h"

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

    Camera2D camera;
    camera.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    camera.target = (Vector2){0, 0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Vector2 prev_mpos = GetMousePosition();


    while (!WindowShouldClose())
    {
        float time = GetTime();

        Vector2 mpos = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 delta =  Vector2Subtract(prev_mpos, mpos);
            camera.target  = Vector2Add(camera.target, delta);
        }
        prev_mpos = mpos;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 world_coords = GetScreenToWorld2D(mpos, camera);
            qtree_add(&qtree, world_coords.x, world_coords.y);
            printf("tile count: %d\n", qtree.tile_count);
            printf("qtree size: %d Byte\n", qtree_get_size(&qtree));
        }
        float mouse_wheel_delta = GetMouseWheelMove();
        float new_zoom = camera.zoom + mouse_wheel_delta*0.1f;
        camera.zoom = (new_zoom>0)?new_zoom:0;



        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(0,0);

	BeginMode2D(camera);
        render_qtree(qtree);
	EndMode2D();
        EndDrawing();
        //break;
    }

    CloseWindow();
    qtree_delete(&qtree);

    return 0;
}
