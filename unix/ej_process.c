/* -*- mode: c -*- */
/* $Id: ej_process.c 6599 2011-12-28 15:49:44Z cher $ */

/* Copyright (C) 2005-2011 Alexander Chernov <cher@ejudge.ru> */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "ej_process.h"
#include "compat.h"
#include "list_ops.h"

#include "reuse_xalloc.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/resource.h>

static int
error(const char *format, ...)
  __attribute__((format(printf, 1, 2)));
static int
error(const char *format, ...)
{
  va_list args;
  char buf[1024];

  va_start(args, format);
  vsnprintf(buf, sizeof(buf), format, args);
  va_end(args);

  fprintf(stderr, "error: %s\n", buf);
  return -1;
}

static int
fferror(FILE *ferr, const char *format, ...)
  __attribute__((format(printf, 2, 3)));
static int
fferror(FILE *ferr, const char *format, ...)
{
  va_list args;
  char buf[1024];

  va_start(args, format);
  vsnprintf(buf, sizeof(buf), format, args);
  va_end(args);

  fprintf(ferr, "error: %s\n", buf);
  return -1;
}

unsigned char *
read_process_output(const unsigned char *cmd,
                    const unsigned char *workdir,
                    int max_ok_code,
                    int redirect_stderr)
{
  FILE *fin = 0;
  FILE *fout = 0;
  char *out_txt = 0;
  size_t out_len = 0;
  int pfd[2] = { -1, -1 };
  int c, pid, status;
  sigset_t mask;

  if (!(fout = open_memstream(&out_txt, &out_len))) goto failed;
  if (pipe(pfd) < 0) goto failed;
  if ((pid = fork()) < 0) goto failed;
  if (!pid) {
    // child
    close(pfd[0]);
    dup2(pfd[1], 1);
    if (redirect_stderr) dup2(pfd[1], 2);
    close(pfd[1]);
    if (workdir) chdir(workdir);
    sigemptyset(&mask);
    sigprocmask(SIG_SETMASK, &mask, 0);
    execl("/bin/sh", "/bin/sh", "-c", cmd, NULL);
    _exit(1);
  }
  close(pfd[1]); pfd[1] = -1;
  if (!(fin = fdopen(pfd[0], "r"))) goto failed;
  pfd[0] = -1;
  while ((c = getc(fin)) != EOF) putc(c, fout);
  waitpid(pid, &status, 0);
  fclose(fin);
  close_memstream(fout); fout = 0;
  c = 1;
  if (WIFEXITED(status) && (WEXITSTATUS(status) & 0xff) <= max_ok_code) c = 0;

  if (c) {
    xfree(out_txt);
    return xstrdup("");
  }

  out_len = strlen(out_txt);
  while (out_len > 0 && isspace(out_txt[out_len - 1])) out_txt[--out_len] = 0;
  return out_txt;

 failed:
  if (pfd[0] >= 0) close(pfd[0]);
  if (pfd[1] >= 0) close(pfd[1]);
  if (fin) pclose(fin);
  if (fout) close_memstream(fout);
  xfree(out_txt);
  return 0;
}

