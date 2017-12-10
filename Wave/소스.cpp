#include "header.h"

// define & enum
enum COLOR {BLACK, WHITE, CONE, COLOR};
enum DIR {DOWN, UP};

#define MAPSIZE_H 350
#define MAPSIZE_W 450
#define MAPSIZE_D 600
#define VIEWANGLE 60
#define DELAY 10
#define STARNUM 5000

// ���� ����

bool Direction;
Point Color[COLOR];

// �ݹ� ���� �Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
GLvoid KeyBoard(unsigned char, int, int);
GLvoid Timer(int);
GLvoid Mouse(int, int, int, int);

// ����� ���� �Լ� 
GLvoid MakeColor();			// ����� �� ���ϰ�, ���� �ʱ�ȭ
GLvoid Effect();
GLvoid Initialize();

// Ŭ���� ����

class SubObject
{
	Point Star[STARNUM];
public:
	GLvoid Make()
	{

		for (int i = 0; i < STARNUM; ++i)
		{
			Star[i].x = rand() % 10000 - 5000;
			Star[i].y = rand() % 10000 - 5000;
			Star[i].z = rand() % 10000 - 5000;
		}
	}
	GLvoid Draw()
	{
		glPushMatrix();
		for(int i = 0; i < STARNUM; ++i)
		{
			glTranslatef(Star[i].x, Star[i].y, Star[i].z);
			glColor3f(1, 1, 1);
			glutWireCube(2);
			glRotatef(90, 1, 0, 1);
			glutWireCube(2);
			glRotatef(-90, 1, 0, 1);
			glTranslatef(-Star[i].x, -Star[i].y, -Star[i].z);
		}
		glPopMatrix();
	}
};

class Plane
{
	float ConeSize;
	float Angle; 
	float ConeY;
	
public:
	GLvoid ChangeDir()
	{
		if (Direction)
		{
			Direction = DOWN;
			Angle = 0;
		}
		else
		{
			Direction = UP;
			Angle = 0;
		}
	}
	GLvoid Init()
	{
		Angle = 0;
		ConeSize = 60;
		ConeY = 0;
		Direction = DOWN;
	}

	GLvoid Draw()
	{
		glPushMatrix();
		{
			glTranslatef(-150, ConeY, 0);
			glRotatef(Angle, 0, 0, 1);

			// Cone
			glLineWidth(4);
			
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
	GLvoid Update()
	{
		if (Direction)
		{
			ConeY+=2;
			Angle++;
			if (Angle < 0)
				Angle += 5;
			if (Angle > 45)
				Angle = 45;
			if (ConeY > 400)
				ConeY = 400;
		}
		else
		{
			ConeY-=2;
			Angle--;
			if (Angle > 0)
				Angle -= 5;
			if (Angle < -45)
				Angle = -45;
			if (ConeY < -400)
				ConeY = -400;
		}
	}
};

class Process
{
	Plane Cone;
	SubObject Star;

public:
	GLvoid Init()
	{
		Star.Make();
		Cone.Init();
	}
	GLvoid Update()
	{
		Cone.Update();
	}
	GLvoid Draw()
	{
		Star.Draw();
		Cone.Draw();
	}
	GLvoid Change()
	{
		Cone.ChangeDir();
	}
};

Process Manager;

void main(int argc, char *argv[]) {   //�ʱ�ȭ �Լ���  

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // ���÷��� ��� ���� 
	glutInitWindowPosition(250, 50);   // �������� ��ġ���� 
	glutInitWindowSize(MAPSIZE_W * 2, MAPSIZE_H * 2);    // �������� ũ�� ����
	glutCreateWindow("Wave");   // ������ ���� (������ �̸�) 
	
	Initialize();	// �ʱ�ȭ �Լ� �� ���� �Ҹ��� �ȴ�.
	
	glutTimerFunc(DELAY, Timer, 1);
	glutMouseFunc(Mouse);
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

	Effect();		// ȿ�� ��ĥ

	Manager.Draw();

	glutPostRedisplay();
	glutSwapBuffers();// ȭ�鿡 ����ϱ�
}

GLvoid Mouse(int Mouse, int Button, int x, int y)
{
	if (Mouse == GLUT_LEFT_BUTTON && Button == GLUT_DOWN)
	{
		Direction = UP;
	}
	else
	{
		Direction = DOWN;
	}

}

GLvoid Timer(int n)
{
	Manager.Update();
	glutTimerFunc(DELAY, Timer, 1);
}

// ����� ���� �Լ�

GLvoid MakeColor()
{
	Color[BLACK] = { 0,0,0 };
	Color[WHITE] = { 1,1,1 };
	Color[CONE] = { 1, 0.7f, 0.7f };
}

GLvoid Initialize()
{
	MakeColor();
	Manager.Init();
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

	gluPerspective(VIEWANGLE, 1, 1, 1000000);
	
	gluLookAt(
		-700, 80, 700,
		0, 0, 0,
		0, 1, 0
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}