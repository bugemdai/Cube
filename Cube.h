#define _CUBE_H

#include "Element.h"

// Define a 3D array to represent the cube's elements
Element elements[3][3][3];

// Array to store rotation angles for each face
int faceRotations[6];

// Size of the cube
double size;

// Colors for each face of the cube
unsigned int faceColors[6];

// Current face being rotated
int currentFace;

class Cube
{
public:
	Cube() : currentFace(-1) {}

	Cube(double cubeSize, unsigned int* colors) {
		initialize(cubeSize, colors);
	}

	void initialize(double cubeSize, unsigned int* colors) {
		memset(faceRotations, 0, sizeof(faceRotations));
		size = cubeSize;
		currentFace = -1;

		// Set colors for each face
		for (int i = 0; i < 6; i++) {
			faceColors[i] = colors[i];
		}

		// Set colors for each element on the cube's faces
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				elements[i][j][2].setColor(0, colors[0]);
				elements[i][j][0].setColor(1, colors[1]);
			}
		}
		for (int k = 0; k < 3; k++) {
			for (int j = 0; j < 3; j++) {
				elements[j][0][k].setColor(2, colors[2]);
				elements[j][2][k].setColor(3, colors[3]);
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				elements[0][k][i].setColor(4, colors[4]);
				elements[2][k][i].setColor(5, colors[5]);
			}
		}

		// Set size for each element
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					elements[i][j][k].size = (cubeSize / 3.0) * 0.95;
				}
			}
		}
	}

	void draw() {
		const double shrinkFactor = 0.65;
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(((1.0 - shrinkFactor) / 2) * size + shrinkFactor * size / 2,
					 ((1.0 - shrinkFactor) / 2) * size + shrinkFactor * size / 2,
					 ((1.0 - shrinkFactor) / 2) * size + shrinkFactor * size / 2);
		glutSolidCube(size * shrinkFactor);
		glPopMatrix();

		memset(ok, true, sizeof(ok));
		if (currentFace != -1) {
			glPushMatrix();
			int i, j, k;

			if (currentFace == 0 || currentFace == 1) {
				k = (currentFace & 1) * 2;
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						ok[i][j][k] = false;

				glTranslated(size / 2, size / 2, 0);
				glRotatef(faceRotations[currentFace], 0, 0, 1);
				glTranslated(-size / 2, -size / 2, 0);
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						elements[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
			} else if (currentFace == 2 || currentFace == 3) {
				j = (currentFace & 1) * 2;
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						ok[i][j][k] = false;

				glTranslated(size / 2, 0, size / 2);
				glRotatef(faceRotations[currentFace], 0, 1, 0);
				glTranslated(-size / 2, 0, -size / 2);
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						elements[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
			} else if (currentFace == 4 || currentFace == 5) {
				i = (currentFace & 1) * 2;
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						ok[i][j][k] = false;

				glTranslated(0, size / 2, size / 2);
				glRotatef(faceRotations[currentFace], 1, 0, 0);
				glTranslated(0, -size / 2, -size / 2);
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						elements[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
			}
			glPopMatrix();
		}

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					if (ok[i][j][k])
						elements[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
	}

	void rotateFace90(int faceIndex, int direction) {
		int i, j, k;
		if (direction == -1) direction = 3;
		while (direction--) {
			if (faceIndex == 0 || faceIndex == 1) {
				k = (faceIndex & 1) * 2;
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						tmp[j][2 - i] = elements[i][j][k];
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						tmp[i][j].rotateZ(), elements[i][j][k] = tmp[i][j];
			} else if (faceIndex == 2 || faceIndex == 3) {
				j = (faceIndex & 1) * 2;
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						tmp[k][2 - i] = elements[i][j][k];
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						tmp[i][k].rotateX(), elements[i][j][k] = tmp[i][k];
			} else if (faceIndex == 4 || faceIndex == 5) {
				i = (faceIndex & 1) * 2;
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						tmp[k][2 - j] = elements[i][j][k];
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						tmp[j][k].rotateY(), elements[i][j][k] = tmp[j][k];
			}
		}
	}

	void rotateFace(int faceIndex, int angle) {
		if (currentFace == -1 || currentFace == faceIndex) {
			faceRotations[faceIndex] += angle;

			if (faceRotations[faceIndex] % 90 != 0) {
				currentFace = faceIndex;
			} else {
				if ((faceRotations[faceIndex] < 0) ^ (currentFace == 2 || currentFace == 3))
					rotateFace90(faceIndex, 1);
				else
					rotateFace90(faceIndex, -1);
				faceRotations[faceIndex] = 0;
				currentFace = -1;
			}
		}
	}

private:
	int _angle[4];
	bool ok[4][4][4];
	Element tmp[4][4];
};
