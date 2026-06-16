#include "affine_transformation.h"

void rotate_x(float rad, vertex_t *vertex, unsigned count) {
    for (unsigned i = 0; i < count; ++i) {
        float y = vertex[i].y;
        float z = vertex[i].z;
        vertex[i].y = cos(rad) * y - sin(rad) * z;
        vertex[i].z = sin(rad) * y + cos(rad) * z;
    }
}

void rotate_y(float rad, vertex_t *vertex, unsigned count) {
    for (unsigned i = 0; i < count; ++i) {
        float x = vertex[i].x;
        float z = vertex[i].z;
        vertex[i].x = cos(rad) * x + sin(rad) * z;
        vertex[i].z = -sin(rad) * x + cos(rad) * z;
    }
}

void rotate_z(float rad, vertex_t *vertex, unsigned count) {
    for (unsigned i = 0; i < count; ++i) {
        float x = vertex[i].x;
        float y = vertex[i].y;
        vertex[i].x = cos(rad) * x - sin(rad) * y;
        vertex[i].y = sin(rad) * x + cos(rad) * y;
    }
}

void mov_x(float dist, vertex_t *vertex, unsigned count) {
    for (unsigned i = 0; i < count; ++i) vertex[i].x += dist;
}

void mov_y(float dist, vertex_t *vertex, unsigned count) {
    for (unsigned i = 0; i < count; ++i) vertex[i].y += dist;
}

void mov_z(float dist, vertex_t *vertex, unsigned count) {
    for (unsigned i = 0; i < count; ++i) vertex[i].z += dist;
}

void scale_xyz(float scale, vertex_t *vertex, unsigned count) {
    if (scale == 0)
        return;
    if (scale > 0) {
        for (unsigned i = 0; i < count; ++i) {
            vertex[i].x *= scale;
            vertex[i].y *= scale;
            vertex[i].z *= scale;
        }
    } else if (scale < 0) {
        scale = -scale;
        for (unsigned i = 0; i < count; ++i) {
            vertex[i].x /= scale;
            vertex[i].y /= scale;
            vertex[i].z /= scale;
        }
    }
}

void scale_x(float scale, vertex_t *vertex, unsigned count) {
    if (scale == 0)
        return;
    if (scale > 0) {
        for (unsigned i = 0; i < count; ++i) vertex[i].x *= scale;
    } else if (scale < 0) {
        scale = -scale;
        for (unsigned i = 0; i < count; ++i) vertex[i].x /= scale;
    }
}

void scale_y(float scale, vertex_t *vertex, unsigned count) {
    if (scale == 0)
        return;
    if (scale > 0) {
        for (unsigned i = 0; i < count; ++i) vertex[i].y *= scale;
    } else if (scale < 0) {
        scale = -scale;
        for (unsigned i = 0; i < count; ++i) vertex[i].y /= scale;
    }
}

void scale_z(float scale, vertex_t *vertex, unsigned count) {
    if (scale == 0)
        return;
    if (scale > 0) {
        for (unsigned i = 0; i < count; ++i) vertex[i].z *= scale;
    } else if (scale < 0) {
        scale = -scale;
        for (unsigned i = 0; i < count; ++i) vertex[i].z /= scale;
    }
}
