check_PROGRAMS = suite

check_HEADERS = munit.h \
								test_group.h test_hash.h test_helper.h test_image.h test_integration.h test_list.h \
								test_material.h test_object.h test_parser.h test_program.h test_projection.h test_shader.h \
								test_texture.h test_vertex_array_object.h

EXTRA_DIST = fragment-blue.glsl fragment-normal.glsl fragment-red.glsl fragment-texture.glsl \
						 fragment-two-textures.glsl invalid.glsl vertex-identity.glsl vertex-normal-identity.glsl \
						 vertex-projection.glsl vertex-texcoord.glsl vertex-uv.glsl fragment-uv.glsl vertex-ambient.glsl \
						 fragment-ambient.glsl vertex-diffuse.glsl fragment-diffuse.glsl vertex-specular.glsl \
						 fragment-specular.glsl \
						 empty.mtl test.mtl colors.png gray.png name.obj

suite_SOURCES = suite.c munit.c \
								test_group.c test_hash.c test_helper.c test_image.c test_integration.c test_list.c \
								test_material.c test_object.c test_parser.c test_program.c test_projection.c test_shader.c \
								test_texture.c test_vertex_array_object.c
suite_CFLAGS = -I.. $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
suite_LDADD = ../fsim/librender.la $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS)

check-local:
	./suite
