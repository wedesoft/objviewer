ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = mini tetraeder

lib_LTLIBRARIES = librender.la

mini_SOURCES = mini.c
mini_CFLAGS = $(GLEW_CFLAGS) $(GL_CFLAGS)
mini_LDADD = $(GLEW_LIBS) $(GL_LIBS)

tetraeder_SOURCES = tetraeder.c
tetraeder_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
tetraeder_LDADD = librender.la $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS) -lm

librender_la_SOURCES = image.c normal.c object.c program.c report_status.c rgb.c shader.c \
											 surface.c texture.c texture_coordinate.c vertex_array_object.c vertex.c
librender_la_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
librender_la_LDFLAGS =
librender_la_LIBADD = $(MAGICK_LIBS) $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS)
