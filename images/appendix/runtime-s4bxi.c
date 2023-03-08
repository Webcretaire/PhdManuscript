#include "config.h"
#include <s4bxi/s4bxi_c_util.h>
#include "runtime.h"
#include "shmem_internal.h"
#include "uthash.h"

struct keyval_entry
{
    size_t length;
    void* value;
};
typedef struct keyval_entry keyval_entry_t;

int shmem_runtime_init(int enable_node_ranks)
{
    return 0;
}

int shmem_runtime_fini(void)
{
    return 0;
}

void shmem_runtime_abort(int exit_code, const char msg[])
{
    s4bxi_fprintf(stderr, "%s\n", msg);
    s4bxi_exit(exit_code);
}

int shmem_runtime_get_rank(void)
{
    return s4bxi_get_my_rank();
}

int shmem_runtime_get_size(void)
{
    return s4bxi_get_rank_number();
}

int shmem_runtime_get_node_rank(int pe)
{
    shmem_internal_assert(pe < s4bxi_get_rank_number() && pe >= 0);
    return pe;
}

int shmem_runtime_get_node_size(void)
{
    return 1;
}

int shmem_runtime_exchange(void)
{
    return 0;
}

int shmem_runtime_put(char *key, void *value, size_t valuelen)
{
    keyval_entry_t *v = (keyval_entry_t *)malloc(sizeof(keyval_entry_t));
    v->length = valuelen;
    v->value = value;

    s4bxi_keyval_store_pointer(key, v);

    return 0;
}

int shmem_runtime_get(int pe, char *key, void *value, size_t valuelen)
{
    keyval_entry_t *v = (keyval_entry_t *)s4bxi_keyval_fetch_pointer(pe, key);

    if (!v || valuelen < v->length) 
        return 1;
    memcpy(value, v->value, v->length);

    return 0;
}

void shmem_runtime_barrier(void)
{
    s4bxi_barrier();
}