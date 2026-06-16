#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include "3d_viewer.h"

int st_TEST(int a) {
    static int b = 3;
    b++;
    return b + a;
}

int count_v_f(const char *path, unsigned *v, unsigned *f) {
    FILE *fp;
    fp = fopen(path, "rb");
    int is_open = 0;
    *v = 0;
    *f = 0;
    if (fp) {
        is_open = 1;
        char *str = calloc(1000, sizeof(char));
        size_t len;
        while (getline(&str, &len, fp) != EOF) {
            if (str[0] == 'v' && str[1] == ' ' && (str[2] == '-' || (str[2] >= '0' && str[2] <= '9'))) {
                *v += 1;
            } else if (str[0] == 'f' && str[1] == ' ' && (str[2] >= '0' && str[2] <= '9')) {
                *f += 1;
            }
        }
        if (str) free(str);
        fclose(fp);
    }

    return is_open;
}

s21_data scan_obj(const char *path) {
    s21_data figure;
    if (count_v_f(path, &figure.count_vertexes, &figure.count_facets)) {
        FILE *fp = fopen(path, "rb");
        figure.vertexes = malloc(figure.count_vertexes * sizeof(vertex_t));
        figure.polygons = malloc(figure.count_facets * sizeof(polygon_t));
        char *str = calloc(1000, sizeof(char));
        size_t len;
        for (int v = 0, f = 0; v + f < figure.count_facets + figure.count_vertexes;) {
            getline(&str, &len, fp);
            if (str[0] == 'v' && str[1] == ' ') {
                sscanf(str + 2,
                       "%f%f%f",
                       &figure.vertexes[v].x,
                       &figure.vertexes[v].y,
                       &figure.vertexes[v].z);
                v++;
            } else if (str[0] == 'f' && str[1] == ' ' && (str[2] >= '0' && str[2] <= '9')) {
                int words = count_words(str);
                figure.polygons[f].vertexes = (uint32_t*)malloc(sizeof(uint32_t) * words);
                figure.polygons[f].vertexes_in_facets = 0;
                int n = 0;
                for (int i = 2; figure.polygons[f].vertexes_in_facets < words;) {
                    sscanf(str + i,
                           "%d%n",
                           &figure.polygons[f].vertexes[figure.polygons[f].vertexes_in_facets],
                           &n);
                    i += n;
                    while (str[i] != ' ' && str[i] != 0)
                        i++;
                    figure.polygons[f].vertexes_in_facets++;
                }
                f++;
            }
        }
        fclose(fp);
        if (str) free(str);
    }
    return figure;
}

int count_words(const char *str) {
    int words = 0;
    for (int i = 2; str[i]; ++i) {
        if (str[i] >= '0' && str[i] <= '9' && str[i - 1] == ' ') words++;
    }
    return words;
}

void free_obj(s21_data *figure) {
    for (int i = 0; i < figure->count_facets; ++i)
        free(figure->polygons[i].vertexes);
    free(figure->polygons);
    free(figure->vertexes);
}
