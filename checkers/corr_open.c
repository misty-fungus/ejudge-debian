/* -*- mode: c -*- */
/* $Id: corr_open.c 5912 2010-06-26 08:52:45Z cher $ */

/* Copyright (C) 2010 Alexander Chernov <cher@ejudge.ru> */

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

void
checker_corr_open(const char *path)
{
  if (f_corr && f_corr == f_arr[2]) {
    fclose(f_corr); f_corr = 0; f_arr[2] = 0;
  }
  if (f_corr) fclose(f_corr);
  f_corr = 0;
  if (f_arr[2]) fclose(f_arr[2]);
  f_arr[2] = 0;

  if (!(f_corr = fopen(path, "r"))) {
    fatal_CF("%s: cannot open %s for reading", f_arr_names[2], path);
  }
  f_arr[2] = f_corr;
}
