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

void draw();
void drawLine();


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

    frag = create_shader(frag_shader_text, GL_FRAGMENT_SHADER);
    vert = create_shader(vert_shader_text, GL_VERTEX_SHADER);

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
    glBindAttribLocation(program, 1, "color");

    glLinkProgram(program);

    uniform_rotaion =glGetUniformLocation(program, "rotation");

}


void draw()
{
    glViewport(0, 0, 800, 600);
    //glClearColor(0.0,0.0, 0.5, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);
    drawLine();
//    glFlush();
}


void drawLine()
{
    static int count=1;
    printf("draw line start\n");
    static const GLfloat verts[4][2] = {
        { -0.5, -0.5 },
        {  0.5, -0.5 },
        {  0,    0.5 },
        {  0.5,  0.5 }
    };
    static const GLfloat colors[3][3] = {
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
    };
    GLfloat angle;
    GLfloat rotation[4][4] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };
    angle = count % 360 * M_PI / 180.0;
    printf("rotation angle is:%f\n",angle);
    rotation[0][0] =  cos(angle);
    rotation[0][2] =  sin(angle);
    rotation[2][0] = -sin(angle);
    rotation[2][2] =  cos(angle);

    glUniformMatrix4fv(uniform_rotaion, 1, GL_FALSE,
               (GLfloat *) rotation);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, verts);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    count +=1;
}
