/* -*- c -*- */
/* $Id: digest_3.c 5675 2010-01-19 09:52:11Z cher $ */

/* Copyright (C) 2005 Alexander Chernov <cher@ispras.ru> */

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

#include "digest_io.h"

#include <reuse/logger.h>

#include <stdio.h>

int
digest_to_ascii(int kind, const void *raw, unsigned char *asc)
{
  int dlen, i;
  const unsigned char *p = (const unsigned char*) raw;

  switch (kind) {
  case DIGEST_SHA1: dlen = 20; break;
  default:
    SWERR(("unhandled digest type %d", kind));
  }

  for (i = 0; i < dlen; i++, p++, asc += 2)
    sprintf(asc, "%02x", *p);

  return dlen * 2;
}

/**
 * Local variables:
 *  compile-command: "make"
 *  c-font-lock-extra-types: ("\\sw+_t" "FILE")
 * End:
 */
