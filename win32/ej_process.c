/* -*- mode: c -*- */
/* $Id: ej_process.c 5678 2010-01-19 10:00:07Z cher $ */

/* Copyright (C) 2005-2009 Alexander Chernov <cher@ejudge.ru> */

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

unsigned char *
read_process_output(const unsigned char *cmd,
                    const unsigned char *workdir,
                    int max_ok_code,
                    int redirect_stderr)
{
  // FIXME: stub
  return 0;
}

/*
 * Local variables:
 *  compile-command: "make"
 *  c-font-lock-extra-types: ("\\sw+_t" "FILE" "va_list" "fd_set" "DIR")
 * End:
 */
