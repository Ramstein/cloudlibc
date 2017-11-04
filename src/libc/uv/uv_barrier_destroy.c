// Copyright (c) 2017 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <pthread.h>
#include <stdlib.h>
#include <uv.h>

void uv_barrier_destroy(uv_barrier_t *barrier) {
  if (pthread_barrier_destroy(barrier) != 0)
    abort();
}