int
ejudge_invoke_process(
        char **args,
        char **envs,
        const unsigned char *workdir,
        const unsigned char *stdin_text,
        int merge_out_flag,
        unsigned char **stdout_text,
        unsigned char **stderr_text)
{
  char *err_t = 0, *out_t = 0;
  size_t err_z = 0, out_z = 0;
  FILE *err_f = 0, *out_f = 0;
  int pid, out_p[2] = {-1, -1}, err_p[2] = {-1, -1}, in_p[2] = {-1, -1};
  int maxfd, n, status, retcode = 0;
  const unsigned char *stdin_ptr;
  size_t stdin_len;
  unsigned char buf[4096];
  fd_set wset, rset;
  int i;
  sigset_t mask;

  if (!stdin_text) stdin_text = "";
  stdin_ptr = stdin_text;
  stdin_len = strlen(stdin_text);

  if (pipe(in_p) < 0) {
    err_f = open_memstream(&err_t, &err_z);
    fferror(err_f, "pipe failed: %s", strerror(errno));
    goto fail;
  }
  if (pipe(out_p) < 0) {
    err_f = open_memstream(&err_t, &err_z);
    fferror(err_f, "pipe failed: %s", strerror(errno));
    goto fail;
  }
  if (!merge_out_flag) {
    if (pipe(err_p) < 0) {
      err_f = open_memstream(&err_t, &err_z);
      fferror(err_f, "pipe failed: %s", strerror(errno));
      goto fail;
    }
  }

  if ((pid = fork()) < 0) {
    err_f = open_memstream(&err_t, &err_z);
    fferror(err_f, "fork failed: %s", strerror(errno));
    goto fail;
  } else if (!pid) {
    fflush(stderr);
    dup2(in_p[0], 0); close(in_p[0]); close(in_p[1]);
    dup2(out_p[1], 1); close(out_p[0]); close(out_p[1]);
    if (!merge_out_flag) {
      dup2(err_p[1], 2); close(err_p[0]); close(err_p[1]);
    } else {
      dup2(1, 2);
    }

    if (workdir) {
      if (chdir(workdir) < 0) {
        error("cannot change directory to %s: %s", workdir, strerror(errno));
        fflush(stderr);
        _exit(1);
      }
    }
    if (envs) {
      for (i = 0; envs[i]; ++i) {
        putenv(envs[i]);
      }
    }
    sigemptyset(&mask);
    sigprocmask(SIG_SETMASK, &mask, 0);
    execve(args[0], args, environ);
    error("exec failed: %s", strerror(errno));
    fflush(stderr);
    _exit(1);
  }

  /* parent */
  close(in_p[0]); in_p[0] = -1;
  close(out_p[1]); out_p[1] = -1;
  if (err_p[1] >= 0) {
    close(err_p[1]);
  }
  err_p[1] = -1;
  err_f = open_memstream(&err_t, &err_z);
  out_f = open_memstream(&out_t, &out_z);

  while (1) {
    maxfd = -1;
    FD_ZERO(&wset);
    FD_ZERO(&rset);
    if (in_p[1] >= 0) {
      FD_SET(in_p[1], &wset);
      if (in_p[1] > maxfd) maxfd = in_p[1];
    }
    if (out_p[0] >= 0) {
      FD_SET(out_p[0], &rset);
      if (out_p[0] > maxfd) maxfd = out_p[0];
    }
    if (err_p[0] >= 0) {
      FD_SET(err_p[0], &rset);
      if (err_p[0] > maxfd) maxfd = err_p[0];
    }
    if (maxfd < 0) {
      break;
    }

    n = select(maxfd + 1, &rset, &wset, NULL, NULL);
    if (n < 0) {
      fprintf(err_f, "Error: select failed: %s\n", strerror(errno));
      if (in_p[1] >= 0) close(in_p[1]);
      in_p[1] = -1;
      if (out_p[0] >= 0) close(out_p[0]);
      out_p[0] = -1;
      if (err_p[0] >= 0) close(err_p[0]);
      err_p[0] = -1;
      break;
    }

    if (in_p[1] >= 0 && FD_ISSET(in_p[1], &wset)) {
      if (stdin_len > 0) {
        n = write(in_p[1], stdin_ptr, stdin_len);
        if (n < 0) {
          fprintf(err_f, "Error: write to process failed: %s\n",
                  strerror(errno));
          close(in_p[1]); in_p[1] = -1;
        } else if (!n) {
          fprintf(err_f, "Error: write to process returned 0\n");
          close(in_p[1]); in_p[1] = -1;
        } else {
          stdin_ptr += n;
          stdin_len -= n;
        }
      } else {
        close(in_p[1]); in_p[1] = -1;
      }
    }
    if (out_p[0] >= 0 && FD_ISSET(out_p[0], &rset)) {
      n = read(out_p[0], buf, sizeof(buf));
      if (n < 0) {
        fprintf(err_f, "Error: read from process failed: %s\n",
                strerror(errno));
        close(out_p[0]); out_p[0] = -1;
      } else if (!n) {
        close(out_p[0]); out_p[0] = -1;
      } else {
        fwrite(buf, 1, n, out_f);
      }
    }
    if (err_p[0] >= 0 && FD_ISSET(err_p[0], &rset)) {
      n = read(err_p[0], buf, sizeof(buf));
      if (n < 0) {
        fprintf(err_f, "Error: read from process failed %s\n",
                strerror(errno));
        close(err_p[0]); err_p[0] = -1;
      } else if (!n) {
        close(err_p[0]); err_p[0] = -1;
      } else {
        fwrite(buf, 1, n, err_f);
      }
    }
  }

  n = waitpid(pid, &status, 0);
  if (n < 0) {
    fprintf(err_f, "Error: waiting failed: %s\n", strerror(errno));
    goto fail;
  }

  fclose(out_f); out_f = 0;
  fclose(err_f); err_f = 0;
  if (stdout_text) {
    *stdout_text = out_t; out_t = 0;
  } else {
    free(out_t); out_t = 0;
  }
  if (stderr_text) {
    *stderr_text = err_t; err_t = 0;
  } else {
    free(err_t); err_t = 0;
  }

  if (WIFEXITED(status)) {
    retcode = WEXITSTATUS(status);
  } else if (WIFSIGNALED(status)) {
    retcode = 256 + WTERMSIG(status);
  }

  return retcode;

fail:
  if (in_p[0] >= 0) close(in_p[0]);
  if (in_p[1] >= 0) close(in_p[1]);
  if (out_p[0] >= 0) close(out_p[0]);
  if (out_p[1] >= 0) close(out_p[1]);
  if (err_p[0] >= 0) close(err_p[0]);
  if (err_p[1] >= 0) close(err_p[1]);
  if (err_f) fclose(err_f);
  if (out_f) fclose(out_f);
  if (stderr_text) {
    *stderr_text = err_t; err_t = 0;
  } else {
    free(err_t);
  }
  free(out_t);
  if (stdout_text) *stdout_text = 0;
  return -1;
}

