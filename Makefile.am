ACLOCAL_AMFLAGS = -I m4

SUBDIRS = fsim tests

noinst_PROGRAMS = mini tetraeder

EXTRA_DIST = vertex.glsl fragment.glsl

mini_SOURCES = mini.c
mini_CFLAGS = $(GLEW_CFLAGS) $(GL_CFLAGS)
mini_LDADD = $(GLEW_LIBS) $(GL_LIBS)

tetraeder_SOURCES = tetraeder.c
tetraeder_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
tetraeder_LDADD = fsim/librender.la $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS) -lm
