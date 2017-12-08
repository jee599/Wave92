#include "header.h"

#define MAPSIZE_H 350
#define MAPSIZE_W 450
#define MAPSIZE_D 600
#define VIEWANGLE 100

GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
GLvoid KeyBoard(unsigned char, int, int);

void main(int argc, char *argv[]) {   //초기화 함수들  

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100);   // 윈도우의 위치지정 
	glutInitWindowSize(MAPSIZE_W * 2, MAPSIZE_H * 2);    // 윈도우의 크기 지정
	glutCreateWindow("Example 1");   // 윈도우 생성 (윈도우 이름) 
	glutKeyboardFunc(KeyBoard);
	glutDisplayFunc(drawScene);    // 출력 함수의 지정   
	glutReshapeFunc(Reshape);   // 다시 그리기 함수의 지정 
	glutMainLoop();
}

// 윈도우 출력 함수 
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 0.5f, 0.4f, 1.0f);   // 바탕색을 'blue' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // 설정된 색으로 전체를 칠하기 
	glutPostRedisplay();
	glutSwapBuffers();// 화면에 출력하기
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