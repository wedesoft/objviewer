SUFFIXES = .c .h .y .l

AM_YFLAGS = -d

lib_LTLIBRARIES = librender.la

pkginclude_HEADERS = hash.h image.h list.h material.h object.h parser.h program.h projection.h report_status.h \
										 shader.h surface.h texture.h vertex_array_object.h

BUILT_SOURCES = parser_bison.h

librender_la_SOURCES = hash.c image.c list.c material.c object.c parser.c parser_bison.y parser_flex.l program.c \
											 projection.c report_status.c shader.c surface.c texture.c vertex_array_object.c
librender_la_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
librender_la_LDFLAGS =
librender_la_LIBADD = $(MAGICK_LIBS) $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS)
