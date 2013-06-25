/* guppi_threads.h
 *
 * Definitions, routines common to 
 * all thread functions.
 */
#ifndef _GUPPI_THREADS_H
#define _GUPPI_THREADS_H

#include "fitshead.h"
#include "hashpipe_status.h"
#include "guppi_thread_args.h"

/* Functions to query, set, and clear the "run_threads" flag. */
int run_threads();
void set_run_threads();
void clear_run_threads();

/* Safe lock/unlock functions for status shared mem. */
#define hashpipe_status_lock_safe(s) \
    pthread_cleanup_push((void *)hashpipe_status_unlock, s); \
    hashpipe_status_lock(s);

#define hashpipe_status_lock_busywait_safe(s) \
    pthread_cleanup_push((void *)hashpipe_status_unlock, s); \
    hashpipe_status_lock_busywait(s);

#define hashpipe_status_unlock_safe(s) \
    hashpipe_status_unlock(s); \
    pthread_cleanup_pop(0);

#ifdef STATUS_KEY
/* Exit handler that updates status buffer */
static inline void set_exit_status(struct hashpipe_status *s) {
    hashpipe_status_lock(s);
    hputs(s->buf, STATUS_KEY, "exiting");
    hashpipe_status_unlock(s);
}
#endif // STATUS_KEY

#endif // _GUPPI_THREADS_H