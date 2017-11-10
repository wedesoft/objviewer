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
	sed -i /map_Bump/d MMSEV.mtl
	touch $@

# https://nasa3d.arc.nasa.gov/detail/nmss-sev
MMSEV.zip:
	curl -O https://nasa3d.arc.nasa.gov/shared_assets/models/nmss-sev/MMSEV.zip

HDU_lowRez_part1.obj: HDU.zip
	unzip -oj $<
	sed -i /illum/d HDU_lowRez_part1.mtl
	sed -i /illum/d HDU_lowRez_part2.mtl
	sed -i /Tf/d HDU_lowRez_part1.mtl
	sed -i /Tf/d HDU_lowRez_part2.mtl
	sed -i "s/s /g /" HDU_lowRez_part1.obj
	sed -i "s/s /g /" HDU_lowRez_part2.obj

# https://nasa3d.arc.nasa.gov/detail/nmss-hdu
HDU.zip:
	curl -O https://nasa3d.arc.nasa.gov/shared_assets/models/nmss-hdu/HDU.zip
