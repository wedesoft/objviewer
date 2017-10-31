ACLOCAL_AMFLAGS = -I m4

SUBDIRS = fsim tests

noinst_PROGRAMS = raw tetraeder

EXTRA_DIST = vertex.glsl fragment.glsl projection.glsl white.glsl

raw_SOURCES = raw.c
raw_CFLAGS = $(GLEW_CFLAGS) $(GL_CFLAGS)
raw_LDADD = $(GLEW_LIBS) $(GL_LIBS)

tetraeder_SOURCES = tetraeder.c
tetraeder_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
tetraeder_LDADD = fsim/librender.la $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS) -lm
