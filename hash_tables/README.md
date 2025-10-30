# C - Hash Tables

Task 0: `hash_table_create(unsigned long int size)`  
- Allocates a `hash_table_t` and an array of `hash_node_t *` buckets.  
- Uses `calloc` so all buckets start as `NULL`.  
- Returns `NULL` on any allocation failure or if `size == 0`.  