struct background_process *
background_process_alloc(void)
{
  struct background_process *prc;

  XCALLOC(prc, 1);
  prc->stdin_f = -1;
  prc->stdout_f = -1;
  prc->stderr_f = -1;
  return prc;
}

struct background_process *
background_process_free(struct background_process *prc)
{
  if (!prc) return NULL;

  xfree(prc->name);
  xfree(prc->stdin_b);
  if (prc->stdin_f >= 0) close(prc->stdin_f);
  if (prc->stdout_f >= 0) close(prc->stdout_f);
  if (prc->stderr_f >= 0) close(prc->stderr_f);
  xfree(prc->out.buf);
  xfree(prc->err.buf);

  memset(prc, 0, sizeof(*prc));
  prc->stdin_f = -1;
  prc->stdout_f = -1;
  prc->stderr_f = -1;

  xfree(prc);
  return NULL;
}

struct background_process *
ejudge_start_process(
        FILE *log_f,
        const unsigned char *name,
        char **args,
        char **envs,
        const unsigned char *workdir,
        const unsigned char *stdin_text,
        int merge_out_flag,
        int time_limit_ms,
        void (*continuation)(struct background_process*),
        void *user)
{
  int in_pipe[2] = { -1, -1 };
  int out_pipe[2] = { -1, -1 };
  int err_pipe[2] = { -1, -1 };
  int pid = 0;
  struct background_process *prc = NULL;
  struct timeval tv;

  if (stdin_text && pipe(in_pipe) < 0) {
    fprintf(log_f, "%s: pipe() failed: %s\n", __FUNCTION__, strerror(errno));
    goto fail;
  }
  if (pipe(out_pipe) < 0) {
    fprintf(log_f, "%s: pipe() failed: %s\n", __FUNCTION__, strerror(errno));
    goto fail;
  }
  if (merge_out_flag <= 0 && pipe(err_pipe) < 0) {
    fprintf(log_f, "%s: pipe() failed: %s\n", __FUNCTION__, strerror(errno));
    goto fail;
  }

  gettimeofday(&tv, NULL);

  if ((pid = fork()) < 0) {
    fprintf(log_f, "%s: fork() failed: %s\n", __FUNCTION__, strerror(errno));
    goto fail;
  } else if (!pid) {
    // son
    fflush(stderr);
    setpgid(0, 0);
    if (err_pipe[1] >= 0) {
      if (dup2(err_pipe[1], 2) < 0) {
        fprintf(stderr, "%s: dup2() failed in child: %s\n", __FUNCTION__,
                strerror(errno));
        fflush(stderr);
        _exit(1);
      }
    } else {
      if (dup2(out_pipe[1], 2) < 0) {
        fprintf(stderr, "%s: dup2() failed in child %s\n", __FUNCTION__,
                strerror(errno));
        fflush(stderr);
        _exit(1);
      }
    }
    // from this point the stderr is redirected to the pipe
    if (dup2(out_pipe[1], 1) < 0) {
      fprintf(stderr, "%s: dup2() failed in child %s\n", __FUNCTION__,
              strerror(errno));
      fflush(stderr);
      _exit(1);
    }
    if (in_pipe[0] < 0) {
      in_pipe[0] = open("/dev/null", O_RDONLY, 0);
      if (in_pipe[0] < 0) {
        fprintf(stderr, "%s: failed to open /dev/null: %s\n", __FUNCTION__,
                strerror(errno));
        _exit(1);
      }
    }
    if (dup2(in_pipe[0], 0) < 0) {
      fprintf(stderr, "%s: dup2() failed in child %s\n", __FUNCTION__,
              strerror(errno));
      fflush(stderr);
      _exit(1);
    }
    if (in_pipe[0] >= 0) close(in_pipe[0]);
    if (in_pipe[1] >= 0) close(in_pipe[1]);
    if (out_pipe[0] >= 0) close(out_pipe[0]);
    if (out_pipe[1] >= 0) close(out_pipe[1]);
    if (err_pipe[0] >= 0) close(err_pipe[0]);
    if (err_pipe[1] >= 0) close(err_pipe[1]);
    if (workdir && chdir(workdir) < 0) {
      fprintf(stderr, "%s: cannot chdir to %s: %s", __FUNCTION__,
              workdir, strerror(errno));
      fflush(stderr);
      _exit(1);
    }
    if (envs) {
      for (int i = 0; envs[i]; ++i) {
        putenv(envs[i]);
      }
    }
    sigset_t mask;
    sigemptyset(&mask);
    sigprocmask(SIG_SETMASK, &mask, 0);
    execve(args[0], args, environ);
    fprintf(stderr, "%s: exec failed: %s", __FUNCTION__,
            strerror(errno));
    fflush(stderr);
    _exit(1);
  }

  setpgid(pid, pid);

  if (in_pipe[0] >= 0) close(in_pipe[0]);
  in_pipe[0] = -1;
  if (out_pipe[1] >= 0) close(out_pipe[1]);
  out_pipe[1] = -1;
  if (err_pipe[1] >= 0) close(err_pipe[1]);
  err_pipe[1] = -1;

  prc = background_process_alloc();
  prc->name = xstrdup(name);
  if (stdin_text) {
    prc->stdin_b = xstrdup(stdin_text);
    prc->stdin_z = strlen(stdin_text);
  }
  prc->time_limit_ms = time_limit_ms;
  prc->kill_grace_ms = 1000;
  prc->start_time_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
  prc->merge_out_flag = merge_out_flag;
  if (in_pipe[1] >= 0) {
    prc->stdin_f = in_pipe[1]; in_pipe[1] = -1;
    fcntl(prc->stdin_f, F_SETFL, fcntl(prc->stdin_f, F_GETFL) | O_NONBLOCK);
  }
  if (out_pipe[0] >= 0) {
    prc->stdout_f = out_pipe[0]; out_pipe[0] = -1;
    fcntl(prc->stdout_f, F_SETFL, fcntl(prc->stdout_f, F_GETFL) | O_NONBLOCK);
  }
  if (err_pipe[0] >= 0) {
    prc->stderr_f = err_pipe[0]; err_pipe[0] = -1;
    fcntl(prc->stderr_f, F_SETFL, fcntl(prc->stderr_f, F_GETFL) | O_NONBLOCK);
  }
  prc->state = BACKGROUND_PROCESS_RUNNING;
  prc->pid = pid;
  prc->user = user;
  prc->continuation = continuation;

  return prc;

fail:
  prc = background_process_free(prc);
  if (in_pipe[0] >= 0) close(in_pipe[0]);
  if (in_pipe[1] >= 0) close(in_pipe[1]);
  if (out_pipe[0] >= 0) close(out_pipe[0]);
  if (out_pipe[1] >= 0) close(out_pipe[1]);
  if (err_pipe[0] >= 0) close(err_pipe[0]);
  if (err_pipe[1] >= 0) close(err_pipe[1]);
  return NULL;
}

