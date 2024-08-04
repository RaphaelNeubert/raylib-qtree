#ifndef RENDER_H
#define RENDER_H
#include "quadtree.h"
#include "raylib.h"

int render_qtree(struct QTree qtree, Camera2D camera);
void render_num_top_right(int number, char* prefix_text);


#endif  // RENDER_H
