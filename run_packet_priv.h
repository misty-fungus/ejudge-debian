/* -*- c -*- */
/* $Id: run_packet_priv.h 5675 2010-01-19 09:52:11Z cher $ */
#ifndef __RUN_PACKET_PRIV_H__
#define __RUN_PACKET_PRIV_H__

/* Copyright (C) 2005-2008 Alexander Chernov <cher@ejudge.ru> */

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

#include <reuse/integral.h>

/* various private data structures and constants for run packets */

/* bits for flags */
#define FLAGS_PUT_SCORING_SYSTEM(s) ((s & 0xf))
#define FLAGS_GET_SCORING_SYSTEM(f) ((f & 0xf))

enum
{
  FLAGS_ACCEPTING_MODE       = 0x010,
  FLAGS_ACCEPT_PARTIAL       = 0x020,
  FLAGS_DISABLE_SOUND        = 0x040,
  FLAGS_FULL_ARCHIVE         = 0x080,
  FLAGS_MEMORY_LIMIT         = 0x100,
  FLAGS_SECURE_RUN           = 0x200,
  FLAGS_SECURITY_VIOLATION   = 0x400,
  FLAGS_NOTIFY               = 0x800,

  FLAGS_ALL_MASK             = 0xfff, /* scoring system incl. */
};

/* serve->run binary packet structure */
/* little-endian byte ordering is assumed */
struct run_request_bin_packet
{
  ruint32_t packet_len;
  rint32_t  version;
  rint32_t  contest_id;
  rint32_t  run_id;
  rint32_t  problem_id;
  rint32_t  user_id;
  rint32_t  time_limit_adj;
  rint32_t  time_limit_adj_millis;
  ruint32_t flags;              /* incl. scoring system */
  rint32_t  ts1;
  rint32_t  ts1_us;
  rint32_t  ts2;
  rint32_t  ts2_us;
  rint32_t  ts3;
  rint32_t  ts3_us;
  rint32_t  ts4;
  rint32_t  ts4_us;
  ruint16_t judge_id;
  ruint16_t user_spelling_len;
  ruint16_t prob_spelling_len;
  ruint8_t  exe_sfx_len;
  ruint8_t  arch_len;
  ruint8_t  variant;
  unsigned char pad[55];        /* padding to 128 bytes */
  /* exe_sfx */
  /* arch */
  /* user spelling */
  /* prob spelling */
  /* padding to 16-byte boundary */
};

/* run->serve binary packet structure */
/* little-endian byte ordering is assumed */
struct run_reply_bin_packet
{
  ruint32_t packet_len;
  rint32_t  version;
  rint32_t  judge_id;
  rint32_t  contest_id;
  rint32_t  run_id;
  rint32_t  status;
  rint32_t  failed_test;
  rint32_t  score;
  ruint32_t flags;
  rint32_t  ts1;
  rint32_t  ts1_us;
  rint32_t  ts2;
  rint32_t  ts2_us;
  rint32_t  ts3;
  rint32_t  ts3_us;
  rint32_t  ts4;
  rint32_t  ts4_us;
  rint32_t  ts5;
  rint32_t  ts5_us;
  rint32_t  ts6;
  rint32_t  ts6_us;
  rint32_t  ts7;
  rint32_t  ts7_us;
  unsigned char pad[36];        /* padding to 128 bytes */
};

#endif /* __RUN_PACKET_PRIV_H__ */
