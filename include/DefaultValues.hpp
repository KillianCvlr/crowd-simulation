#pragma once

#define SCREEN_X 2000
#define SCREEN_Y 1000

#define COLUMN_NUMBER (SCREEN_X / CELL_SIZE)
#define LINE_NUMBER (SCREEN_Y / CELL_SIZE)

#define FPS 200

#define NB_CELLULAR_UNITS ((COLUMN_NUMBER * LINE_NUMBER) / 200)
//#define NB_CELLULAR_UNITS 1
#define CELL_SIZE 4

#define ANGLE_VIEW  M_PI_2f
#define DISTANCE_VIEW 15*CELL_SIZE

#define SIZE_MAX_QTREE 2
#define MAX_LEVEL_QTREE 20
#define FORCE_FACTOR 0.03
#define MAX_SPEED 1.0
#define MAX_ACCEL 1.0

#define DT 0.01