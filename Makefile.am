ACLOCAL_AMFLAGS = -I m4

SUBDIRS = fsim tests

noinst_PROGRAMS = minimal tetraeder

EXTRA_DIST = vertex.glsl fragment.glsl

minimal_SOURCES = minimal.c
minimal_CFLAGS = $(GLEW_CFLAGS) $(GL_CFLAGS)
minimal_LDADD = $(GLEW_LIBS) $(GL_LIBS)

tetraeder_SOURCES = tetraeder.c
tetraeder_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
tetraeder_LDADD = fsim/librender.la $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS) -lm
