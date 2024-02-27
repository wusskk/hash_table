/**
 * @file hash_table.c
 * @brief Implementation of a hash table data structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"
#include "prime.h"


static int BASE_SIZE = 53;
static int UP = 3;
static int DOWN = 4;

/**
 * @brief Creates a new ht_item structure.
 * @param k The key of the item.
 * @param v The value associated with the key.
 * @return A pointer to the newly created ht_item structure.
 */
static ht_item* new_ht_item(const char* k, const char* v) {
    ht_item* item = (ht_item*)malloc(sizeof(ht_item));
    if (item == NULL) {
        perror("Error: Failed to malloc item!\n");
        exit(EXIT_FAILURE);
    }

    item->key = strdup(k);
    if (item->key == NULL) {
        perror("Error: Failed to malloc key!\n");
        free(item);
        exit(EXIT_FAILURE);
    }

    item->value = strdup(v);
    if (item->value == NULL) {
        perror("Error: Failed to malloc key!\n");
        free(item->key);
        free(item);
        exit(EXIT_FAILURE);
    }

    return item;
}

/**
 * @brief Deletes an ht_item structure.
 * @param item A pointer to the ht_item structure to be deleted.
 */
static void del_ht_item(ht_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

/**
 * @brief Hashes a string using a specified prime number and the number of buckets.
 * @param str The string to be hashed.
 * @param a The prime number to be used in the hash function.
 * @param num_buckets The number of buckets in the hash table.
 * @return The hash value of the string.
 */
static int hash(const char* str, const int a, const int num_buckets) {
    long hash = 0;
    size_t string_len = strlen(str);
    for (size_t i = 0; i < string_len; i++) {
        hash += (long)pow(a, string_len - (i + 1)) * str[i];
    }
    hash = hash % num_buckets;
    return (int)hash;
}

/**
 * @brief Calculates the hash value for a given string and attempt number.
 * @param str The string to be hashed.
 * @param attempt The attempt number.
 * @param num_buckets The number of buckets in the hash table.
 * @return The hash value for the given string and attempt number.
 */
static int get_hash(const char* str, const int attempt, const int num_buckets) {
    int hash_a = hash(str, HT_PRIME_1, num_buckets);
    int hash_b = hash(str, HT_PRIME_2, num_buckets);
    // index = hash_a(string) + i * hash_b(string + 1) % num_buckets
    return (hash_a + attempt * (hash_b + 1)) % num_buckets;
}

/**
 * @brief Creates a new hash_table structure with a specified size.
 * @param size The size of the hash table.
 * @return A pointer to the newly created hash_table structure.
 */
static hash_table* new_ht_sized(int size) {
    hash_table* ht = (hash_table*)malloc(sizeof(hash_table));
    if (ht == NULL) {
        perror("Error: Failed to malloc hash table!\n");
        exit(EXIT_FAILURE);
    }

    ht->size = size;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));

    if (ht->items == NULL) {
        perror("Error: Failed to malloc items!\n");
        free(ht);
        exit(EXIT_FAILURE);
    }

    return ht;
}

/**
 * @brief Resizes the hash table.
 * @param ht A pointer to the hash table to be resized.
 * @param flag A flag indicating whether to increase or decrease the size of the hash table.
 */
static void resize_hash_table(hash_table* ht, int flag) {
    int new_size;

    if ((ht->count * 100 / ht->size) > 70 && flag == UP)
        new_size = next_prime(ht->size * 2);
    else if ((ht->count * 100 / ht->size) < 10 && flag == DOWN)
        new_size = next_prime(ht->size / 2);
    else
        return;

    hash_table* new_ht = new_ht_sized(new_size);

    ht_item* tmp;
    for (int i = 0; i < ht->size; i++) {
        tmp = ht->items[i];
        if (tmp) {
            ht_insert(new_ht, tmp->key, tmp->value);
        }
    }

    int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    del_hash_table(new_ht);

    return;
}

/**
 * @brief Deletes a hash_table structure.
 * @param ht A pointer to the hash_table structure to be deleted.
 */
void del_hash_table(hash_table* ht) {
    ht_item* item;
    for (int i = 0; i < ht->size; i++) {
        item = ht->items[i];
        if (item != NULL) {
            del_ht_item(item);
        }
    }
    free(ht->items);
    free(ht);
}

/**
 * @brief Creates a new hash_table structure.
 * @return A pointer to the newly created hash_table structure.
 */
hash_table* new_hash_table() {
    return new_ht_sized(BASE_SIZE);
}

/**
 * @brief Inserts a key-value pair into the hash table.
 * @param ht A pointer to the hash_table structure.
 * @param k The key of the item.
 * @param v The value associated with the key.
 */
void ht_insert(hash_table* ht, const char* k, const char* v) {
    resize_hash_table(ht, UP);

    ht_item* item = new_ht_item(k, v);
    int index = get_hash(k, 0, ht->size);
    int attempt = 1;

    ht_item* tmp = ht->items[index];

    while (tmp != NULL) {
        if (strcmp(tmp->key, k) == 0) {
            del_ht_item(tmp);
            break;
        }

        index = get_hash(k, attempt++, ht->size);
        tmp = ht->items[index];
    }

    ht->items[index] = item;
    ht->count++;
}

/**
 * @brief Searches for a key in the hash table.
 * @param ht A pointer to the hash_table structure.
 * @param k The key to search for.
 * @return The value associated with the key if found, otherwise NULL.
 */
char* ht_search(hash_table* ht, const char* k) {
    int index = get_hash(k, 0, ht->size);
    int attempt = 1;
    ht_item* tmp = ht->items[index];

    while (tmp != NULL) {
        if (strcmp(tmp->key, k) == 0)
            return tmp->value;

        index = get_hash(k, attempt++, ht->size);
        tmp = ht->items[index];
    }

    return NULL;
}

/**
 * @brief Deletes a key-value pair from the hash table.
 * @param ht A pointer to the hash_table structure.
 * @param k The key of the item to be deleted.
 */
void ht_delete(hash_table* ht, const char* k) {
    int index = get_hash(k, 0, ht->size);
    int attempt = 1;
    ht_item* tmp = ht->items[index];

    while (tmp != NULL) {
        if (strcmp(tmp->key, k) == 0) {
            del_ht_item(tmp);
            ht->items[index] = NULL;
            ht->count--;
        }
        index = get_hash(k, attempt++, ht->size);
        tmp = ht->items[index];
    }

    resize_hash_table(ht, DOWN);
    return;
}
