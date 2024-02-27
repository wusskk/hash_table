#define HT_PRIME_1 157
#define HT_PRIME_2 199


/**
 * @struct ht_item
 * @brief Structure representing a key-value pair in the hash table.
 */
typedef struct
{
    char* key;
    char* value;
} ht_item;


/**
 * @struct hash_table
 * @brief Structure representing a hash table.
 */
typedef struct
{
    int size;
    int count;
    ht_item** items;
} hash_table;

void del_hash_table(hash_table* ht);
hash_table* new_hash_table();

// method
void ht_insert(hash_table* ht, const char* k, const char* v);
char* ht_search(hash_table* ht, const char* k);
void ht_delete(hash_table* ht, const char* k);