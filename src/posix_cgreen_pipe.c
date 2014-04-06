#include "cgreen/internal/cgreen_pipe.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#ifndef O_ASYNC
#  define O_ASYNC FASYNC
#  ifndef FASYNC
#    error "Your POSIX platform does not support ASYNC pipe reads. Please report a bug to cgreen-devel@lists.sf.net"
#  endif
#endif

#ifdef __cplusplus
namespace cgreen {
#endif


int cgreen_pipe_open(int pipes[2])
{
    return pipe(pipes);
}

void cgreen_pipe_close(int p)
{
    close(p);
}

ssize_t cgreen_pipe_read(int p, void *buf, size_t count)
{
    if (0 != fcntl(p, F_SETFL, O_ASYNC)) {
        fprintf(stderr, "could not set file status flag on read pipe\n");
        return -1;
    }

    return read(p,buf,count);
}

ssize_t cgreen_pipe_write(int p, const void *buf, size_t count)
{
    return write(p,buf,count);
}


#ifdef __cplusplus
} // namespace cgreen
#endif

/* vim: set ts=4 sw=4 et cindent: */
