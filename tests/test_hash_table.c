#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"

void test_ht_insert() {
    hash_table* ht = new_hash_table();

    // Test inserting a key-value pair
    ht_insert(ht, "key1", "value1");
    if (strcmp(ht_search(ht, "key1"), "value1") == 0) {
        printf("Test passed for ht_insert\n");
    } else {
        printf("Test failed for ht_insert\n");
    }

    // Test inserting a duplicate key
    ht_insert(ht, "key1", "value2");
    if (strcmp(ht_search(ht, "key1"), "value2") == 0) {
        printf("Test passed for ht_insert (duplicate key)\n");
    } else {
        printf("Test failed for ht_insert (duplicate key)\n");
    }

    // Test inserting multiple key-value pairs
    ht_insert(ht, "key2", "value3");
    ht_insert(ht, "key3", "value4");
    if (strcmp(ht_search(ht, "key2"), "value3") == 0 && strcmp(ht_search(ht, "key3"), "value4") == 0) {
        printf("Test passed for ht_insert (multiple key-value pairs)\n");
    } else {
        printf("Test failed for ht_insert (multiple key-value pairs)\n");
    }

    del_hash_table(ht);
}

void test_ht_search() {
    hash_table* ht = new_hash_table();

    // Test searching for a key that doesn't exist
    if (ht_search(ht, "key1") == NULL) {
        printf("Test passed for ht_search (key not found)\n");
    } else {
        printf("Test failed for ht_search (key not found)\n");
    }

    // Test searching for a key that exists
    ht_insert(ht, "key1", "value1");
    if (strcmp(ht_search(ht, "key1"), "value1") == 0) {
        printf("Test passed for ht_search (key found)\n");
    } else {
        printf("Test failed for ht_search (key found)\n");
    }

    del_hash_table(ht);
}

void test_ht_delete() {
    hash_table* ht = new_hash_table();

    // Test deleting a key-value pair
    ht_insert(ht, "key1", "value1");
    ht_delete(ht, "key1");
    if (ht_search(ht, "key1") == NULL) {
        printf("Test passed for ht_delete\n");
    } else {
        printf("Test failed for ht_delete\n");
    }

    // Test deleting a key that doesn't exist
    ht_delete(ht, "key2");
    if (ht_search(ht, "key2") == NULL) {
        printf("Test passed for ht_delete (key not found)\n");
    } else {
        printf("Test failed for ht_delete (key not found)\n");
    }

    del_hash_table(ht);
}

int main() {
    test_ht_insert();
    test_ht_search();
    test_ht_delete();

    return 0;
}