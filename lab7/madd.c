#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

#define NUM_THREADS 2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
    unsigned int start;
    unsigned int end;
} thread_arg_t;

static void *thread_main(void *p_arg) {

    // TODO

    thread_arg_t *data = (thread_arg_t *)p_arg;
    unsigned int mid = data->m->nrows / 2;

    if (data->id == 1) data->start = 0, data->end = mid;
    else data->start = mid, data->end = data->m->nrows;

    for (unsigned int i = data->start; i < data->end; i++) {
        for (unsigned int j = 0; j < data->m->ncols; j++) {
            data->t->data[i][j] = data->m->data[i][j] + data->n->data[i][j];
        }
    }
    return NULL;
}

/* Return the sum of two matrices. The result is in a newly creaed matrix. 
 *
 * If a pthread function fails, report error and exit. 
 * Return NULL if something else is wrong.
 *
 * Similar to addMatrix, but this function uses 2 threads.
 */
TMatrix *addMatrix_thread(TMatrix *m, TMatrix *n) {
    if (m == NULL || n == NULL || m->nrows != n->nrows || m->ncols != n->ncols)
        return NULL;

    TMatrix *t = newMatrix(m->nrows, m->ncols);
    if (t == NULL)
        return NULL;

    //TODO

    pthread_t threads[NUM_THREADS];
    thread_arg_t dataThread[NUM_THREADS];

    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        dataThread[i].id = i + 1;
        dataThread[i].m = m;
        dataThread[i].n = n;
        dataThread[i].t = t;

        if (pthread_create(&threads[i], NULL, thread_main, &dataThread[i]) != 0) {
            for (unsigned int j = 0; j < i; j++) {
                pthread_cancel(threads[j]);
            }
            return NULL;
        }
    }

    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) return NULL;
    }
    return t;
}