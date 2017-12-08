#include "header.h"

#define MAPSIZE_H 350
#define MAPSIZE_W 450
#define MAPSIZE_D 600
#define VIEWANGLE 100

GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
GLvoid KeyBoard(unsigned char, int, int);

void main(int argc, char *argv[]) {   //�ʱ�ȭ �Լ���  

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100);   // �������� ��ġ���� 
	glutInitWindowSize(MAPSIZE_W * 2, MAPSIZE_H * 2);    // �������� ũ�� ����
	glutCreateWindow("Example 1");   // ������ ���� (������ �̸�) 
	glutKeyboardFunc(KeyBoard);
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����   
	glutReshapeFunc(Reshape);   // �ٽ� �׸��� �Լ��� ���� 
	glutMainLoop();
}

// ������ ��� �Լ� 
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 0.5f, 0.4f, 1.0f);   // �������� 'blue' �� ����  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // ������ ������ ��ü�� ĥ�ϱ� 
	glutPostRedisplay();
	glutSwapBuffers();// ȭ�鿡 ����ϱ�
}


GLvoid KeyBoard(unsigned char key, int a, int b)
{

}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(VIEWANGLE, 1, 1, 1000);
	glTranslatef(0, 0, -MAPSIZE_D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}