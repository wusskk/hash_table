# Simple Hash Table in C

This is a simple implementation of a Hash Table in C.

The main implementation is derived from [Write a hash table in C](https://github.com/jamesroutley/write-a-hash-table).

## Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/hash-table.git
   ```

2. Run the `build.sh` file:
    ```bash
    # Only build libhash_table.so in package directory
    ./build.sh
    # Build the project and run tests.
    ./build.sh test
    # Only clean the build directory.
    ./build.sh clean
    # Clean the package tests/output and build directory.
    ./build.sh clean output        
    # Display this help message.
    ./build.sh help
   ```

## Function Documentation
- `void del_hash_table(hash_table* ht)`
    ```c
        Delete the hash table
- `hash_table* new_hash_table()`
    ```c
        Create a new hash table with a specific size of 53
- `void ht_insert(hash_table* ht, const char* k, const char* v)`
    ```c
        First, check if the capacity of the hash table exceeds 70%. If it is, double the capacity. 
        Then, insert the key-value pair. If the inserted value is a duplicate, the new value will overwrite the old one.
- `char* ht_search(hash_table* ht, const char* k)`
    ```c
        Query the value in the hash table based on the key.
- `void ht_delete(hash_table* ht, const char* k)`
    ```c
        First, delete the key-value pair.
        Then check if the capacity of the hash table is less than 10%. If it is, reduce it to half.
    ```
