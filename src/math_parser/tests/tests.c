#include <stdlib.h>
#include <check.h>
#include <calculator.h>
#include <stdio.h>
#include <math.h>


START_TEST(test_name) {
    status_t status;
    double result;
    char x_val[64];

    status = calculator("1 + 3", NULL, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_msg(fabs(result - 4.0) < FLT_EPSILON, "%e < %e", fabs(result - 4.0), FLT_EPSILON);

    snprintf(x_val, sizeof(x_val), "%.12f", PI);
    status = calculator("cos(x)", x_val, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_msg(fabs(result - (-1.0)) < FLT_EPSILON, "%e < %e", fabs(result + 1.0), FLT_EPSILON);

    snprintf(x_val, sizeof(x_val), "%.32f", PI);
    status = calculator("cos(x) * sin(x)", x_val, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_msg(fabs(result - 0.0) < FLT_EPSILON, "%e < %e", fabs(result - 0.0), FLT_EPSILON);

    status = calculator("4 --4 ", NULL, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_msg(fabs(result - 8.0) < FLT_EPSILON, "%e < %e", fabs(result - 8.0), FLT_EPSILON);

    status = calculator("10 mod 3", NULL, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_msg(fabs(result - 1.0) < FLT_EPSILON, "%e < %e", fabs(result - 1.0), FLT_EPSILON);

    snprintf(x_val, sizeof(x_val), "%.32f", PI);
    status = calculator("cos(x) * sin(x) +", x_val, &result);
    ck_assert_int_eq(status, INVALID_EXPRESSION_STRUCTURE);

    status = calculator("tan(atan(3))", NULL, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_msg(fabs(result - 3.0) < FLT_EPSILON, "%e < %e", fabs(result - 3.0), FLT_EPSILON);

    status = calculator("sqrt(ln(2.5))", NULL, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_msg(fabs(result - 0.95723076208) < FLT_EPSILON,
        "%e < %e",
        fabs(result - 0.95723076208),
        FLT_EPSILON);

    status = calculator("1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1",
        NULL,
        &result);
    ck_assert_int_eq(status, OK);
    ck_assert_msg(fabs(result - 41.0) < FLT_EPSILON,
        "%e < %e",
        fabs(result - 41.0),
        FLT_EPSILON);

    status = calculator("acos(asin(log(4)))", NULL, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_msg(fabs(result - 0.868360769) < FLT_EPSILON,
        "%e < %e",
        fabs(result - 0.868360769),
        FLT_EPSILON);

    status = calculator("2 ^ 2 ^ 2", NULL, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_msg(fabs(result - 16) < FLT_EPSILON,
        "%e < %e",
        fabs(result - 16),
        FLT_EPSILON);
} END_TEST


Suite *example_suite_create(void) {
    Suite *suite = suite_create("Example");
    TCase *tcase_core = tcase_create("Core of example");
    tcase_add_test(tcase_core, test_name);
    suite_add_tcase(suite, tcase_core);
    return suite;
}


int main(void) {
    Suite *suite = example_suite_create();
    SRunner *suite_runner = srunner_create(suite);

    srunner_run_all(suite_runner, CK_NORMAL);
    int failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    if (failed_count != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
