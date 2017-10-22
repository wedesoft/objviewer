#pragma once
#include <GL/gl.h>


int report_status(const char *text, GLuint context, GLuint status);

int report_compile_status(const char *file_name, GLuint context);

int report_link_status(GLuint context);
