/* -*- mode: c -*- */
/* $Id: startstop.c 6161 2011-03-27 07:01:28Z cher $ */

/* Copyright (C) 2006-2011 Alexander Chernov <cher@ejudge.ru> */

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

#include "config.h"
#include "ej_types.h"
#include "version.h"

#include "startstop.h"
#include "pathutl.h"
#include "errlog.h"

#include "reuse_osdeps.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

static path_t self_exe;
static char **self_argv;
static sigset_t init_sigmask;

void
start_set_self_args(int argc, char *argv[])
{
  int n;

  if ((n = readlink("/proc/self/exe", self_exe, sizeof(self_exe))) <= 0) {
    fprintf(stderr, "%s: cannot access /proc/self/exe: %s\n",
            argv[0], os_ErrorMsg());
    snprintf(self_exe, sizeof(self_exe), "%s", argv[0]);
  } else {
    self_exe[n] = 0;
  }
  self_argv = argv;
  self_argv[0] = self_exe;
  sigprocmask(SIG_SETMASK, 0, &init_sigmask);
}

int
start_switch_user(const unsigned char *user, const unsigned char *group)
{
  struct passwd *pwinfo = 0;
  struct group *grinfo = 0;

  if (user && !*user) user = 0;
  if (group && !*group) group = 0;

  if (!user && !getuid()) {
    fprintf(stderr, 
            "Error: user is not specified\n"
            "Note: since you've invoked program as the root user, you must\n"
            "  specify an unprivileged user login and group to run as.\n"
            "  The program will not run with the root privileges!\n");
    return -1;
  }
  if (!group) group = user;
  if (user && !(pwinfo = getpwnam(user))) {
    fprintf(stderr, "Error: no such user: %s\n", user);
    return -1;
  }
  if (group && !(grinfo = getgrnam(group))) {
    fprintf(stderr, "Error: no such group: %s\n", group);
    return -1;
  }
  if (group && setgid(grinfo->gr_gid) < 0) {
    fprintf(stderr, "Error: cannot change gid: %s\n", os_ErrorMsg());
    return -1;
  }
  if (user && setuid(pwinfo->pw_uid) < 0) {
    fprintf(stderr, "Error: cannot change uid: %s\n", os_ErrorMsg());
    return -1;
  }
  return 0;
}

int
start_prepare(const unsigned char *user, const unsigned char *group,
              const unsigned char *workdir)
{
  if (start_switch_user(user, group) < 0) return -1;

  if (workdir && *workdir) {
    if (chdir(workdir) < 0) {
      fprintf(stderr, "Error: cannot change directory to %s\n", workdir);
      return -1;
    }
  }
  return 0;
}

void
start_restart(void)
{
  sigprocmask(SIG_SETMASK, &init_sigmask, 0);
  execv(self_exe, self_argv);
}

void
start_set_args(char *argv[])
{
  self_argv = argv;
  self_argv[0] = self_exe;
}

int
start_find_process(const unsigned char *name, int *p_uid)
{
  DIR *d = 0;
  struct dirent *dd;
  char *eptr;
  int pid, nlen, mypid, dlen;
  path_t fpath, xpath, dpath;
  long llen;
  int retval = -1;

  nlen = strlen(name);
  mypid = getpid();

  snprintf(dpath, sizeof(dpath), "%s (deleted)", name);
  dlen = strlen(dpath);

  if (!(d = opendir("/proc"))) goto cleanup;
  retval = 0;
  while ((dd = readdir(d))) {
    eptr = 0; errno = 0;
    pid = strtol(dd->d_name, &eptr, 10);
    if (errno || *eptr || eptr == dd->d_name || pid <= 0 || pid == mypid)
      continue;
    snprintf(fpath, sizeof(fpath), "/proc/%d/exe", pid);
    xpath[0] = 0;
    llen = readlink(fpath, xpath, sizeof(xpath));
    if (llen <= 0 || llen >= sizeof(xpath)) continue;
    xpath[llen] = 0;
    if (llen < nlen + 1) continue;
    if (xpath[llen - nlen - 1] == '/' && !strcmp(xpath + llen - nlen, name)) {
      retval = pid;
      // FIXME: get the actual uid
      if (p_uid) *p_uid = getuid();
      goto cleanup;
    }
    if (llen < dlen + 1) continue;
    if (xpath[llen - dlen - 1] == '/' && !strcmp(xpath + llen - dlen, dpath)) {
      retval = pid;
      // FIXME: get the actual uid
      if (p_uid) *p_uid = getuid();
      goto cleanup;
    }
  }
  closedir(d); d = 0;

 cleanup:
  if (d) closedir(d);
  return retval;
}

int
start_kill(int pid, int op)
{
  int signum = 0;
  switch (op) {
  case START_RESTART: signum = SIGHUP; break;
  case START_STOP: signum = SIGTERM; break;
  }
  return kill(pid, signum);
}

/*
 * Local variables:
 *  compile-command: "make -C .."
 *  c-font-lock-extra-types: ("\\sw+_t" "FILE" "va_list" "fd_set" "DIR")
 * End:
 */
