/* -*- mode: c -*- */
/* $Id: read_team_unsigned_long_long.c 5687 2010-01-19 10:10:15Z cher $ */

/* Copyright (C) 2004-2006 Alexander Chernov <cher@ejudge.ru> */

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

#include "checker_internal.h"
#include <errno.h>

int
checker_read_out_unsigned_long_long(const char *name,
                                    int eof_error_flag,
                                    unsigned long long *p_val)
{
  unsigned long long x;
  char sb[128], *db = 0, *vb = 0, *ep = 0;
  size_t ds = 0;

  if (!name) name = "";
  vb = checker_read_buf_2(1, name, eof_error_flag, sb, sizeof(sb), &db, &ds);
  if (!vb) return -1;
  if (vb[0] == '-') fatal_PE("minus sign before uint64 value in output");
  errno = 0;
  x = strtoull(vb, &ep, 10);
  if (*ep) fatal_PE("cannot parse uint64 value for %s from output", name);
  if (errno) fatal_PE("uint64 value %s from output is out of range", name);
  *p_val = x;
  return 1;
}

int
checker_read_team_unsigned_long_long(const char *name,
                                     int eof_error_flag,
                                     unsigned long long *p_val)
{
  return checker_read_out_unsigned_long_long(name, eof_error_flag, p_val);
}

/*
 * Local variables:
 *  compile-command: "make"
 *  c-font-lock-extra-types: ("\\sw+_t" "FILE")
 * End:
 */
