/**
 * sortedlist.h
 *
 * Creation Date: 17/09/2019
 *
 * Authors:
 * Leonardo Vencovsky (https://github.com/LeoVen)
 *
 */

/**
 * SortedList
 *
 * A sorted list is a dynamic array, meaning that you can store as many elements
 * as you like and when its capacity is full, the buffer is reallocated. The
 * elements are only sorted when a certain action requires that the array is
 * sorted like accessing min() or max(). This prevents the array from being
 * sorted after every insertion or removal. The array is sorted using a
 * variation of quick sort that uses insertion sort for small partitions.
 */

#ifndef CMC_SORTEDLIST_H
#define CMC_SORTEDLIST_H

/* -------------------------------------------------------------------------
 * Core functionalities of the C Macro Collections Library
 * ------------------------------------------------------------------------- */
#include "../cor/core.h"

/* -------------------------------------------------------------------------
 * SortedList specific
 * ------------------------------------------------------------------------- */
/* to_string format */
static const char *cmc_string_fmt_sortedlist = "struct %s<%s> "
                                               "at %p { "
                                               "buffer:%p, "
                                               "capacity:%" PRIuMAX ", "
                                               "count:%" PRIuMAX ", "
                                               "is_sorted:%s, "
                                               "flag:%d, "
                                               "f_val:%p, "
                                               "alloc:%p, "
                                               "callbacks:%p }";

#define CMC_GENERATE_SORTEDLIST(PFX, SNAME, V)    \
    CMC_GENERATE_SORTEDLIST_HEADER(PFX, SNAME, V) \
    CMC_GENERATE_SORTEDLIST_SOURCE(PFX, SNAME, V)

#define CMC_WRAPGEN_SORTEDLIST_HEADER(PFX, SNAME, K, V) \
    CMC_GENERATE_SORTEDLIST_HEADER(PFX, SNAME, V)

#define CMC_WRAPGEN_SORTEDLIST_SOURCE(PFX, SNAME, K, V) \
    CMC_GENERATE_SORTEDLIST_SOURCE(PFX, SNAME, V)

/* -------------------------------------------------------------------------
 * Header
 * ------------------------------------------------------------------------- */
