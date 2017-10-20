dnl Run `./bootstrap` to generate a configure script.
dnl Then run `./configure` to generate a Makefile.
dnl Finally run `make` to build the project.
AC_PREREQ([2.69])
AC_INIT([fsim], [0.1.0], [jan@wedesoft.de])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([--warnings=no-portability foreign])
AC_CONFIG_MACRO_DIR([m4])
LT_INIT
AC_PROG_CC
AC_PROG_INSTALL
AC_LANG(C)
PKG_PROG_PKG_CONFIG

AX_HAVE_OPENGL
AC_MSG_CHECKING([for GL])
if test "x$have_GL" != "xyes"; then
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([Could not find GL])
else
  AC_MSG_RESULT([yes])
fi
AC_MSG_CHECKING([for GLU])
if test "x$have_GLU" != "xyes"; then
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([Could not find GLU])
else
  AC_MSG_RESULT([yes])
fi
AC_MSG_CHECKING([for glut])
if test "x$have_glut" != "xyes"; then
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([Could not find glut])
else
  AC_MSG_RESULT([yes])
fi

PKG_CHECK_MODULES(GLEW, glew >= 2.0.0)
AC_SUBST(GLEW_CFLAGS)
AC_SUBST(GLEW_LIBS)

PKG_CHECK_MODULES(MAGICK, ImageMagick >= 6.7.7)
AC_SUBST(MAGICK_CFLAGS)
AC_SUBST(MAGICK_LIBS)

PKG_CHECK_MODULES(BOEHM, bdw-gc >= 7.4.2)
AC_SUBST(BOEHM_CFLAGS)
AC_SUBST(BOEHM_LIBS)

AC_OUTPUT(Makefile)