static int
trywait(struct background_process *prc, long long current_time_ms)
{
  struct rusage usage;
  int status = 0;

  memset(&usage, 0, sizeof(usage));
  if (wait4(prc->pid, &status, WNOHANG, &usage) <= 0) return 0;
  prc->state = BACKGROUND_PROCESS_FINISHED;
  if (WIFEXITED(status)) {
    prc->is_exited = 1;
    prc->exit_code = WEXITSTATUS(status);
  } else if (WIFSIGNALED(status)) {
    prc->is_signaled = 1;
    prc->term_signal = WTERMSIG(status);
  }
  prc->utime_ms = usage.ru_utime.tv_sec * 1000LL + usage.ru_utime.tv_usec / 1000LL;
  prc->stime_ms = usage.ru_stime.tv_sec * 1000LL + usage.ru_stime.tv_usec / 1000LL;
  prc->maxrss = usage.ru_maxrss;
  prc->stop_time_ms = current_time_ms;
  return 1;
}

static void
buffer_append_mem(struct background_process_buffer *p, const unsigned char *buf, int size)
{
  int exp_size = p->size + size + 1;
  int new_size = p->allocated;
  if (exp_size > new_size) {
    if (!new_size) new_size = 64;
    while (new_size < exp_size) new_size *= 2;
    p->buf = xrealloc(p->buf, new_size * sizeof(p->buf[0]));
    p->allocated = new_size;
  }
  memcpy(p->buf + p->size, buf, size);
  p->size += size;
  p->buf[p->size] = 0;
}