#define CMC_GENERATE_SORTEDLIST_HEADER(PFX, SNAME, V)                        \
                                                                             \
    /* List Structure */                                                     \
    struct SNAME                                                             \
    {                                                                        \
        /* Dynamic array of elements */                                      \
        V *buffer;                                                           \
                                                                             \
        /* Current array capacity */                                         \
        size_t capacity;                                                     \
                                                                             \
        /* Current amount of elements */                                     \
        size_t count;                                                        \
                                                                             \
        /* Flag if the list is sorted or not, used by lazy evaluation */     \
        bool is_sorted;                                                      \
                                                                             \
        /* Flags indicating errors or success */                             \
        int flag;                                                            \
                                                                             \
        /* Value function table */                                           \
        struct SNAME##_fval *f_val;                                          \
                                                                             \
        /* Custom allocation functions */                                    \
        struct cmc_alloc_node *alloc;                                        \
                                                                             \
        /* Custom callback functions */                                      \
        struct cmc_callbacks *callbacks;                                     \
    };                                                                       \
                                                                             \
    /* Value struct function table */                                        \
    struct SNAME##_fval                                                      \
    {                                                                        \
        /* Comparator function */                                            \
        int (*cmp)(V, V);                                                    \
                                                                             \
        /* Copy function */                                                  \
        V (*cpy)(V);                                                         \
                                                                             \
        /* To string function */                                             \
        bool (*str)(FILE *, V);                                              \
                                                                             \
        /* Free from memory function */                                      \
        void (*free)(V);                                                     \
                                                                             \
        /* Hash function */                                                  \
        size_t (*hash)(V);                                                   \
                                                                             \
        /* Priority function */                                              \
        int (*pri)(V, V);                                                    \
    };                                                                       \
                                                                             \
    /* List Iterator */                                                      \
    struct SNAME##_iter                                                      \
    {                                                                        \
        /* Target list */                                                    \
        struct SNAME *target;                                                \
                                                                             \
        /* Cursor's position (index) */                                      \
        size_t cursor;                                                       \
                                                                             \
        /* If the iterator has reached the start of the iteration */         \
        bool start;                                                          \
                                                                             \
        /* If the iterator has reached the end of the iteration */           \
        bool end;                                                            \
    };                                                                       \
                                                                             \
    /* Collection Functions */                                               \
    /* Collection Allocation and Deallocation */                             \
    struct SNAME *PFX##_new(size_t capacity, struct SNAME##_fval *f_val);    \
    struct SNAME *PFX##_new_custom(                                          \
        size_t capacity, struct SNAME##_fval *f_val,                         \
        struct cmc_alloc_node *alloc, struct cmc_callbacks *callbacks);      \
    void PFX##_clear(struct SNAME *_list_);                                  \
    void PFX##_free(struct SNAME *_list_);                                   \
    /* Customization of Allocation and Callbacks */                          \
    void PFX##_customize(struct SNAME *_list_, struct cmc_alloc_node *alloc, \
                         struct cmc_callbacks *callbacks);                   \
    /* Collection Input and Output */                                        \
    bool PFX##_insert(struct SNAME *_list_, V value);                        \
    bool PFX##_remove(struct SNAME *_list_, size_t index);                   \
    /* Element Access */                                                     \
    V PFX##_max(struct SNAME *_list_);                                       \
    V PFX##_min(struct SNAME *_list_);                                       \
    V PFX##_get(struct SNAME *_list_, size_t index);                         \
    size_t PFX##_index_of(struct SNAME *_list_, V value, bool from_start);   \
    /* Collection State */                                                   \
    bool PFX##_contains(struct SNAME *_list_, V value);                      \
    bool PFX##_empty(struct SNAME *_list_);                                  \
    bool PFX##_full(struct SNAME *_list_);                                   \
    size_t PFX##_count(struct SNAME *_list_);                                \
    size_t PFX##_capacity(struct SNAME *_list_);                             \
    int PFX##_flag(struct SNAME *_list_);                                    \
    /* Collection Utility */                                                 \
    bool PFX##_resize(struct SNAME *_list_, size_t capacity);                \
    void PFX##_sort(struct SNAME *_list_);                                   \
    struct SNAME *PFX##_copy_of(struct SNAME *_list_);                       \
    bool PFX##_equals(struct SNAME *_list1_, struct SNAME *_list2_);         \
    struct cmc_string PFX##_to_string(struct SNAME *_list_);                 \
    bool PFX##_print(struct SNAME *_list_, FILE *fptr);                      \
                                                                             \
    /* Iterator Functions */                                                 \
    /* Iterator Initialization */                                            \
    struct SNAME##_iter PFX##_iter_start(struct SNAME *target);              \
    struct SNAME##_iter PFX##_iter_end(struct SNAME *target);                \
    /* Iterator State */                                                     \
    bool PFX##_iter_at_start(struct SNAME##_iter *iter);                     \
    bool PFX##_iter_at_end(struct SNAME##_iter *iter);                       \
    /* Iterator Movement */                                                  \
    bool PFX##_iter_to_start(struct SNAME##_iter *iter);                     \
    bool PFX##_iter_to_end(struct SNAME##_iter *iter);                       \
    bool PFX##_iter_next(struct SNAME##_iter *iter);                         \
    bool PFX##_iter_prev(struct SNAME##_iter *iter);                         \
    bool PFX##_iter_advance(struct SNAME##_iter *iter, size_t steps);        \
    bool PFX##_iter_rewind(struct SNAME##_iter *iter, size_t steps);         \
    bool PFX##_iter_go_to(struct SNAME##_iter *iter, size_t index);          \
    /* Iterator Access */                                                    \
    V PFX##_iter_value(struct SNAME##_iter *iter);                           \
    size_t PFX##_iter_index(struct SNAME##_iter *iter);

/* -------------------------------------------------------------------------
 * Source
 * ------------------------------------------------------------------------- */
