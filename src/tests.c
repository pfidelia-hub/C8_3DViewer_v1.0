#include <check.h>
#include "3d_viewer.h"
#include "affine_transformation.h"
#include <stdio.h>

START_TEST(test) {
    s21_data figure = scan_obj("tests/c.obj");
    ck_assert(figure.count_vertexes == 8);
    ck_assert(figure.count_facets == 12);
    float tmp_x = figure.vertexes[0].x;
    float tmp_y = figure.vertexes[0].y;
    float tmp_z = figure.vertexes[0].z;
    rotate_x(1, figure.vertexes, figure.count_vertexes);
    ck_assert_float_eq(tmp_x, figure.vertexes[0].x);
    ck_assert(tmp_y != figure.vertexes[0].y);
    ck_assert(tmp_z != figure.vertexes[0].z);
    tmp_x = figure.vertexes[0].x;
    tmp_y = figure.vertexes[0].y;
    tmp_z = figure.vertexes[0].z;
    rotate_y(1, figure.vertexes, figure.count_vertexes);
    ck_assert_float_eq(tmp_y, figure.vertexes[0].y);
    ck_assert(tmp_x != figure.vertexes[0].x);
    ck_assert(tmp_z != figure.vertexes[0].z);
    tmp_x = figure.vertexes[0].x;
    tmp_y = figure.vertexes[0].y;
    tmp_z = figure.vertexes[0].z;
    rotate_z(1, figure.vertexes, figure.count_vertexes);
    ck_assert_float_eq(tmp_z, figure.vertexes[0].z);
    ck_assert(tmp_x != figure.vertexes[0].x);
    ck_assert(tmp_y != figure.vertexes[0].y);
    tmp_x = figure.vertexes[0].x;
    tmp_y = figure.vertexes[0].y;
    tmp_z = figure.vertexes[0].z;
    mov_x(1, figure.vertexes, figure.count_vertexes);
    ck_assert_float_eq(tmp_y, figure.vertexes[0].y);
    ck_assert_float_eq(tmp_z, figure.vertexes[0].z);
    tmp_x = figure.vertexes[0].x;
    tmp_y = figure.vertexes[0].y;
    tmp_z = figure.vertexes[0].z;
    mov_y(1, figure.vertexes, figure.count_vertexes);
    ck_assert_float_eq(tmp_x, figure.vertexes[0].x);
    ck_assert_float_eq(tmp_z, figure.vertexes[0].z);
    tmp_x = figure.vertexes[0].x;
    tmp_y = figure.vertexes[0].y;
    tmp_z = figure.vertexes[0].z;
    mov_z(1, figure.vertexes, figure.count_vertexes);
    ck_assert_float_eq(tmp_x, figure.vertexes[0].x);
    ck_assert_float_eq(tmp_y, figure.vertexes[0].y);
    scale_xyz(2, figure.vertexes, figure.count_vertexes);
    ck_assert(tmp_x != figure.vertexes[0].x);
    ck_assert(tmp_y != figure.vertexes[0].y);
    ck_assert(tmp_z != figure.vertexes[0].z);
    tmp_x = figure.vertexes[0].x;
    tmp_y = figure.vertexes[0].y;
    tmp_z = figure.vertexes[0].z;
    scale_x(2, figure.vertexes, figure.count_vertexes);
    ck_assert(tmp_x != figure.vertexes[0].x);
    tmp_x = figure.vertexes[0].x;
    tmp_y = figure.vertexes[0].y;
    tmp_z = figure.vertexes[0].z;
    scale_y(2, figure.vertexes, figure.count_vertexes);
    ck_assert(tmp_y != figure.vertexes[0].y);
    tmp_x = figure.vertexes[0].x;
    tmp_y = figure.vertexes[0].y;
    tmp_z = figure.vertexes[0].z;
    scale_z(2, figure.vertexes, figure.count_vertexes);
    ck_assert(tmp_z != figure.vertexes[0].z);
    scale_xyz(-2.2, figure.vertexes, figure.count_vertexes);
    ck_assert(tmp_x != figure.vertexes[0].x);
    ck_assert(tmp_y != figure.vertexes[0].y);
    ck_assert(tmp_z != figure.vertexes[0].z);
    tmp_x = figure.vertexes[0].x;
    tmp_y = figure.vertexes[0].y;
    tmp_z = figure.vertexes[0].z;
    scale_x(-2, figure.vertexes, figure.count_vertexes);
    ck_assert(tmp_x != figure.vertexes[0].x);
    tmp_x = figure.vertexes[0].x;
    tmp_y = figure.vertexes[0].y;
    tmp_z = figure.vertexes[0].z;
    scale_y(-2, figure.vertexes, figure.count_vertexes);
    ck_assert(tmp_y != figure.vertexes[0].y);
    tmp_x = figure.vertexes[0].x;
    tmp_y = figure.vertexes[0].y;
    tmp_z = figure.vertexes[0].z;
    scale_z(-2, figure.vertexes, figure.count_vertexes);
    ck_assert(tmp_z != figure.vertexes[0].z);
    free_obj(&figure);
};
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;
    suite_add_tcase(s1, tc);

    tcase_add_test(tc, test);
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);
    return nf != 0;
}
