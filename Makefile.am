ACLOCAL_AMFLAGS = -I m4

SUBDIRS = fsim tests

noinst_PROGRAMS = raw objviewer

EXTRA_DIST = vertex.glsl fragment.glsl

raw_SOURCES = raw.c
raw_CFLAGS = $(GLEW_CFLAGS) $(GL_CFLAGS)
raw_LDADD = $(GLEW_LIBS) $(GL_LIBS)

objviewer_SOURCES = objviewer.c
objviewer_CFLAGS = $(MAGICK_CFLAGS) $(GLEW_CFLAGS) $(GL_CFLAGS) $(BOEHM_CFLAGS)
objviewer_LDADD = fsim/librender.la $(GLEW_LIBS) $(GL_LIBS) $(BOEHM_LIBS) -lm


MMSEV.obj: MMSEV.zip
	unzip -o $<
	sed -i /illum/d MMSEV.mtl
	sed -i /map_Ks/d MMSEV.mtl
	sed -i /map_Bump/d MMSEV.mtl
	touch $@

# https://nasa3d.arc.nasa.gov/detail/nmss-sev
MMSEV.zip:
	curl -O https://nasa3d.arc.nasa.gov/shared_assets/models/nmss-sev/MMSEV.zip
