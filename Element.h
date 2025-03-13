#ifndef _ELEMENT_H
#define _ELEMENT_H

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <gl/freeglut.h>
#include <gl/glut.h>
#include <array>
#include <algorithm>

struct Element
{
	static constexpr int NUM_FACES = 6;
	std::array<unsigned int, NUM_FACES> color;
	double size;
	unsigned char _color[4];

	Element() : size(0.0) {
		std::fill(color.begin(), color.end(), 0);
	}

	void rotateZ() {
		std::rotate(color.rbegin(), color.rbegin() + 1, color.rend());
	}

	void rotateY() {
		std::swap(color[0], color[2]);
		std::swap(color[1], color[3]);
	}

	void rotateX() {
		std::swap(color[0], color[4]);
		std::swap(color[1], color[5]);
	}

	void setColor(int i, int colorValue) {
		if (i >= 0 && i < NUM_FACES) {
			color[i] = colorValue;
		}
	}

	unsigned char* at(int i) {
		if (i >= 0 && i < NUM_FACES) {
			_color[0] = (color[i] >> 16) & 0xFF;
			_color[1] = (color[i] >> 8) & 0xFF;
			_color[2] = color[i] & 0xFF;
		}
		return _color;
	}

	void draw() {
		glPushMatrix();
		glBegin(GL_QUADS);

		for (int i = 0; i < NUM_FACES; ++i) {
			glColor3ubv(at(i));
			glNormal3f(0, 0, 1);
			glVertex3f(size, size, size);
			glVertex3f(0, size, size);
			glVertex3f(0, 0, size);
			glVertex3f(size, 0, size);
		}

		glEnd();
		glPopMatrix();
	}

	void draw(double x, double y, double z) {
		glPushMatrix();
		glTranslated(x, y, z);
		draw();
		glPopMatrix();
	}
};

#endif;
