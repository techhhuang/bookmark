#ifndef __LOAD_SHADERS_H__
#define __LOAD_SHADERS_H__

#include <GLES2/gl2.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  GLenum type;
  const char* filename;
  GLuint shader;
} ShaderInfo;

GLuint LoadShaders(ShaderInfo*);

#ifdef __cplusplus
};
#endif

#endif
