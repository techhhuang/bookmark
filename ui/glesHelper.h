#include<GLES2/gl2.h>
#include <stdio.h>
#include <assert.h>

static const char *vert_shader_text =
    "uniform mat4 rotation;\n"
    "attribute vec4 position;\n"
    "attribute vec4 color;\n"
    "varying vec4 v_color;\n"
    "void main() {\n"
    "  gl_Position = rotation*position;\n"
    "  v_color = color;\n"
    "}\n";

static const char *frag_shader_text =
    "precision mediump float;\n"
    "varying vec4 v_color;\n"
    "void main() {\n"
    "  gl_FragColor = v_color;\n"
    "}\n";

static const char *vert_simple_shader_text =
    "attribute vec4 position;\n"
    "void main() {\n"
    "  gl_Position = position;\n"
    "}\n";

static const char *frag_simple_shader_text =
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(1.0,0,0,0);\n"
    "}\n";

GLuint uniform_rotaion;


GLuint create_shader(const char *source, GLenum shader_type)
{
    GLuint shader;
    GLint status;

    shader = glCreateShader(shader_type);
    assert(shader != 0);

    glShaderSource(shader, 1, (const char **) &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char log[1000];
        GLsizei len;
        glGetShaderInfoLog(shader, 1000, &len, log);
        printf("Error: compiling %s: %*s\n",
            shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment",
            len, log);
        exit(1);
    }

    return shader;
}
void init_gl()
{
    printf("init gl start\n");
    GLuint frag, vert;
    GLint status;
    GLuint program;

    frag = create_shader(frag_simple_shader_text, GL_FRAGMENT_SHADER);
    vert = create_shader(vert_simple_shader_text, GL_VERTEX_SHADER);

    program = glCreateProgram();
    glAttachShader(program, frag);
    glAttachShader(program, vert);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        char log[1000];
        GLsizei len;
        glGetProgramInfoLog(program, 1000, &len, log);
        printf("Error: linking:\n%*s\n", len, log);
        exit(1);
    }

    glUseProgram(program);

    glBindAttribLocation(program, 0, "position");
    //glBindAttribLocation(program, 1, "color");

    glLinkProgram(program);

    //uniform_rotaion =glGetUniformLocation(program, "rotation");

    printf("init gl end\n");
}


