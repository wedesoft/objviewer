check_PROGRAMS = testsuite

check_HEADERS = munit.h \
								test_helper.h test_image.h test_list.h test_object.h test_program.h \
								test_projection.h test_rgb.h test_shader.h test_surface.h \
								test_texture_coordinate.h test_texture.h test_vertex_array_object.h test_vertex.h

EXTRA_DIST = fragment-blue.glsl fragment-normal.glsl fragment-red.glsl fragment-texture.glsl \
							invalid.glsl vertex-identity.glsl vertex-normal-identity.glsl vertex-projection.glsl \
							vertex-texcoord.glsl colors.png

testsuite_SOURCES = testsuite.c munit.c \
										test_helper.c test_image.c test_list.c test_object.c test_program.c \
										test_projection.c test_rgb.c test_shader.c test_surface.c test_texture.c \
										test_texture_coordinate.c test_vertex_array_object.c test_vertex.c
testsuite_CFLAGS = -I.. $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
testsuite_LDADD = ../fsim/librender.la $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS)

check-local:
	./testsuite
