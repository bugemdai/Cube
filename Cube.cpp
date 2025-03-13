#include "Cube.h"

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <Windows.h>
#include <ctime>
#include <time.h>
#include <stdlib.h>
#include <GL/glut.h>

#define CUBE_SIZE 10
#define TIMER_INTERVAL 1

unsigned int faceColors[6] = { 0xFFFFFF, 0xFFFF00, 0x0000FF, 0x00FF00, 0xFF0000, 0xCD853F };

GLfloat lightPosition[] = { 0, 100, 200, 0 };
int xRotation = 24, yRotation = 34;
double zTranslation = -35.0;
Cube cube;
int timerActive = 0;

void display()
{
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glTranslatef(0, 0, zTranslation);
	glRotatef(xRotation, 1, 0, 0);
	glRotatef(yRotation, 0, 1, 0);
	glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
	cube.draw();
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(60, aspectRatio, 1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init()
{
	glClearColor(0.5, 0.5, 0.5, 0.5);
	srand(static_cast<unsigned int>(time(0)));

	float specularMaterial[] = { 0.3, 0.3, 0.3, 0 };
	float diffuseLight[] = { 0.2, 0.2, 0.2, 1 };
	float ambientLight[] = { 0.9, 0.9, 0.9, 1.0 };
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	cube.clear(CUBE_SIZE, faceColors);
}

void specialKeys(int key, int, int)
{
	switch (key) {
		case GLUT_KEY_F5:
			for (int i = 0; i < 1000000; i++) {
				yRotation = (yRotation - 3 + 360) % 360;
				glutPostRedisplay();
				Sleep(30);
			}
			break;
		case GLUT_KEY_DOWN:
			xRotation = (xRotation + 3) % 360;
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP:
			xRotation = (xRotation - 3 + 360) % 360;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			yRotation = (yRotation + 3) % 360;
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			yRotation = (yRotation - 3 + 360) % 360;
			glutPostRedisplay();
			break;
		case GLUT_KEY_HOME:
			zTranslation += 5;
			glutPostRedisplay();
			break;
		case GLUT_KEY_END:
			zTranslation -= 5;
			glutPostRedisplay();
			break;
		case GLUT_KEY_F1:
			cube.clear(CUBE_SIZE, faceColors);
			glutPostRedisplay();
			break;
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

void mouse(int button, int state, int, int)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		timerActive = 1 - timerActive;
	}
}

void timer(int)
{
	glutTimerFunc(TIMER_INTERVAL, timer, 0);
	if (timerActive)
	{
		if (cube.current == -1)
		{
			keys(rand() % 6 + '0', 0, 0);
		}
		else
		{
			cube.Rotate(cube.current, 3);
		}
	}
	else if (cube.current != -1)
	{
		cube.Rotate(cube.current, 3);
	}
	display();
}

void menuEvent(int option) {
	// Placeholder for menu event handling
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GLUT_MULTISAMPLE);	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cube");
	
	glutCreateMenu(menuEvent);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	glutTimerFunc(TIMER_INTERVAL, timer, 0);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}