static void
buffer_append_str(struct background_process_buffer *p, const unsigned char *str)
{
  if (!str || !*str) return;
  buffer_append_mem(p, str, strlen(str));
}

void
ejudge_check_process_finished(struct background_process *prc)
{
  struct timeval tv;
  long long current_time_ms;
  const unsigned char *msg = NULL;

  if (!prc || prc->state != BACKGROUND_PROCESS_RUNNING) return;

  gettimeofday(&tv, NULL);
  current_time_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
  if (prc->kill_time_ms > 0) {
    // do nothing
  } else if (prc->term_time_ms > 0) {
    if (current_time_ms >= prc->term_time_ms + prc->kill_grace_ms) {
      kill(-prc->pid, SIGKILL);
      prc->kill_time_ms = current_time_ms;
      msg = "\nKill signal sent\n";
    }
  } else if (prc->time_limit_ms > 0 && current_time_ms >= prc->start_time_ms + prc->time_limit_ms) {
    kill(-prc->pid, SIGTERM);
    prc->term_time_ms = current_time_ms;
    msg = "\nTerm signal sent\n";
  }
  if (msg != NULL) {
    if (prc->merge_out_flag <= 0) {
      buffer_append_str(&prc->err, msg);
    } else {
      buffer_append_str(&prc->out, msg);
    }
  }

  // do not check for finishing until all fds are closed
  if (prc->stdin_f >= 0 || prc->stdout_f >= 0 || prc->stderr_f >= 0) return;
  trywait(prc, current_time_ms);
}

