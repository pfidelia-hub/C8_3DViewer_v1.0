#ifndef SRC_AFFINE_TRANSFORMATION_H_
#define SRC_AFFINE_TRANSFORMATION_H_

#include "3d_viewer.h"
#include <math.h>

void rotate_x(float rad, vertex_t *vertex, unsigned count);
void rotate_y(float rad, vertex_t *vertex, unsigned count);
void rotate_z(float rad, vertex_t *vertex, unsigned count);

void mov_x(float dist, vertex_t *vertex, unsigned count);
void mov_y(float dist, vertex_t *vertex, unsigned count);
void mov_z(float dist, vertex_t *vertex, unsigned count);

void scale_xyz(float scale, vertex_t *vertex, unsigned count);
void scale_x(float scale, vertex_t *vertex, unsigned count);
void scale_y(float scale, vertex_t *vertex, unsigned count);
void scale_z(float scale, vertex_t *vertex, unsigned count);

#endif  //  SRC_AFFINE_TRANSFORMATION_H_
