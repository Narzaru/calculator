#include <stdlib.h>
#include <check.h>
#include <calculator.h>


START_TEST(test_name) {
    status_t status;
    double result;
    status = calculator("1 + 3", NULL, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_double_eq(result, 4.0);
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
