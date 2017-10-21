ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = mini tetraeder

lib_LTLIBRARIES = librender.la

include_HEADERS = image.h normal.h object.h program.h projection.h report_status.h rgb.h \
									shader.h surface.h texture_coordinate.h texture.h \
									vertex_array_object.h vertex.h

check_PROGRAMS = testsuite

check_HEADERS = munit.h \
								test_helper.h test_image.h test_normal.h test_object.h test_program.h \
								test_projection.h test_rgb.h test_shader.h test_surface.h \
								test_texture_coordinate.h test_texture.h test_vertex_array_object.h test_vertex.h

EXTRA_DIST = fragment-blue.glsl fragment.glsl fragment-normal.glsl fragment-red.glsl fragment-texture.glsl \
							invalid.glsl vertex.glsl vertex-identity.glsl vertex-normal-identity.glsl vertex-projection.glsl \
							vertex-texcoord.glsl colors.png

mini_SOURCES = mini.c
mini_CFLAGS = $(GLEW_CFLAGS) $(GL_CFLAGS)
mini_LDADD = $(GLEW_LIBS) $(GL_LIBS)

tetraeder_SOURCES = tetraeder.c
tetraeder_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
tetraeder_LDADD = librender.la $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS) -lm

testsuite_SOURCES = testsuite.c munit.c \
										test_helper.c test_image.c test_normal.c test_object.c test_program.c \
										test_projection.c test_rgb.c test_shader.c test_surface.c test_texture.c \
										test_texture_coordinate.c test_vertex_array_object.c test_vertex.c
testsuite_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
testsuite_LDADD = librender.la $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS)

librender_la_SOURCES = image.c normal.c object.c program.c projection.c report_status.c rgb.c shader.c \
											 surface.c texture.c texture_coordinate.c vertex_array_object.c vertex.c
librender_la_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
librender_la_LDFLAGS =
librender_la_LIBADD = $(MAGICK_LIBS) $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS)

check-local:
	./testsuite
