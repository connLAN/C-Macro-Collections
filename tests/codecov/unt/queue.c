#include "utl/assert.h"
#include "utl/test.h"
#include "../src/queue.c"

CMC_CREATE_UNIT(queue_test, false, {
    CMC_CREATE_TEST(new, {
        queue *q = q_new(1000000);

        cmc_assert_not_equals(ptr, NULL, q);
        cmc_assert_not_equals(ptr, NULL, q->buffer);
        cmc_assert_equals(size_t, 1000000, q_capacity(q));
        cmc_assert_equals(size_t, 0, q_count(q));
        cmc_assert_not_equals(ptr, NULL, q->buffer);

        q_free(q);
    });

    CMC_CREATE_TEST(new[edge_case:capacity = 0], {
        queue *q = q_new(0);

        cmc_assert_equals(ptr, NULL, q);
    });

    CMC_CREATE_TEST(new[edge_case:capacity = UINT64_MAX], {
        queue *q = q_new(UINT64_MAX);

        cmc_assert_equals(ptr, NULL, q);
    });

    CMC_CREATE_TEST(clear[count capacity], {
        queue *q = q_new(100);

        cmc_assert_not_equals(ptr, NULL, q);

        for (size_t i = 0; i < 50; i++)
            cmc_assert(q_enqueue(q, i));

        cmc_assert_equals(size_t, 50, q_count(q));

        q_clear(q);

        cmc_assert_equals(size_t, 0, q_count(q));
        cmc_assert_equals(size_t, 100, q_capacity(q));

        q_free(q);
    });

    CMC_CREATE_TEST(buffer_growth[edge_case:capacity = 1], {
        queue *q = q_new(1);

        cmc_assert_not_equals(ptr, NULL, q);

        for (size_t i = 0; i < 50; i++)
            cmc_assert(q_enqueue(q, i));

        cmc_assert_equals(size_t, 50, q_count(q));

        q_free(q);
    });

});