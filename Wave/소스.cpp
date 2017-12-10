#include "header.h"

// define & enum
enum COLOR {BLACK, WHITE, CONE, COLOR};
enum DIR {UP, DOWN};

#define MAPSIZE_H 350
#define MAPSIZE_W 450
#define MAPSIZE_D 600
#define VIEWANGLE 60

// ���� ����

Point Color[COLOR];

// Ŭ���� ����
class Plane
{
	float ConeSize = 60;
	bool Direction = DOWN;
public:
	
	GLvoid Draw()
	{
		glPushMatrix();
		{
			// Cone
			glLineWidth(4);
			glTranslatef(-150, 0, 0);
			glColor3f(Color[CONE].x, Color[CONE].y, Color[CONE].z);
			glRotatef(90, 0, 1, 0);
			glutWireCone(ConeSize / 3, ConeSize, 4, 1);

			// Bounding Box
			glLineWidth(1);
			glColor3f(1, 1, 1);
			glTranslatef(0,0,ConeSize);
			glutWireCube(15);
		}glPopMatrix();
	}

};

class Process
{
	Plane Cone;
public:
	GLvoid Init()
	{
		Cone.Draw();
	}
	GLvoid Update()
	{
		Cone.Draw();
	}
};

Process Manager;

// �ݹ� ���� �Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
GLvoid KeyBoard(unsigned char, int, int);

// ����� ���� �Լ� 
GLvoid MakeColor();			// ����� �� ���ϰ�, ���� �ʱ�ȭ
GLvoid Effect();

void main(int argc, char *argv[]) {   //�ʱ�ȭ �Լ���  

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // ���÷��� ��� ���� 
	glutInitWindowPosition(250, 50);   // �������� ��ġ���� 
	glutInitWindowSize(MAPSIZE_W * 2, MAPSIZE_H * 2);    // �������� ũ�� ����
	glutCreateWindow("Wave");   // ������ ���� (������ �̸�) 
	
	MakeColor();
	
	glutKeyboardFunc(KeyBoard);
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����   
	glutReshapeFunc(Reshape);   // �ٽ� �׸��� �Լ��� ���� 
	glutMainLoop();
}

// ������ ��� �Լ� 
GLvoid drawScene(GLvoid)
{
	glClearColor(Color[BLACK].x, Color[BLACK].y, Color[BLACK].z, 1.0f);   // �������� 'blue' �� ����  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // ������ ������ ��ü�� ĥ�ϱ� 
	// ȿ�� ��ĥ
	Effect();
	Manager.Update();
	glutPostRedisplay();
	glutSwapBuffers();// ȭ�鿡 ����ϱ�
}

// ����� ���� �Լ�

GLvoid MakeColor()
{
	Color[BLACK] = { 0,0,0 };
	Color[WHITE] = { 1,1,1 };
	Color[CONE] = { 1, 0.7f, 0.7f };
}

GLvoid Effect()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
}

GLvoid KeyBoard(unsigned char key, int a, int b)
{
	
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(VIEWANGLE, 1, 1, 10000);
	
	gluLookAt(
		-300, 80, 600,
		0, 0, 0,
		0, 1, 0
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}