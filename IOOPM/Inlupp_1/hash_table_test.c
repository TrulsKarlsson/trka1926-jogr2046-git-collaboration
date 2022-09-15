#include <CUnit/Basic.h>
#include "hash_table.h"
#include <stdlib.h>

typedef struct entry entry_t;

struct entry
{
    int key;       // holds the key
    char *value;   // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

static entry_t *entry_create(int key, char *value, entry_t *next)
{
    // Create an object for the new entry
    entry_t *new_entry = calloc(1, sizeof(entry_t));
    // Set the key and value fields to the key and value
    new_entry->key = key;
    new_entry->value = value;
    // Make the first entry the next entry of the new entry
    new_entry->next = next;

    return new_entry;
}

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.
void test1(void) {
  CU_ASSERT(42);
}

void test2(void) {
  CU_ASSERT_EQUAL(1 + 1, 2);
}

void test_entry_create()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    entry_t *entry = entry_create(4, "Test", NULL);
    CU_ASSERT_PTR_NOT_NULL(ht);
    ioopm_hash_table_destroy(ht);
}

void test_create_destroy()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    CU_ASSERT_PTR_NOT_NULL(ht);
    ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
    ioopm_hash_table_t *h = ioopm_hash_table_create();
    int key = 8;
    char *value = "Test";
    CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(h, key));
    ioopm_hash_table_insert(h, key, value);
    CU_ASSERT_EQUAL(ioopm_hash_table_lookup(h, key), value);
    ioopm_hash_table_destroy(h);
}

void test_insert_key_exist()
{
    ioopm_hash_table_t *h = ioopm_hash_table_create();
    int key = 4;
    char *value1 = "Test value1";
    char *value2 = "Test value2";
    CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(h, key));
    ioopm_hash_table_insert(h, key, value1);
    ioopm_hash_table_insert(h, key, value2);
    CU_ASSERT_EQUAL(ioopm_hash_table_lookup(h, key), value2);
    ioopm_hash_table_destroy(h);
}

int main() 
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "test_entry_create()", test_entry_create) == NULL)      ||
    (CU_add_test(my_test_suite, "test_insert_once", test_insert_once) == NULL)      ||
    (CU_add_test(my_test_suite, "test_insert_key_exist", test_insert_key_exist) == NULL)      ||
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
} 