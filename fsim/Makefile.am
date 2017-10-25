lib_LTLIBRARIES = librender.la

pkginclude_HEADERS = image.h list.h normal.h object.h program.h projection.h report_status.h rgb.h \
									shader.h surface.h texture_coordinate.h texture.h \
									vertex_array_object.h vertex.h

librender_la_SOURCES = image.c list.c normal.c object.c program.c projection.c report_status.c rgb.c shader.c \
											 surface.c texture.c texture_coordinate.c vertex_array_object.c vertex.c
librender_la_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
librender_la_LDFLAGS =
librender_la_LIBADD = $(MAGICK_LIBS) $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS)
