#include<GL/glut.h>
void initial()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200, 0.0, 150.0);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(30, 30);
	glVertex2i(105, 80);
	glVertex2i(15, 80);
	glVertex2i(90, 30);
	glVertex2i(60, 100);
	glEnd();
	glFlush();

}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Hello, OpenGL");
	glutDisplayFunc(&display);
	initial();
	glutMainLoop();
	return 0;
}
