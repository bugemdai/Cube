#define _CUBE_H

#include "Element.h"

class Cube
{
	Element a[3][3][3];
	int rotate[6];
	double size;
	unsigned int color[6];

public:
	int current;

	Cube() {}

	Cube(double size, unsigned int* color) {
		clear(size, color);
	}

	void clear(double size, unsigned int* color){
		memset(rotate, 0, sizeof(rotate));
		this->size = size;
		current = -1;

		int i, j, k;
		for (i = 0; i < 6; i++)
			this->color[i] = color[i];

		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				a[i][j][2].setColor(0, color[0]);

		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				a[i][j][0].setColor(1, color[1]);

		for (k = 0; k < 3; k++)
			for (j = 0; j < 3; j++)
				a[j][0][k].setColor(2, color[2]);

		for (k = 0; k < 3; k++)
			for (j = 0; j < 3; j++)
				a[j][2][k].setColor(3, color[3]);

		for (i = 0; i < 3; i++)
			for (k = 0; k < 3; k++)
				a[0][k][i].setColor(4, color[4]);

		for (i = 0; i < 3; i++)
			for (k = 0; k < 3; k++)
				a[2][k][i].setColor(5, color[5]);

		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				for (k = 0; k < 3; k++)
					a[i][j][k].size = (size / 3.0) * 0.95;
	}

	void draw()	{
		const double K = 0.65;
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(((1.0 - K) / 2) * size + K * size / 2, ((1.0 - K) / 2) * size + K * size / 2, ((1.0 - K) / 2) * size + K * size / 2);
		glutSolidCube(size * K);
		glPopMatrix();

		memset(ok, true, sizeof(ok));
		if (current != -1)
		{
			glPushMatrix();
			int i, j, k;

			if (current == 0 || current == 1)
			{
				k = (current & 1) * 2;
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						ok[i][j][k] = false;

				glTranslated(size / 2, size / 2, 0);   // ñäâèãàåìñÿ ê öåíòðó
				glRotatef(rotate[current], 0, 0, 1);   // êðóòèì
				glTranslated(-size / 2, -size / 2, 0); // ñäâèãàåìñÿ îáðàòíî
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
			}
			else if (current == 2 || current == 3)
			{
				j = (current & 1) * 2;
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						ok[i][j][k] = false;

				glTranslated(size / 2, 0, size / 2);
				glRotatef(rotate[current], 0, 1, 0);
				glTranslated(-size / 2, 0, -size / 2);
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
			}
			else if (current == 4 || current == 5)
			{
				i = (current & 1) * 2;
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						ok[i][j][k] = false;

				glTranslated(0, size / 2, size / 2);
				glRotatef(rotate[current], 1, 0, 0);
				glTranslated(0, -size / 2, -size / 2);
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
			}
			glPopMatrix();
		}

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					if (ok[i][j][k])
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
	}

public:
	void rot90(int idx, int sign)
	{
		int i, j, k;
		if (sign == -1)
			sign = 3;
		while (sign--)
		{
			if (idx == 0 || idx == 1)
			{
				k = (idx & 1) * 2;
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						tmp[j][2 - i] = a[i][j][k];
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						tmp[i][j].rotateZ(), a[i][j][k] = tmp[i][j];
			}
			else if (idx == 2 || idx == 3)
			{
				j = (idx & 1) * 2;
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						tmp[k][2 - i] = a[i][j][k];
				for (i = 0; i < 3; i++)
					for (k = 0; k < 3; k++)
						tmp[i][k].rotateX(), a[i][j][k] = tmp[i][k];
			}
			else if (idx == 4 || idx == 5)
			{
				i = (idx & 1) * 2;
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						tmp[k][2 - j] = a[i][j][k];
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++)
						tmp[j][k].rotateY(), a[i][j][k] = tmp[j][k];
			}
		}
	}

	void Rotate(int idx, int angle)
	{
		if (current == -1 || current == idx)
		{
			rotate[idx] += angle;

			if (rotate[idx] % 90 != 0)
			{
				current = idx;
			}
			else
			{
				if ((rotate[idx] < 0) ^ (current == 2 || current == 3))
					rot90(idx, 1);
				else
					rot90(idx, -1);
				rotate[idx] = 0;
				current = -1;
			}
		}
	}
private:
	int _angle[4];
	bool ok[4][4][4];
	Element tmp[4][4];
};