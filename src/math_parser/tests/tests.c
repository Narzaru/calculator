#include <stdlib.h>
#include <check.h>


START_TEST(test_name) {
  /* Исходный код теста. */
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
