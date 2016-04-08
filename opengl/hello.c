#include <GL/glut.h>

void myDisplay(void)

{
  glClear(GL_COLOR_BUFFER_BIT);

  glLineWidth(2.0f);
  // glRectf(0.0f, 0.0f, 0.5f, 0.5f);
  glBegin(GL_LINES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2f(-1.0f, 0.0f);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2f(1.0f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex2f(0.0f, -1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex2f(0.0f, 1.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex2f(-0.5f, -0.5f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex2f(0.5f, 0.5f);
  glEnd();

  glFlush();
}

int main(int argc, char *argv[])

{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

  glutInitWindowPosition(100, 100);

  glutInitWindowSize(600, 600);

  glutCreateWindow("第一个OpenGL程序");

  glutDisplayFunc(&myDisplay);

  glutMainLoop();

  return 0;
}