# -*- Makefile -*-

# Copyright (C) 2015 Alexander Chernov <cher@ejudge.ru> */

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

PLUGINDIR = $(libexecdir)/ejudge/plugins

CC = gcc
LD = gcc

CFLAGS = -I../../include $(MONGO_CFLAGS) $(CDEBUGFLAGS) $(CCOMPFLAGS) $(CEXTRAFLAGS) $(WPTRSIGN)
LDFLAGS = $(MYSQL_LIB_OPT) $(EXPAT_LIB_OPT) $(CDEBUGFLAGS) $(LDCOMPFLAGS) $(LDEXTRAFLAGS)
LDLIBS = $(EXTRALIBS) $(MONGO_LIBS) -lexpat -lm

CFILES = common_mongo.c

PLUGINS = common_mongo.so

all : $(PLUGINS)

install : $(PLUGINS)
	install -d "${DESTDIR}${PLUGINDIR}"
	install -m 0755 $(PLUGINS) "${DESTDIR}${PLUGINDIR}"

clean :
	-rm -f *.so *.o deps.make

distclean : clean
	-rm -f Makefile

deps.make : $(CFILES) $(HFILES)
	../../cdeps -v COMMON_MONGO_OFILES -I ../../include -g -c '$$(CC) $$(CFLAGS) -DPIC -fPIC' $(CFILES) > deps.make

include deps.make

common_mongo.so : $(COMMON_MONGO_OFILES)
	$(LD) -shared $(LDFLAGS) $^ -o $@ $(LDLIBS)

