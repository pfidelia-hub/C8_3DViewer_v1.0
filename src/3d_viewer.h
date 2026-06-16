#ifndef SRC_3D_VIEWER_H_
#define SRC_3D_VIEWER_H_

#define S21_FLOAT

#ifdef S21_DOUBLE
typedef double s21_flt;
#elif defined S21_FLOAT
typedef float s21_flt;
#endif
/*==========PARSER==========*/
typedef struct facets {
  unsigned *vertexes;
  unsigned vertexes_in_facets;
} polygon_t;

typedef struct {
  s21_flt x, y, z;
} vertex_t;

typedef struct {
  unsigned count_vertexes;
  unsigned count_facets;
  vertex_t *vertexes;
  polygon_t *polygons;
} s21_data;

int count_v_f(const char *path, unsigned *v, unsigned *f);
vertex_t *scan_vertexes(const char *path, int v);
void print_vertexes(vertex_t *arr, int count);
void print_polygons(polygon_t *arr, int count);
int count_words(const char *str);
s21_data scan_obj(const char *path);
void free_obj(s21_data *figure);

#endif  //  SRC_3D_VIEWER_H_
