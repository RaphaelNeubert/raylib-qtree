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
    SetTargetFPS(1000);

    struct QTree qtree; 
    //qtree_init(&qtree, 200, 1400, 50, 800, 40);
    qtree_init(&qtree, -20000000, 20000000, -20000000, 20000000, 40);

    for (int i=0; i<15000000; i++) {
        qtree_add(&qtree, 200+i, 50+i);
        //qtree_add(&qtree, 200, 50+i);
    }
    printf("tile count: %d\n", qtree.tile_count);
    printf("qtree size: %d Byte\n", qtree_get_size(&qtree));

    Camera2D camera;
    //camera.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    camera.offset = (Vector2){0,0};
    camera.target = (Vector2){0,0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Vector2 prev_mpos = GetMousePosition();


    while (!WindowShouldClose())
    {
        float time = GetTime();

        // Handle inputs
        Vector2 mpos = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 delta =  Vector2Subtract(prev_mpos, mpos);
            camera.target  = GetScreenToWorld2D(Vector2Add(camera.offset, delta), camera);
        }
        prev_mpos = mpos;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 world_coords = GetScreenToWorld2D(mpos, camera);
            qtree_add(&qtree, world_coords.x, world_coords.y);
            printf("tile count: %d\n", qtree.tile_count);
            int qtree_size = qtree_get_size(&qtree);
            printf("qtree size: %d Byte, %d MByte\n",qtree_size, (int)qtree_size/1000000);
        }
        float mouse_wheel_delta = GetMouseWheelMove();
        float new_zoom = camera.zoom + mouse_wheel_delta*0.1f;
        camera.zoom = (new_zoom>0)?new_zoom:0;



        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(0,0);

	BeginMode2D(camera);
        int tiles_drawn = render_qtree(qtree, camera);
	EndMode2D();

        render_num_top_right(tiles_drawn, "tiles drawn:");
        EndDrawing();
        //break;
    }

    CloseWindow();
    qtree_delete(&qtree);

    return 0;
}
