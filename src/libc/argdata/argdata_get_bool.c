// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/argdata.h>

#include <argdata.h>
#include <errno.h>
#include <stdbool.h>

int argdata_get_bool(const argdata_t *ad, bool *value) {
  switch (ad->type) {
    case AD_BUFFER: {
      const uint8_t *buf = ad->buffer.buf;
      size_t len = ad->buffer.len;
      int error = parse_type(ADT_BOOL, &buf, &len);
      if (error != 0)
        return error;

      // Extract boolean value.
      if (ad->buffer.len != 1)
        return EINVAL;
      *value = ad->buffer.buf[1] != 0;
      return 0;
    }
    default:
      return EINVAL;
  }
}
