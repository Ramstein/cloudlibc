// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/locale.h>
#include <common/stdio.h>

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

wint_t ungetwc(wint_t wc, FILE *stream) {
  // Pushing WEOF is not permitted.
  if (wc == WEOF) {
    errno = EINVAL;
    return WEOF;
  }

  // Push character into ungetc buffer after multibyte encoding. Only
  // allow this to be performed if the stream has been opened for
  // reading. According to the standard, this function may set errno to
  // EILSEQ. Set errno to reasonable values for all other error cases.
  flockfile(stream);
  bool result = false;
  if ((stream->oflags & O_RDONLY) == 0) {
    errno = EBADF;
  } else {
    const struct lc_ctype *ctype = stream->ctype;
    char buf[MB_LEN_MAX];
    ssize_t len = ctype->c32tomb(buf, wc, ctype->data);
    if (len != -1) {
      if (stream->ungetclen + len > sizeof(stream->ungetc)) {
        errno = ENOSPC;
      } else {
        stream->ungetclen += len;
        memcpy(stream->ungetc + sizeof(stream->ungetc) - stream->ungetclen, buf,
               len);
        result = true;
      }
    }
  }
  funlockfile(stream);
  return result ? wc : WEOF;
}