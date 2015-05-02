/* -*- mode:c -*- */
/* $Id: reuse_xfree.c 8530 2014-08-22 12:09:30Z cher $ */

/* Copyright (C) 2002-2014 Alexander Chernov <cher@ejudge.ru> */

/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#include "ejudge/xalloc.h"

/**
 * NAME:    xfree
 * PURPOSE: wrapper over free function
 * NOTE:    accepts NULL pointer as argument
 */
void
xfree(void *ptr)
{
  if (ptr == NULL) return;
  free(ptr);
}

/*
 * Local variables:
 *  compile-command: "make"
 * End:
 */