void
background_process_cleanup(struct background_process_head *list)
{
  if (!list) return;
  struct background_process *prc, *next;
  for (prc = list->first; prc; prc = next) {
    next = prc->next;
    if (prc->state == BACKGROUND_PROCESS_GARBAGE) {
      UNLINK_FROM_LIST(prc, list->first, list->last, prev, next);
      background_process_free(prc);
    }
  }
}

int
background_process_set_fds(struct background_process_head *list, int max_fd, void *vprset, void *vpwset)
{
  fd_set *prset = (fd_set*) vprset;
  fd_set *pwset = (fd_set*) vpwset;

  if (!list) return max_fd;
  struct background_process *prc;
  for (prc = list->first; prc; prc = prc->next) {
    if (prc->state != BACKGROUND_PROCESS_RUNNING) continue;
    if (prc->stdin_f >= 0) {
      FD_SET(prc->stdin_f, pwset);
      if (prc->stdin_f > max_fd) max_fd = prc->stdin_f;
    }
    if (prc->stdout_f >= 0) {
      FD_SET(prc->stdout_f, prset);
      if (prc->stdout_f > max_fd) max_fd = prc->stdout_f;
    }
    if (prc->stderr_f >= 0) {
      FD_SET(prc->stderr_f, prset);
      if (prc->stderr_f > max_fd) max_fd = prc->stderr_f;
    }
  }

  return max_fd;
}

void
background_process_readwrite(struct background_process_head *list, void *vprset, void *vpwset)
{
  fd_set *prset = (fd_set*) vprset;
  fd_set *pwset = (fd_set*) vpwset;
  unsigned char buf[4096];

  if (!list) return;
  struct background_process *prc;
  for (prc = list->first; prc; prc = prc->next) {
    if (prc->state != BACKGROUND_PROCESS_RUNNING) continue;
    if (prc->stdin_f >= 0 && FD_ISSET(prc->stdin_f, pwset)) {
      if (!prc->stdin_b || prc->stdin_z <= 0 || prc->stdin_u >= prc->stdin_z) {
        close(prc->stdin_f); prc->stdin_f = -1;
      } else {
        int wsz = prc->stdin_z - prc->stdin_u;
        while (1) {
          int w = write(prc->stdin_f, prc->stdin_b + prc->stdin_u, wsz);
          if (w < 0) {
            if (errno != EAGAIN) {
              fprintf(stderr, "%s: write to pipe failed: %s\n", __FUNCTION__, strerror(errno));
              close(prc->stdin_f); prc->stdin_f = -1;
              break;
            } else if (wsz == 1) {
              break;
            } else {
              wsz /= 2;
            }
          } else if (w == 0) {
            fprintf(stderr, "%s: write to pipe returned 0!\n", __FUNCTION__);
            close(prc->stdin_f); prc->stdin_f = -1;
            break;
          } else {
            prc->stdin_u += w;
            wsz = prc->stdin_z - prc->stdin_u;
            if (w <= 0) {
              close(prc->stdin_f); prc->stdin_f = -1;
              break;
            }
          }
        }
      }
      //FD_CLR(prc->stdin_f, pwset);
    }
    if (prc->stdout_f >= 0 && FD_ISSET(prc->stdout_f, prset)) {
      while (1) {
        int r = read(prc->stdout_f, buf, sizeof(buf));
        if (r < 0) {
          if (errno != EAGAIN) {
            fprintf(stderr, "%s: read from pipe failed: %s\n", __FUNCTION__, strerror(errno));
            close(prc->stdout_f); prc->stdout_f = -1;
          }
          break;
        } else if (r == 0) {
          close(prc->stdout_f); prc->stdout_f = -1;
          break;
        } else {
          buffer_append_mem(&prc->out, buf, r);
        }
      }
      //FD_CLR(prc->stdout_f, prset);
    }
    if (prc->stderr_f >= 0 && FD_ISSET(prc->stderr_f, prset)) {
      while (1) {
        int r = read(prc->stderr_f, buf, sizeof(buf));
        if (r < 0) {
          if (errno != EAGAIN) {
            fprintf(stderr, "%s: read from pipe failed: %s\n", __FUNCTION__, strerror(errno));
            close(prc->stderr_f); prc->stderr_f = -1;
          }
          break;
        } else if (r == 0) {
          close(prc->stderr_f); prc->stderr_f = -1;
          break;
        } else {
          buffer_append_mem(&prc->err, buf, r);
        }
      }
      //FD_CLR(prc->stderr_f, prset);
    }
  }
}