#define CMC_GENERATE_SORTEDLIST_SOURCE(PFX, SNAME, V)                          \
                                                                               \
    /* Implementation Detail Functions */                                      \
    static size_t PFX##_impl_binary_search_first(struct SNAME *_list_,         \
                                                 V value);                     \
    static size_t PFX##_impl_binary_search_last(struct SNAME *_list_,          \
                                                V value);                      \
    void PFX##_impl_sort_quicksort(V *array, int (*cmp)(V, V), size_t low,     \
                                   size_t high);                               \
    void PFX##_impl_sort_insertion(V *array, int (*cmp)(V, V), size_t low,     \
                                   size_t high);                               \
                                                                               \
    struct SNAME *PFX##_new(size_t capacity, struct SNAME##_fval *f_val)       \
    {                                                                          \
        struct cmc_alloc_node *alloc = &cmc_alloc_node_default;                \
                                                                               \
        if (capacity < 1)                                                      \
            return NULL;                                                       \
                                                                               \
        if (!f_val)                                                            \
            return NULL;                                                       \
                                                                               \
        struct SNAME *_list_ = alloc->malloc(sizeof(struct SNAME));            \
                                                                               \
        if (!_list_)                                                           \
            return NULL;                                                       \
                                                                               \
        _list_->buffer = alloc->calloc(capacity, sizeof(V));                   \
                                                                               \
        if (!_list_->buffer)                                                   \
        {                                                                      \
            alloc->free(_list_);                                               \
            return NULL;                                                       \
        }                                                                      \
                                                                               \
        _list_->capacity = capacity;                                           \
        _list_->count = 0;                                                     \
        _list_->is_sorted = false;                                             \
        _list_->flag = cmc_flags.OK;                                           \
        _list_->f_val = f_val;                                                 \
        _list_->alloc = alloc;                                                 \
        _list_->callbacks = NULL;                                              \
                                                                               \
        return _list_;                                                         \
    }                                                                          \
                                                                               \
    struct SNAME *PFX##_new_custom(                                            \
        size_t capacity, struct SNAME##_fval *f_val,                           \
        struct cmc_alloc_node *alloc, struct cmc_callbacks *callbacks)         \
    {                                                                          \
        if (capacity < 1)                                                      \
            return NULL;                                                       \
                                                                               \
        if (!alloc)                                                            \
            alloc = &cmc_alloc_node_default;                                   \
                                                                               \
        struct SNAME *_list_ = alloc->malloc(sizeof(struct SNAME));            \
                                                                               \
        if (!_list_)                                                           \
            return NULL;                                                       \
                                                                               \
        _list_->buffer = alloc->calloc(capacity, sizeof(V));                   \
                                                                               \
        if (!_list_->buffer)                                                   \
        {                                                                      \
            alloc->free(_list_);                                               \
            return NULL;                                                       \
        }                                                                      \
                                                                               \
        _list_->capacity = capacity;                                           \
        _list_->count = 0;                                                     \
        _list_->is_sorted = false;                                             \
        _list_->flag = cmc_flags.OK;                                           \
        _list_->f_val = f_val;                                                 \
        _list_->alloc = alloc;                                                 \
        _list_->callbacks = callbacks;                                         \
                                                                               \
        return _list_;                                                         \
    }                                                                          \
                                                                               \
    void PFX##_clear(struct SNAME *_list_)                                     \
    {                                                                          \
        if (_list_->f_val->free)                                               \
        {                                                                      \
            for (size_t i = 0; i < _list_->count; i++)                         \
                _list_->f_val->free(_list_->buffer[i]);                        \
        }                                                                      \
                                                                               \
        memset(_list_->buffer, 0, sizeof(V) * _list_->capacity);               \
                                                                               \
        _list_->count = 0;                                                     \
        _list_->flag = cmc_flags.OK;                                           \
    }                                                                          \
                                                                               \
    void PFX##_free(struct SNAME *_list_)                                      \
    {                                                                          \
        if (_list_->f_val->free)                                               \
        {                                                                      \
            for (size_t i = 0; i < _list_->count; i++)                         \
                _list_->f_val->free(_list_->buffer[i]);                        \
        }                                                                      \
                                                                               \
        _list_->alloc->free(_list_->buffer);                                   \
        _list_->alloc->free(_list_);                                           \
    }                                                                          \
                                                                               \
    void PFX##_customize(struct SNAME *_list_, struct cmc_alloc_node *alloc,   \
                         struct cmc_callbacks *callbacks)                      \
    {                                                                          \
        if (!alloc)                                                            \
            _list_->alloc = &cmc_alloc_node_default;                           \
        else                                                                   \
            _list_->alloc = alloc;                                             \
                                                                               \
        _list_->callbacks = callbacks;                                         \
                                                                               \
        _list_->flag = cmc_flags.OK;                                           \
    }                                                                          \
                                                                               \
    bool PFX##_insert(struct SNAME *_list_, V value)                           \
    {                                                                          \
        if (PFX##_full(_list_))                                                \
        {                                                                      \
            if (!PFX##_resize(_list_, _list_->capacity * 2))                   \
                return false;                                                  \
        }                                                                      \
                                                                               \
        _list_->buffer[_list_->count++] = value;                               \
                                                                               \
        _list_->is_sorted = false;                                             \
        _list_->flag = cmc_flags.OK;                                           \
                                                                               \
        if (_list_->callbacks && _list_->callbacks->create)                    \
            _list_->callbacks->create();                                       \
                                                                               \
        return true;                                                           \
    }                                                                          \
                                                                               \
    bool PFX##_remove(struct SNAME *_list_, size_t index)                      \
    {                                                                          \
        if (PFX##_empty(_list_))                                               \
        {                                                                      \
            _list_->flag = cmc_flags.EMPTY;                                    \
            return false;                                                      \
        }                                                                      \
                                                                               \
        if (index >= _list_->count)                                            \
        {                                                                      \
            _list_->flag = cmc_flags.RANGE;                                    \
            return false;                                                      \
        }                                                                      \
                                                                               \
        memmove(_list_->buffer + index, _list_->buffer + index + 1,            \
                (_list_->count - index) * sizeof(V));                          \
                                                                               \
        _list_->buffer[--_list_->count] = (V){ 0 };                            \
                                                                               \
        _list_->flag = cmc_flags.OK;                                           \
                                                                               \
        if (_list_->callbacks && _list_->callbacks->delete)                    \
            _list_->callbacks->delete ();                                      \
                                                                               \
        return true;                                                           \
    }                                                                          \
                                                                               \
    V PFX##_max(struct SNAME *_list_)                                          \
    {                                                                          \
        if (PFX##_empty(_list_))                                               \
        {                                                                      \
            _list_->flag = cmc_flags.EMPTY;                                    \
            return (V){ 0 };                                                   \
        }                                                                      \
                                                                               \
        PFX##_sort(_list_);                                                    \
                                                                               \
        _list_->flag = cmc_flags.OK;                                           \
                                                                               \
        if (_list_->callbacks && _list_->callbacks->read)                      \
            _list_->callbacks->read();                                         \
                                                                               \
        return _list_->buffer[_list_->count - 1];                              \
    }                                                                          \
                                                                               \
    V PFX##_min(struct SNAME *_list_)                                          \
    {                                                                          \
        if (PFX##_empty(_list_))                                               \
        {                                                                      \
            _list_->flag = cmc_flags.EMPTY;                                    \
            return (V){ 0 };                                                   \
        }                                                                      \
                                                                               \
        PFX##_sort(_list_);                                                    \
                                                                               \
        _list_->flag = cmc_flags.OK;                                           \
                                                                               \
        if (_list_->callbacks && _list_->callbacks->read)                      \
            _list_->callbacks->read();                                         \
                                                                               \
        return _list_->buffer[0];                                              \
    }                                                                          \
                                                                               \
    V PFX##_get(struct SNAME *_list_, size_t index)                            \
    {                                                                          \
        if (PFX##_empty(_list_))                                               \
        {                                                                      \
            _list_->flag = cmc_flags.EMPTY;                                    \
            return (V){ 0 };                                                   \
        }                                                                      \
                                                                               \
        if (index >= _list_->count)                                            \
        {                                                                      \
            _list_->flag = cmc_flags.RANGE;                                    \
            return (V){ 0 };                                                   \
        }                                                                      \
                                                                               \
        PFX##_sort(_list_);                                                    \
                                                                               \
        _list_->flag = cmc_flags.OK;                                           \
                                                                               \
        if (_list_->callbacks && _list_->callbacks->read)                      \
            _list_->callbacks->read();                                         \
                                                                               \
        return _list_->buffer[index];                                          \
    }                                                                          \
                                                                               \
    size_t PFX##_index_of(struct SNAME *_list_, V value, bool from_start)      \
    {                                                                          \
        _list_->flag = cmc_flags.OK;                                           \
                                                                               \
        PFX##_sort(_list_);                                                    \
                                                                               \
        if (_list_->callbacks && _list_->callbacks->read)                      \
            _list_->callbacks->read();                                         \
                                                                               \
        if (from_start)                                                        \
        {                                                                      \
            return PFX##_impl_binary_search_first(_list_, value);              \
        }                                                                      \
                                                                               \
        return PFX##_impl_binary_search_last(_list_, value);                   \
    }                                                                          \
                                                                               \
    bool PFX##_contains(struct SNAME *_list_, V value)                         \
    {                                                                          \
        _list_->flag = cmc_flags.OK;                                           \
                                                                               \
        if (PFX##_empty(_list_))                                               \
            return false;                                                      \
                                                                               \
        PFX##_sort(_list_);                                                    \
                                                                               \
        if (_list_->callbacks && _list_->callbacks->read)                      \
            _list_->callbacks->read();                                         \
                                                                               \
        return PFX##_impl_binary_search_first(_list_, value) < _list_->count;  \
    }                                                                          \
                                                                               \
    bool PFX##_empty(struct SNAME *_list_)                                     \
    {                                                                          \
        return _list_->count == 0;                                             \
    }                                                                          \
                                                                               \
    bool PFX##_full(struct SNAME *_list_)                                      \
    {                                                                          \
        return _list_->count >= _list_->capacity;                              \
    }                                                                          \
                                                                               \
    size_t PFX##_count(struct SNAME *_list_)                                   \
    {                                                                          \
        return _list_->count;                                                  \
    }                                                                          \
                                                                               \
    size_t PFX##_capacity(struct SNAME *_list_)                                \
    {                                                                          \
        return _list_->capacity;                                               \
    }                                                                          \
                                                                               \
    int PFX##_flag(struct SNAME *_list_)                                       \
    {                                                                          \
        return _list_->flag;                                                   \
    }                                                                          \
                                                                               \
    bool PFX##_resize(struct SNAME *_list_, size_t capacity)                   \
    {                                                                          \
        if (_list_->capacity == capacity)                                      \
            goto success;                                                      \
                                                                               \
        if (capacity < _list_->count)                                          \
        {                                                                      \
            _list_->flag = cmc_flags.INVALID;                                  \
            return false;                                                      \
        }                                                                      \
                                                                               \
        V *new_buffer =                                                        \
            _list_->alloc->realloc(_list_->buffer, sizeof(V) * capacity);      \
                                                                               \
        if (!new_buffer)                                                       \
        {                                                                      \
            _list_->flag = cmc_flags.ALLOC;                                    \
            return false;                                                      \
        }                                                                      \
                                                                               \
        /* TODO zero out remaining slots */                                    \
                                                                               \
        _list_->buffer = new_buffer;                                           \
        _list_->capacity = capacity;                                           \
                                                                               \
    success:                                                                   \
                                                                               \
        _list_->flag = cmc_flags.OK;                                           \
                                                                               \
        if (_list_->callbacks && _list_->callbacks->resize)                    \
            _list_->callbacks->resize();                                       \
                                                                               \
        return true;                                                           \
    }                                                                          \
                                                                               \
    void PFX##_sort(struct SNAME *_list_)                                      \
    {                                                                          \
        _list_->flag = cmc_flags.OK;                                           \
                                                                               \
        if (!_list_->is_sorted && _list_->count > 1)                           \
        {                                                                      \
            PFX##_impl_sort_quicksort(_list_->buffer, _list_->f_val->cmp, 0,   \
                                      _list_->count - 1);                      \
                                                                               \
            _list_->is_sorted = true;                                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    struct SNAME *PFX##_copy_of(struct SNAME *_list_)                          \
    {                                                                          \
        struct SNAME *result =                                                 \
            PFX##_new_custom(_list_->capacity, _list_->f_val, _list_->alloc,   \
                             _list_->callbacks);                               \
                                                                               \
        if (!result)                                                           \
        {                                                                      \
            _list_->flag = cmc_flags.ERROR;                                    \
            return NULL;                                                       \
        }                                                                      \
                                                                               \
        if (_list_->f_val->cpy)                                                \
        {                                                                      \
            for (size_t i = 0; i < _list_->count; i++)                         \
                result->buffer[i] = _list_->f_val->cpy(_list_->buffer[i]);     \
        }                                                                      \
        else                                                                   \
            memcpy(result->buffer, _list_->buffer, sizeof(V) * _list_->count); \
                                                                               \
        result->count = _list_->count;                                         \
                                                                               \
        _list_->flag = cmc_flags.OK;                                           \
                                                                               \
        return result;                                                         \
    }                                                                          \
                                                                               \
    bool PFX##_equals(struct SNAME *_list1_, struct SNAME *_list2_)            \
    {                                                                          \
        if (_list1_->count != _list2_->count)                                  \
            return false;                                                      \
                                                                               \
        PFX##_sort(_list1_);                                                   \
        PFX##_sort(_list2_);                                                   \
                                                                               \
        for (size_t i = 0; i < _list1_->count; i++)                            \
        {                                                                      \
            if (_list1_->f_val->cmp(_list1_->buffer[i], _list2_->buffer[i]) != \
                0)                                                             \
                return false;                                                  \
        }                                                                      \
                                                                               \
        return true;                                                           \
    }                                                                          \
                                                                               \
    struct cmc_string PFX##_to_string(struct SNAME *_list_)                    \
    {                                                                          \
        struct cmc_string str;                                                 \
        struct SNAME *l_ = _list_;                                             \
                                                                               \
        int n = snprintf(str.s, cmc_string_len, cmc_string_fmt_sortedlist,     \
                         #SNAME, #V, l_, l_->buffer, l_->capacity, l_->count,  \
                         l_->is_sorted ? "true" : "false", l_->flag,           \
                         l_->f_val, l_->alloc, l_->callbacks);                 \
                                                                               \
        return n >= 0 ? str : (struct cmc_string){ 0 };                        \
    }                                                                          \
                                                                               \
    bool PFX##_print(struct SNAME *_list_, FILE *fptr)                         \
    {                                                                          \
        PFX##_sort(_list_);                                                    \
                                                                               \
        for (size_t i = 0; i < _list_->count; i++)                             \
        {                                                                      \
            if (!_list_->f_val->str(fptr, _list_->buffer[i]))                  \
                return false;                                                  \
        }                                                                      \
                                                                               \
        return true;                                                           \
    }                                                                          \
                                                                               \
    struct SNAME##_iter PFX##_iter_start(struct SNAME *target)                 \
    {                                                                          \
        PFX##_sort(target);                                                    \
                                                                               \
        struct SNAME##_iter iter;                                              \
                                                                               \
        iter.target = target;                                                  \
        iter.cursor = 0;                                                       \
        iter.start = true;                                                     \
        iter.end = PFX##_empty(target);                                        \
                                                                               \
        return iter;                                                           \
    }                                                                          \
                                                                               \
    struct SNAME##_iter PFX##_iter_end(struct SNAME *target)                   \
    {                                                                          \
        PFX##_sort(target);                                                    \
                                                                               \
        struct SNAME##_iter iter;                                              \
                                                                               \
        iter.target = target;                                                  \
        iter.cursor = 0;                                                       \
        iter.start = PFX##_empty(target);                                      \
        iter.end = true;                                                       \
                                                                               \
        if (!PFX##_empty(target))                                              \
            iter.cursor = target->count - 1;                                   \
                                                                               \
        return iter;                                                           \
    }                                                                          \
                                                                               \
    bool PFX##_iter_at_start(struct SNAME##_iter *iter)                        \
    {                                                                          \
        return PFX##_empty(iter->target) || iter->start;                       \
    }                                                                          \
                                                                               \
    bool PFX##_iter_at_end(struct SNAME##_iter *iter)                          \
    {                                                                          \
        return PFX##_empty(iter->target) || iter->end;                         \
    }                                                                          \
                                                                               \
    bool PFX##_iter_to_start(struct SNAME##_iter *iter)                        \
    {                                                                          \
        if (!PFX##_empty(iter->target))                                        \
        {                                                                      \
            iter->cursor = 0;                                                  \
            iter->start = true;                                                \
            iter->end = PFX##_empty(iter->target);                             \
                                                                               \
            return true;                                                       \
        }                                                                      \
                                                                               \
        return false;                                                          \
    }                                                                          \
                                                                               \
    bool PFX##_iter_to_end(struct SNAME##_iter *iter)                          \
    {                                                                          \
        if (!PFX##_empty(iter->target))                                        \
        {                                                                      \
            iter->start = PFX##_empty(iter->target);                           \
            iter->cursor = iter->target->count - 1;                            \
            iter->end = true;                                                  \
                                                                               \
            return true;                                                       \
        }                                                                      \
                                                                               \
        return false;                                                          \
    }                                                                          \
                                                                               \
    bool PFX##_iter_next(struct SNAME##_iter *iter)                            \
    {                                                                          \
        if (iter->end)                                                         \
            return false;                                                      \
                                                                               \
        if (iter->cursor + 1 == iter->target->count)                           \
        {                                                                      \
            iter->end = true;                                                  \
            return false;                                                      \
        }                                                                      \
                                                                               \
        iter->start = PFX##_empty(iter->target);                               \
                                                                               \
        iter->cursor++;                                                        \
                                                                               \
        return true;                                                           \
    }                                                                          \
                                                                               \
    bool PFX##_iter_prev(struct SNAME##_iter *iter)                            \
    {                                                                          \
        if (iter->start)                                                       \
            return false;                                                      \
                                                                               \
        if (iter->cursor == 0)                                                 \
        {                                                                      \
            iter->start = true;                                                \
            return false;                                                      \
        }                                                                      \
                                                                               \
        iter->end = PFX##_empty(iter->target);                                 \
                                                                               \
        iter->cursor--;                                                        \
                                                                               \
        return true;                                                           \
    }                                                                          \
                                                                               \
    /* Returns true only if the iterator moved */                              \
    bool PFX##_iter_advance(struct SNAME##_iter *iter, size_t steps)           \
    {                                                                          \
        if (iter->end)                                                         \
            return false;                                                      \
                                                                               \
        if (iter->cursor + 1 == iter->target->count)                           \
        {                                                                      \
            iter->end = true;                                                  \
            return false;                                                      \
        }                                                                      \
                                                                               \
        if (steps == 0 || iter->cursor + steps >= iter->target->count)         \
            return false;                                                      \
                                                                               \
        iter->start = PFX##_empty(iter->target);                               \
                                                                               \
        iter->cursor += steps;                                                 \
                                                                               \
        return true;                                                           \
    }                                                                          \
                                                                               \
    /* Returns true only if the iterator moved */                              \
    bool PFX##_iter_rewind(struct SNAME##_iter *iter, size_t steps)            \
    {                                                                          \
        if (iter->start)                                                       \
            return false;                                                      \
                                                                               \
        if (iter->cursor == 0)                                                 \
        {                                                                      \
            iter->start = true;                                                \
            return false;                                                      \
        }                                                                      \
                                                                               \
        if (steps == 0 || iter->cursor < steps)                                \
            return false;                                                      \
                                                                               \
        iter->end = PFX##_empty(iter->target);                                 \
                                                                               \
        iter->cursor -= steps;                                                 \
                                                                               \
        return true;                                                           \
    }                                                                          \
                                                                               \
    /* Returns true only if the iterator was able to be positioned at the */   \
    /* given index */                                                          \
    bool PFX##_iter_go_to(struct SNAME##_iter *iter, size_t index)             \
    {                                                                          \
        if (index >= iter->target->count)                                      \
            return false;                                                      \
                                                                               \
        if (iter->cursor > index)                                              \
            return PFX##_iter_rewind(iter, iter->cursor - index);              \
        else if (iter->cursor < index)                                         \
            return PFX##_iter_advance(iter, index - iter->cursor);             \
                                                                               \
        return true;                                                           \
    }                                                                          \
                                                                               \
    V PFX##_iter_value(struct SNAME##_iter *iter)                              \
    {                                                                          \
        if (PFX##_empty(iter->target))                                         \
            return (V){ 0 };                                                   \
                                                                               \
        return iter->target->buffer[iter->cursor];                             \
    }                                                                          \
                                                                               \
    size_t PFX##_iter_index(struct SNAME##_iter *iter)                         \
    {                                                                          \
        return iter->cursor;                                                   \
    }                                                                          \
                                                                               \
    static size_t PFX##_impl_binary_search_first(struct SNAME *_list_,         \
                                                 V value)                      \
    {                                                                          \
        if (PFX##_empty(_list_))                                               \
            return 1;                                                          \
                                                                               \
        size_t L = 0;                                                          \
        size_t R = _list_->count;                                              \
                                                                               \
        while (L < R)                                                          \
        {                                                                      \
            size_t M = L + (R - L) / 2;                                        \
                                                                               \
            if (_list_->f_val->cmp(_list_->buffer[M], value) < 0)              \
                L = M + 1;                                                     \
            else                                                               \
                R = M;                                                         \
        }                                                                      \
                                                                               \
        if (_list_->f_val->cmp(_list_->buffer[L], value) == 0)                 \
            return L;                                                          \
                                                                               \
        /* Not found */                                                        \
        return _list_->count;                                                  \
    }                                                                          \
                                                                               \
    static size_t PFX##_impl_binary_search_last(struct SNAME *_list_, V value) \
    {                                                                          \
        if (PFX##_empty(_list_))                                               \
            return 1;                                                          \
                                                                               \
        size_t L = 0;                                                          \
        size_t R = _list_->count;                                              \
                                                                               \
        while (L < R)                                                          \
        {                                                                      \
            size_t M = L + (R - L) / 2;                                        \
                                                                               \
            if (_list_->f_val->cmp(_list_->buffer[M], value) > 0)              \
                R = M;                                                         \
            else                                                               \
                L = M + 1;                                                     \
        }                                                                      \
                                                                               \
        if (L > 0 && _list_->f_val->cmp(_list_->buffer[L - 1], value) == 0)    \
            return L - 1;                                                      \
                                                                               \
        /* Not found */                                                        \
        return _list_->count;                                                  \
    }                                                                          \
                                                                               \
    /* Characteristics of this quicksort implementation: */                    \
    /* - Hybrid: uses insertion sort for small arrays */                       \
    /* - Partition: Lomuto's Method */                                         \
    /* - Tail recursion: minimize recursion depth */                           \
    void PFX##_impl_sort_quicksort(V *array, int (*cmp)(V, V), size_t low,     \
                                   size_t high)                                \
    {                                                                          \
        while (low < high)                                                     \
        {                                                                      \
            /* Quicksort performs poorly for smaller arrays so let */          \
            /* insertion sort do the job */                                    \
            if (high - low < 10)                                               \
            {                                                                  \
                PFX##_impl_sort_insertion(array, cmp, low, high);              \
                break;                                                         \
            }                                                                  \
            else                                                               \
            {                                                                  \
                /* Partition */                                                \
                V pivot = array[high];                                         \
                                                                               \
                size_t pindex = low;                                           \
                                                                               \
                for (size_t i = low; i < high; i++)                            \
                {                                                              \
                    if (cmp(array[i], pivot) <= 0)                             \
                    {                                                          \
                        V _tmp_ = array[i];                                    \
                        array[i] = array[pindex];                              \
                        array[pindex] = _tmp_;                                 \
                                                                               \
                        pindex++;                                              \
                    }                                                          \
                }                                                              \
                                                                               \
                V _tmp_ = array[pindex];                                       \
                array[pindex] = array[high];                                   \
                array[high] = _tmp_;                                           \
                                                                               \
                /* Tail recursion */                                           \
                if (pindex - low < high - pindex)                              \
                {                                                              \
                    PFX##_impl_sort_quicksort(array, cmp, low, pindex - 1);    \
                                                                               \
                    low = pindex + 1;                                          \
                }                                                              \
                else                                                           \
                {                                                              \
                    PFX##_impl_sort_quicksort(array, cmp, pindex + 1, high);   \
                                                                               \
                    high = pindex - 1;                                         \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void PFX##_impl_sort_insertion(V *array, int (*cmp)(V, V), size_t low,     \
                                   size_t high)                                \
    {                                                                          \
        for (size_t i = low + 1; i <= high; i++)                               \
        {                                                                      \
            V _tmp_ = array[i];                                                \
            size_t j = i;                                                      \
                                                                               \
            while (j > low && cmp(array[j - 1], _tmp_) > 0)                    \
            {                                                                  \
                array[j] = array[j - 1];                                       \
                j--;                                                           \
            }                                                                  \
                                                                               \
            array[j] = _tmp_;                                                  \
        }                                                                      \
    }

#endif /* CMC_SORTEDLIST_H */
