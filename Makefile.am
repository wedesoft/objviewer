ACLOCAL_AMFLAGS = -I m4

SUBDIRS = fsim tests

noinst_PROGRAMS = raw tetraeder readobj

EXTRA_DIST = vertex.glsl fragment.glsl

raw_SOURCES = raw.c
raw_CFLAGS = $(GLEW_CFLAGS) $(GL_CFLAGS)
raw_LDADD = $(GLEW_LIBS) $(GL_LIBS)

readobj_SOURCES = readobj.c
readobj_CFLAGS = $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
readobj_LDADD = fsim/librender.la $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS) -lm

tetraeder_SOURCES = tetraeder.c
tetraeder_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
tetraeder_LDADD = fsim/librender.la $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS) -lm
