/* -*- mode:c -*- */
/* $Id: reuse_sleep.c 8530 2014-08-22 12:09:30Z cher $ */

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

#include "ejudge/osdeps.h"

#include <unistd.h>

/**
 * NAME:    os_Sleep
 * PURPOSE: suspend execution of the program for a given time interval
 * ARGS:    millis - the interval in milliseconds
 */
  void
os_Sleep(int millis)
{
  usleep(millis * 1000);
}

/*
 * Local variables:
 *  compile-command: "make -C .."
 * End:
 */
