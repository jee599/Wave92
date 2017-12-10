#include "header.h"

// define & enum
enum COLOR {BLACK, WHITE, CONE, COLOR};
enum DIR {UP, DOWN};

#define MAPSIZE_H 350
#define MAPSIZE_W 450
#define MAPSIZE_D 600
#define VIEWANGLE 60

// 전역 변수

Point Color[COLOR];

// 클래스 정의
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

// 콜백 관련 함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
GLvoid KeyBoard(unsigned char, int, int);

// 사용자 정의 함수 
GLvoid MakeColor();			// 사용할 색 정하고, 만들어서 초기화
GLvoid Effect();

void main(int argc, char *argv[]) {   //초기화 함수들  

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // 디스플레이 모드 설정 
	glutInitWindowPosition(250, 50);   // 윈도우의 위치지정 
	glutInitWindowSize(MAPSIZE_W * 2, MAPSIZE_H * 2);    // 윈도우의 크기 지정
	glutCreateWindow("Wave");   // 윈도우 생성 (윈도우 이름) 
	
	MakeColor();
	
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
	// 효과 떡칠
	Effect();
	Manager.Update();
	glutPostRedisplay();
	glutSwapBuffers();// 화면에 출력하기
}

// 사용자 정의 함수

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