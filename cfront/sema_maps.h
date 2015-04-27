/* -*- mode:c -*- */
#ifndef __SEMA_MAPS_H__
#define __SEMA_MAPS_H__

/* $Id: sema_maps.h 7720 2014-01-03 10:41:03Z cher $ */

/* Copyright (C) 2003-2014 Alexander Chernov <cher@ejudge.ru> */

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

int sema_binop_to_c_operation(int op);
int sema_unop_to_c_operation(int op);
int sema_postop_to_c_operation(int op);

#endif /* __SEMA_MAPS_H__ */