void
background_process_check_finished(struct background_process_head *list)
{
  if (!list) return;
  struct background_process *prc;
  for (prc = list->first; prc; prc = prc->next) {
    ejudge_check_process_finished(prc);
  }
}

void
background_process_register(struct background_process_head *list, struct background_process *prc)
{
  if (!list || !prc) return;
  LINK_FIRST(prc, list->first, list->last, prev, next);
}

struct background_process *
background_process_find(struct background_process_head *list, const unsigned char *name)
{
  if (!list || !name) return NULL;
  struct background_process *prc;
  for (prc = list->first; prc; prc = prc->next) {
    if (!strcmp(prc->name, name))
      return prc;
  }
  return NULL;
}

int
background_process_handle_termination(
        struct background_process_head *list,
        int pid,
        int status,
        const void *vusage)
{
  const struct rusage *pusage = (typeof(pusage)) vusage;
  if (!list) return 0;
  struct background_process *prc;
  for (prc = list->first; prc; prc = prc->next) {
    if (prc->state == BACKGROUND_PROCESS_RUNNING && prc->pid == pid) {
      struct timeval tv;
      gettimeofday(&tv, NULL);
      long long current_time_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
      prc->state = BACKGROUND_PROCESS_FINISHED;
      if (WIFEXITED(status)) {
        prc->is_exited = 1;
        prc->exit_code = WEXITSTATUS(status);
      } else if (WIFSIGNALED(status)) {
        prc->is_signaled = 1;
        prc->term_signal = WTERMSIG(status);
      }
      prc->utime_ms = pusage->ru_utime.tv_sec * 1000LL + pusage->ru_utime.tv_usec / 1000LL;
      prc->stime_ms = pusage->ru_stime.tv_sec * 1000LL + pusage->ru_stime.tv_usec / 1000LL;
      prc->maxrss = pusage->ru_maxrss;
      prc->stop_time_ms = current_time_ms;
      return 1;
    }
  }
  return 0;
}

void
background_process_call_continuations(struct background_process_head *list)
{
  if (!list) return;
  struct background_process *prc;
  for (prc = list->first; prc; prc = prc->next) {
    if (prc->state == BACKGROUND_PROCESS_FINISHED && prc->continuation) {
      prc->continuation(prc);
    }
  }
}

/*
 * Local variables:
 *  compile-command: "make -C .."
 *  c-font-lock-extra-types: ("\\sw+_t" "FILE" "va_list" "fd_set" "DIR")
 * End:
 */
