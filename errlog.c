/* -*- c -*- */
/* $Id: errlog.c 5675 2010-01-19 09:52:11Z cher $ */

/* Copyright (C) 2005-2009 Alexander Chernov <cher@ejudge.ru> */

/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#include "errlog.h"

#include <reuse/logger.h>
#include <reuse/xalloc.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if defined __GNUC__ && defined __MINGW32__
#include <malloc.h>
#endif

void
vverr(char const *msg, va_list args)
{
  vwrite_log(0, LOG_ERR, msg, args);
}

void
err(char const *msg, ...)
{
  va_list args;

  va_start(args, msg);
  vwrite_log(0, LOG_ERR, msg, args);
  va_end(args);
}

/* we need this for proper localization */
void
do_err_r(char const *func, char const *txt, ...)
{
  va_list  args;
  char    *s = alloca(strlen(func) + strlen(txt) + 10);

  va_start(args, txt);
  sprintf(s, "%s: %s", func, txt);
  vverr(s, args);
  va_end(args);
}

void
info(char const *msg, ...)
{
  va_list args;

  va_start(args, msg);
  vwrite_log(0, LOG_INFO, msg, args);
  va_end(args);
}

