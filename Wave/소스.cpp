#include "header.h"

// define & enum
enum COLOR {BLACK, WHITE, CONE, COLOR};
enum DIR {DOWN, UP};

#define MAPSIZE_H 350
#define MAPSIZE_W 450
#define MAPSIZE_D 600

const int VIEWANGLE = 60;
const int DELAY = 10;
const int STARNUM = 1000;

// 전역 변수

float ConeY;
float Speed;
float T;
int Ef;
bool Direction;
Point Color[COLOR];

// 콜백 관련 함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
GLvoid KeyBoard(unsigned char, int, int);
GLvoid Timer(int);
GLvoid Mouse(int, int, int, int);

// 사용자 정의 함수 
GLvoid MakeColor();			// 사용할 색 정하고, 만들어서 초기화
GLvoid Effect();
GLvoid Initialize();

// 클래스 정의

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
			Star[i].x -= T;
			if (Star[i].x < -2000)
				Star[i].x += 5000;
			glTranslatef(Star[i].x, Star[i].y - (ConeY/(5000-Star[i].z)), Star[i].z);

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
	bool Coll;
public:
	GLvoid Tail()
	{

	}
	GLvoid CollEffect()	//충돌체크 이펙트
	{
		glPushMatrix();
		if (Ef < 50)	
		{
			glColor3f(1, 1, 1);
			for (int i = 0; i < 10; ++i)
			{
				glRotatef(i*36, 1, 0, 0);
				glTranslatef(Ef, Ef, Ef);
				glutWireCube(i+5);
				glTranslatef(-Ef, -Ef, -Ef);

				glRotatef(i * 36, 0, 1, 0);
				glTranslatef(Ef, Ef, Ef);
				glutWireCube(i+7);
				glTranslatef(-Ef, -Ef, -Ef);
			}
		}
		else
			Ef = 0;
		glPopMatrix();
	}
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
		Coll = false;
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
			glColor3f(1, 0, 0);
			glTranslatef(0,0,ConeSize);
			glutWireCube(15);
			if(Coll)
				CollEffect();
		}glPopMatrix();
	}
	GLvoid Update()
	{
		if (Coll == false)		// 충돌 시엔 안 움직이게
		{
			if (Direction)
			{
				ConeY += Speed;
				Angle++;
				if (Angle < 0)
					Angle += 10;
				if (Angle > 60)
					Angle = 60;
				if (ConeY > 500)
					ConeY = 500;
			}
			else
			{
				ConeY -= Speed;
				Angle--;
				if (Angle > 0)
					Angle -= 10;
				if (Angle < -60)
					Angle = -60;
				if (ConeY < -500)
					ConeY = -500;
			}
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

void main(int argc, char *argv[]) {   //초기화 함수들  

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // 디스플레이 모드 설정 
	glutInitWindowPosition(250, 50);   // 윈도우의 위치지정 
	glutInitWindowSize(MAPSIZE_W * 2, MAPSIZE_H * 2);    // 윈도우의 크기 지정
	glutCreateWindow("Wave");   // 윈도우 생성 (윈도우 이름) 
	
	Initialize();	// 초기화 함수 한 번만 불리면 된다.
	
	glutTimerFunc(DELAY, Timer, 1);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(KeyBoard);
	glutDisplayFunc(drawScene);    // 출력 함수의 지정   
	glutReshapeFunc(Reshape);   // 다시 그리기 함수의 지정 
	glutMainLoop();
}

// 윈도우 출력 함수 
GLvoid drawScene(GLvoid)
{
	glClearColor(Color[BLACK].x, Color[BLACK].y, Color[BLACK].z, 1.0f);   // 바탕색을 'blue' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // 설정된 색으로 전체를 칠하기 

	Effect();		// 효과 떡칠

	Manager.Draw();

	glutPostRedisplay();
	glutSwapBuffers();// 화면에 출력하기
}

GLvoid Mouse(int Mouse, int Button, int x, int y)
{
	if (Mouse == GLUT_LEFT_BUTTON && Button == GLUT_DOWN)
	{
		Speed = 0;
		Direction = UP;
	}
	else
	{
		Speed = 0;
		Direction = DOWN;
	}

}

GLvoid Timer(int n)
{
	Ef++;
	Speed += 0.19;
	if (Speed > 7)
		Speed = 7;

	T += 0.01;
	if (T > 5)
		T = 5;
	Manager.Update();
	glutTimerFunc(DELAY, Timer, 1);
}

// 사용자 정의 함수

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
		-500, 80, 1500,
		200, 0, 0,
		0, 1, 0
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}