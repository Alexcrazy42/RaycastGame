#pragma once
#include <cmath>


#define WIDTH 960
#define HEIGHT 540
#define PI 3.1415926535897932384626433832795
#define e 2.7182818284590452353602874713526
#define NUM_RAYS  480
#define PIXEL_SCALE WIDTH/NUM_RAYS
#define TILE 32
#define FOV  PI/3
#define HALF_FOV  FOV/2 
#define MAX_DEPTH  pow(pow(WIDTH_MAP*32,2) + pow(HEIGHT_MAP*32, 2), 0.5)
#define DELTA_ANGLE  FOV/(NUM_RAYS-1)
#define DIST  NUM_RAYS / (2*tan(HALF_FOV))
#define PROJ_COEFF  2.2 * DIST * TILE
#define SCALE  int(WIDTH/NUM_RAYS)
#define PLAYER_SIZE 10
#define NUM_COL_RAYS 8

// настройки для текстур 
#define TEXTURE_WIDTH 960 
#define TEXTURE_HEIGHT 960 
#define TEXTURE_SCALE int(TEXTURE_WIDTH/TILE)