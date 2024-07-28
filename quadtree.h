#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdbool.h>

struct Tile {
    int x_from;
    int x_to;
    int y_from;
    int y_to;
    bool has_children;
    bool draw;
    struct Tile *child[4];
    struct Tile *parent;
};

struct QTree {
    struct Tile root_tile; 
    int tile_count;
    int tile_size;    // defines a upper bound for the tile size, might be smaller since we divide by 2
};

void qtree_init(struct QTree *qtree, int x_from, int x_to, int y_from, int y_to,
                int min_tile_size);
int qtree_add(struct QTree *qtree, int xpos, int ypos);
int qtree_get_size(struct QTree *qtree);
void qtree_delete(struct QTree *qtree);

#endif 
