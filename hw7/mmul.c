#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

// Search TODO to find the locations where code needs to be completed

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
    unsigned int s;
    unsigned int e;
} thread_arg_t;

static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t *data = (thread_arg_t *)p_arg;
    unsigned int mid = data->m->nrows / 2;

    if (data->id == 1) data->s = 0, data->e = mid;
    else data->s = mid, data->e = data->m->nrows;

    for (unsigned int i = data->s; i < data->e; i++) {
        for (unsigned int j = 0; j < data->t->ncols; j++) {
            TElement sum = (TElement)0;
            for (unsigned int k = 0; k < data->m->ncols; k++) {
                sum += data->m->data[i][k] * data->n->data[k][j];
            }
            data->t->data[i][j] = sum;
        }
    }

    return NULL;
}

/* Return the sum of two matrices.
 *
 * If any pthread function fails, report error and exit. 
 * Return NULL if anything else is wrong.
 *
 * Similar to mulMatrix, but with multi-threading.
 */
TMatrix * mulMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->ncols != n->nrows )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, n->ncols);
    if (t == NULL)
        return t;

    // TODO
    pthread_t threads[NUM_THREADS];
    thread_arg_t dataThread[NUM_THREADS];

    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        dataThread[i].id = i + 1;
        dataThread[i].m = m;
        dataThread[i].n = n;
        dataThread[i].t = t;

        if (pthread_create(&threads[i], NULL, thread_main, &dataThread[i]) != 0) {
            for (unsigned int j = 0; j < i; j++) pthread_cancel(threads[j]);
            return NULL;
        }
    }

    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) return NULL;
    }
    return t;
}