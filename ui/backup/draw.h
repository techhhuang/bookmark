#include<glesHelper.h>
#define WIDTH 800
#define HEIGHT 600
#define TX(x)  (x*2.0/WIDTH -1)
#define TY(y)  (1-y*2.0/HEIGHT)
#define TW(w)  (w*2.0/WIDTH)
#define TH(h)  (h*2.0/HEIGHT)
void draw();
void drawLine(int x, int y, int x1, int y1);
void drawComplex();
void drawRect(int x, int y, int w, int h);

void draw()
{
    init_gl();
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.0,0.0, 0.5, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);
    drawLine(0,0,400,300);
    drawLine(400,300,800,0);
    drawRect(0,0,100,100);
    drawRect(400,300,50,50);
    
}

void drawLine(int x, int y, int x1, int y1)
{
    printf("draw line:%d %d %d %d\n",x,y,x1,y1);
    GLfloat verts[]={
        TX(x),TY(y),
        TX(x1),TY(y1)
    };

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, verts);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_LINES, 0, 2);
    glDisableVertexAttribArray(0);
}

void drawRect(int x, int y, int w, int h)
{
    printf("draw rect:%d %d %d %d\n",x,y,w,h);
    GLfloat verts[] = {
         TX(x) , TY(y),
         TX(x) , TY(y) - TH(h),
         TX(x) + TW(w), TY(y) - TH(h),
         TX(x) + TW(w), TY(y)
    };
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, verts);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableVertexAttribArray(0);
}
void drawComplex()
{
    static int count = 1;
    printf("draw line start\n");
    static const GLfloat verts[4][2] = {
        { -0.5, -0.5 },
        {  0.5, -0.5 },
        {  0,    0.5 },
        {  0.5,  0.5 }
    };
    static const GLfloat colors[3][3] = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };
    GLfloat angle;
    GLfloat rotation[4][4] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };
    angle = count % 360 * M_PI / 180.0;
    printf("rotation angle is:%f\n", angle);
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

    glDrawArrays(GL_LINES, 0, 2);
    count += 1;
}
