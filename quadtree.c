#include "quadtree.h"
#include "stdio.h"
#include "math.h"
#include <stdlib.h>




void qtree_init(struct QTree *qtree, int x_from, int x_to, int y_from, int y_to,
                int min_tile_size)
{
    qtree->root_tile.x_from = x_from;
    qtree->root_tile.x_to = x_to;
    qtree->root_tile.y_from = y_from;
    qtree->root_tile.y_to = y_to;
    qtree->root_tile.has_children = false;
    qtree->root_tile.draw = false;
    qtree->root_tile.parent = NULL;
    qtree->tile_count = 1;
    qtree->tile_size = min_tile_size;
}

struct Tile* find_smallest_tile(struct Tile *tile, int xpos, int ypos)
{
    if (!tile->has_children)
        return tile;
    for (int i=0; i<4; i++) {
        struct Tile *t = tile->child[i];
        if (xpos >= t->x_from && xpos <= t->x_to &&
            ypos >= t->y_from && ypos <= t->y_to) {
            return find_smallest_tile(t, xpos, ypos);
        }
    }
    perror("error: smallest tile was not found");
    return NULL;
}
int subdivide_tile(struct Tile *tile)
{
    int width = tile->x_to - tile->x_from + 1;
    int height = tile->y_to - tile->y_from + 1;

    int mid_x = tile->x_from + (int)ceil(width / 2.0);
    int mid_y = tile->y_from + (int)ceil(height / 2.0);

    for (int i = 0; i < 4; i++) {
            tile->child[i] = (struct Tile *)malloc(sizeof(struct Tile));
            if (tile->child[i] == NULL) {
                perror("Memory allocation failed for child tile\n");
                return -1;
            }
        }
    // top left
    tile->child[0]->x_from = tile->x_from;
    tile->child[0]->x_to = mid_x - 1;
    tile->child[0]->y_from = tile->y_from;
    tile->child[0]->y_to = mid_y - 1;
    tile->child[0]->has_children = false;
    tile->child[0]->draw = false;
    tile->child[0]->parent= tile;
    // top right
    tile->child[1]->x_from = mid_x;
    tile->child[1]->x_to = tile->x_to;
    tile->child[1]->y_from = tile->y_from;
    tile->child[1]->y_to = mid_y - 1;
    tile->child[1]->has_children = false;
    tile->child[1]->draw = false;
    tile->child[1]->parent= tile;
    // bottom left
    tile->child[2]->x_from = tile->x_from;
    tile->child[2]->x_to = mid_x - 1;
    tile->child[2]->y_from = mid_y;
    tile->child[2]->y_to = tile->y_to;
    tile->child[2]->has_children = false;
    tile->child[2]->draw = false;
    tile->child[2]->parent= tile;
    // bottom right
    tile->child[3]->x_from = mid_x;
    tile->child[3]->x_to = tile->x_to;
    tile->child[3]->y_from = mid_y;
    tile->child[3]->y_to = tile->y_to;
    tile->child[3]->has_children = false;
    tile->child[3]->draw = false;
    tile->child[3]->parent= tile;

    tile->has_children = true;

    return 0;
}
// returns the amount of rectangles that have been merged
int merge_children(struct Tile *parent_tile)
{
    int merge_count = 0;
    for (int i=0; i<4; i++) {
        if (parent_tile->child[i]->draw != true)
            return 0;
    }

    parent_tile->draw = true;
    parent_tile->has_children = false;
    for (int i=0; i<4; i++) {
        free(parent_tile->child[i]);
        merge_count++;
    }
    if (parent_tile->parent != NULL)
        merge_count += merge_children(parent_tile->parent);
    return merge_count;
}

int qtree_add(struct QTree *qtree, int xpos, int ypos)
{
    int ret, merged;
    struct Tile *smallest_tile = find_smallest_tile(&qtree->root_tile, xpos, ypos);
    if (smallest_tile->draw)
        return 0;

    while ((smallest_tile->x_to - smallest_tile->x_from + 1) > qtree->tile_size && 
           (smallest_tile->y_to - smallest_tile->y_from + 1) > qtree->tile_size) {
        
        if ((ret = subdivide_tile(smallest_tile) != 0))
            return ret;
        qtree->tile_count += 4;
        smallest_tile = find_smallest_tile(smallest_tile, xpos, ypos);
    }
    smallest_tile->draw = true;
    merged = merge_children(smallest_tile->parent);
    qtree->tile_count -= merged;
    return 0;
}

int qtree_get_size(struct QTree *qtree)
{
    return sizeof(*qtree) + (qtree->tile_count-1) * sizeof(qtree->root_tile);
}

void free_tile(struct Tile *tile)
{
    if (tile->has_children) {
        for (int i=0; i<4; i++)
            free_tile(tile->child[i]);
    }
    free(tile);
}

void qtree_delete(struct QTree *qtree)
{
    for (int i=0; i<4; i++)
        free_tile(qtree->root_tile.child[i]);
}
