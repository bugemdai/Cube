#include "Cube.h"

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <Windows.h>
#include <ctime>
#include <time.h>
#include <stdlib.h>

#define CUBE_SIZE 10
#define TIMER 1

unsigned int c[9] = { 0xFFFFFF, 0xFFFF00, 0x0000FF, 0x00FF00, 0xFF0000, 	0xCD853F };

GLfloat lightPos[] = { 0, 100, 200, 0 };
int xRot = 24, yRot = 34, zRot = 0;
double translateZ = -35.0;
Cube cube;
int timerOn = 0;

void display()
{
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glTranslatef(0, 0, translateZ);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
	cube.draw();
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(60, fAspect, 1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init()
{
	glClearColor(0.5, 0.5, 0.5, 0.5);
	srand(time(0));

	float mat_specular[] = { 0.3, 0.3, 0.3, 0 };
	float diffuseLight[] = { 0.2, 0.2, 0.2, 1 };
	float ambientLight[] = { 0.9, 0.9, 0.9, 1.0 };
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	cube.clear(CUBE_SIZE, c);
}

void specialKeys(int key, int, int)
{
	bool tmp = true;

	if (key == GLUT_KEY_F5)
	{
		for (int i = 0; i < 1000000; i++)
		{
			yRot -= 3;
			if (yRot < 0)
				yRot += 360;
			glutPostRedisplay();
			Sleep(30);
		}
	}

	if (key == GLUT_KEY_DOWN)
	{
		xRot += 3;
		if (xRot >= 360)
			xRot -= 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_UP)
	{
		xRot -= 3;
		if (xRot < 0)
			xRot += 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_RIGHT)
	{
		yRot += 3;
		if (yRot >= 360)
			yRot -= 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_LEFT)
	{
		yRot -= 3;
		if (yRot < 0)
			yRot += 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_HOME)
	{
		translateZ += 5;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_END)
	{
		translateZ -= 5;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_F1)
	{
		cube.clear(CUBE_SIZE, c);
		glutPostRedisplay();
	}
}

void keys(unsigned char key, int, int)
{
	if (cube.current == -1 && key >= '0' && key < '6')
	{
		cube.Rotate(key - '0', 3);
		display();
	}
}

void mouse(int key, int state, int, int)
{
	if (key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		timerOn = 1 - timerOn;
	}
}

void timer(int)
{
	glutTimerFunc(TIMER, timer, 0);
	if (timerOn)
	{
		if (cube.current == -1)
			keys(rand() % 6 + '0', 0, 0);
		else
			cube.Rotate(cube.current, 3);
	}
	else
	{
		if (cube.current != -1)
			cube.Rotate(cube.current, 3);
	}
	display();
}

void menuEvent(int option) {

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GLUT_MULTISAMPLE);	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 1);
	glutCreateWindow("Cube");
	
	glutCreateMenu(menuEvent);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	glutTimerFunc(TIMER, timer, 0);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}